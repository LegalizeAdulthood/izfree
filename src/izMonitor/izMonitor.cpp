// izfree Tools for Windows Installer
// Copyright (C) 2001-2002 Pahvant Technologies, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// izMonitor.cpp : Implementation of WinMain


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f izMonitorps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "izMonitor.h"

#include "izMonitor_i.c"
#include "Monitor.h"


const DWORD dwTimeOut = 5000; // time for EXE to be idle before shutting down
const DWORD dwPause = 1000; // time to wait for threads to finish up

// Passed to CreateThread to monitor the shutdown event
static DWORD WINAPI MonitorProc(void* pv)
{
    CExeModule* p = (CExeModule*)pv;
    p->MonitorShutdown();
    return 0;
}

LONG CExeModule::Unlock()
{
    LONG l = CComModule::Unlock();
    if (l == 0)
    {
        bActivity = true;
        SetEvent(hEventShutdown); // tell monitor that we transitioned to zero
    }
    return l;
}

//Monitors the shutdown event
void CExeModule::MonitorShutdown()
{
    while (1)
    {
        WaitForSingleObject(hEventShutdown, INFINITE);
        DWORD dwWait=0;
        do
        {
            bActivity = false;
            dwWait = WaitForSingleObject(hEventShutdown, dwTimeOut);
        } while (dwWait == WAIT_OBJECT_0);
        // timed out
        if (!bActivity && m_nLockCnt == 0) // if no activity let's really bail
        {
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
            CoSuspendClassObjects();
            if (!bActivity && m_nLockCnt == 0)
#endif
                break;
        }
    }
    CloseHandle(hEventShutdown);
    PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
}

bool CExeModule::StartMonitor()
{
    hEventShutdown = CreateEvent(NULL, false, false, NULL);
    if (hEventShutdown == NULL)
        return false;
    DWORD dwThreadID;
    HANDLE h = CreateThread(NULL, 0, MonitorProc, this, 0, &dwThreadID);
    return (h != NULL);
}

CExeModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_AppIdRecord, CAppIdRecord)
OBJECT_ENTRY(CLSID_AppIdTable, CAppIdTable)
OBJECT_ENTRY(CLSID_Monitor, CMonitor)
OBJECT_ENTRY(CLSID_ClassTable, CClassTable)
OBJECT_ENTRY(CLSID_ClassRecord, CClassRecord)
OBJECT_ENTRY(CLSID_RegistryTable, CRegistryTable)
OBJECT_ENTRY(CLSID_ProgIdTable, CProgIdTable)
OBJECT_ENTRY(CLSID_TypeLibTable, CTypeLibTable)
OBJECT_ENTRY(CLSID_ServiceControlTable, CServiceControlTable)
OBJECT_ENTRY(CLSID_ServiceInstallTable, CServiceInstallTable)
OBJECT_ENTRY(CLSID_RegistryRecord, CRegistryRecord)
OBJECT_ENTRY(CLSID_ProgIdRecord, CProgIdRecord)
OBJECT_ENTRY(CLSID_TypeLibRecord, CTypeLibRecord)
OBJECT_ENTRY(CLSID_ServiceControlRecord, CServiceControlRecord)
OBJECT_ENTRY(CLSID_ServiceInstallRecord, CServiceInstallRecord)
END_OBJECT_MAP()

///////////////////////////////////////////////////////////////////////////
// check_registry
//
// Checks the return values from ::RegXXX functions.  These functions don't
// set the value of ::GetLastError(), so they have to be treated special.
// Throw an exception on failure.
//
LONG
check_registry(LONG result, LPCTSTR file, UINT line, LPCTSTR context)
{
    if (ERROR_SUCCESS != result)
    {
        tostringstream buff;
        buff << file << _T("(") << line << _T("): ") << result << _T(" = ")
            << context << _T("\n");
        TCHAR msg[1024] = { 0 };
        const DWORD count = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, result, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &msg[0], NUM_OF(msg), NULL);
        if (count)
        {
            buff << _T("   '") << msg << _T("\n");
        }
        ::ODS(buff);
        throw win32_error(result, file, line, buff.str().c_str());
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
// check_hr
//
// Throw an exception on a FAILED HRESULT.
//
HRESULT
check_hr(HRESULT hr, LPCTSTR file, UINT line, LPCTSTR context)
{
    if (FAILED(hr))
    {
        tostringstream buff;
        buff << file << _T("(") << line << _T("): 0x") << std::hex
            << std::setfill(_T('0')) << std::setw(8) << hr << _T(" = ")
            << context << _T("\n");
        TCHAR msg[1024] = { 0 };
        const DWORD count = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &msg[0], NUM_OF(msg), NULL);
        if (count)
        {
            buff << _T("   '") << msg << _T("'\n");
        }
        ::ODS(buff);
        throw hresult_error(hr, file, line, buff.str().c_str());
    }
    return hr;
}

LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
    HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
    lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT

#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
    HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
    HRESULT hRes = CoInitialize(NULL);
#endif
    _ASSERTE(SUCCEEDED(hRes));
    _Module.Init(ObjectMap, hInstance, &LIBID_IZMONITORLib);
    _Module.dwThreadID = GetCurrentThreadId();
    TCHAR szTokens[] = _T("-/");

    int nRet = 0;
    BOOL bRun = TRUE;
    LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
    while (lpszToken != NULL)
    {
        if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_izMonitor, FALSE);
            nRet = _Module.UnregisterServer(TRUE);
            bRun = FALSE;
            break;
        }
        if (lstrcmpi(lpszToken, _T("RegServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_izMonitor, TRUE);
            nRet = _Module.RegisterServer(TRUE);
            bRun = FALSE;
            break;
        }
        lpszToken = FindOneOf(lpszToken, szTokens);
    }

    if (bRun)
    {
        _Module.StartMonitor();
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
        _ASSERTE(SUCCEEDED(hRes));
        hRes = CoResumeClassObjects();
#else
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE);
#endif
        _ASSERTE(SUCCEEDED(hRes));

        MSG msg;
        while (GetMessage(&msg, 0, 0, 0))
            DispatchMessage(&msg);

        _Module.RevokeClassObjects();
        Sleep(dwPause); //wait for any threads to finish
    }

    _Module.Term();
    CoUninitialize();
    return nRet;
}
