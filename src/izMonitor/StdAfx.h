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
// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__086297EB_478C_4D58_BCD2_403A59177EFF__INCLUDED_)
#define AFX_STDAFX_H__086297EB_478C_4D58_BCD2_403A59177EFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CExeModule : public CComModule
{
public:
    LONG Unlock();
    DWORD dwThreadID;
    HANDLE hEventShutdown;
    void MonitorShutdown();
    bool StartMonitor();
    bool bActivity;
};
extern CExeModule _Module;
#include <atlcom.h>

#include "tstring.h"

///////////////////////////////////////////////////////////////////////////
// cis_equal -- case-insensitive string equality predicate
//
inline bool
cis_equal(LPCTSTR lhs, const tstring &rhs)
{
    return (_tcslen(lhs) == rhs.size()) && (_tcsicmp(lhs, rhs.c_str()) == 0);
}
inline bool
cis_equal(const tstring &lhs, const tstring &rhs)
{
    return cis_equal(lhs.c_str(), rhs);
}

#pragma warning(push)
#pragma warning(disable: 4786)
#include <algorithm>
#include <set>
#include <sstream>
#include <vector>
#pragma warning(pop)

#include <process.h>

///////////////////////////////////////////////////////////////////////////
// NUM_OF -- gets the size of a fixed-size array
//
#define NUM_OF(ary_) (sizeof(ary_)/sizeof((ary_)[0]))

///////////////////////////////////////////////////////////////////////////
// thread_args -- structure containing arguments passed to registration thread
//
struct thread_args;

class registry_key;

///////////////////////////////////////////////////////////////////////////
// ODS -- ::OutputDebugString shortcut for tstrings
//
inline void ODS(const tstring &s)          { ::OutputDebugString(s.c_str()); }
inline void ODS(const tostringstream &s)   { ::OutputDebugString(s.str().c_str()); }

///////////////////////////////////////////////////////////////////////////
// TRS, TWS, TCR, THR
//
// check registry, win32, C runtime and HRESULTs for failure and throw when
// they fail with a meaningful context message.
//
#define TRS(expr_) \
    check_registry((expr_), _T(__FILE__), __LINE__, _T(#expr_))
#define TWS(expr_) \
    check_win32((expr_), _T(__FILE__), __LINE__, _T(#expr_))
#define TCR(expr_) \
    check_cruntime((expr_), _T(__FILE__), __LINE__, _T(#expr_))
#define THR(expr_) \
    check_hr((expr_), _T(__FILE__), __LINE__, _T(#expr_))

///////////////////////////////////////////////////////////////////////////
// source_error
//
// Structure holding source file context information for an unexpected error.
//
struct source_error
{
    source_error(LPCTSTR file, UINT line, LPCTSTR msg)
        : m_file(file), m_line(line), m_msg(msg) {}
    tstring m_file;
    UINT m_line;
    tstring m_msg;
};

///////////////////////////////////////////////////////////////////////////
// win32_error -- source error context and a Win32 return value
//
struct win32_error : source_error
{
    win32_error(DWORD result, LPCTSTR file, UINT line, LPCTSTR msg)
        : m_result(result), source_error(file, line, msg) {}
    DWORD m_result;
};

///////////////////////////////////////////////////////////////////////////
// crt_error -- source error context and a C runtime return value
//
struct crt_error : source_error
{
    crt_error(unsigned long result, LPCTSTR file, UINT line, LPCTSTR msg)
        : m_result(result), source_error(file, line, msg) {}
    unsigned long m_result;
};

///////////////////////////////////////////////////////////////////////////
// hresult_error -- source error context and an HRESULT
//
struct hresult_error : source_error
{
    hresult_error(HRESULT hr, LPCTSTR file, UINT line, LPCTSTR msg)
        : m_hr(hr), source_error(file, line, msg) {}
    HRESULT m_hr;
};

///////////////////////////////////////////////////////////////////////////
// check_win32
//
// Check the return value of a Win32 function for failure and throw when
// it fails.  This needs to be a template typename to work with functions
// that return GDI opaque pointers or NULL.
//
template <typename T>
T
check_win32(T result, LPCTSTR file, UINT line, LPCTSTR context)
{
    if (!result)
    {
        const DWORD last = ::GetLastError();
        tostringstream buff;
        buff << file << _T("(") << line << _T("): ")
            << *reinterpret_cast<DWORD *>(&result) << _T(" = ")
            << context << _T("; GetLastError() = ") << last << _T("\n");
        if (last)
        {
            TCHAR msg[1024] = { 0 };
            const DWORD count = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                NULL, last, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                &msg[0], NUM_OF(msg), NULL);
            if (count)
            {
                buff << _T("   '") << msg << _T("\n");
            }
        }
        ::ODS(buff);
        throw win32_error((DWORD) result, file, line, buff.str().c_str());
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
// check_cruntime
//
// Check the return value of a C runtime function for failure, indicated by
// -1, and throw an exception when it fails.
//
template <typename T>
T
check_cruntime(T result, LPCTSTR file, UINT line, LPCTSTR context)
{
    if (-1 == result)
    {
        tostringstream buff;
        buff << file << _T("(") << line << _T("): ")
            << *reinterpret_cast<DWORD *>(&result) << _T(" = ") << context
            << _T("; errno = ") << errno << _T("\n");
        if (errno && (errno <= _sys_nerr))
        {
            USES_CONVERSION;
            buff << _T("   '") << A2T(strerror(errno)) << _T("\n");
        }
        ::ODS(buff);
        throw crt_error(result, file, line, buff.str().c_str());
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
// check_registry, check_hr
//
// Checks the return values of registry API functions and functions that
// return HRESULT.  Throws on failure.
//
LONG
check_registry(LONG result, LPCTSTR file, UINT line, LPCTSTR context);
HRESULT
check_hr(HRESULT hr, LPCTSTR file, UINT line, LPCTSTR context);

///////////////////////////////////////////////////////////////////////////
// com_runtime -- acquire the COM runtime as a resource in c'tor
//
class com_runtime
{
public:
    com_runtime()   { THR(::CoInitialize(NULL)); }
    ~com_runtime()  { ::CoUninitialize(); }
};

///////////////////////////////////////////////////////////////////////////
// dynamic_library -- LoadLibrary a file as a resource in c'tor
//
class dynamic_library
{
public:
    dynamic_library(LPCTSTR file)
        : m_library(TWS(::LoadLibrary(file)))
    {
    }
    dynamic_library(const tstring &file)
        : m_library(TWS(::LoadLibrary(file.c_str())))
    {
    }
    ~dynamic_library()
    {
        const BOOL res = ::FreeLibrary(m_library);
        ATLASSERT(res);
    }
    operator HMODULE() const { return m_library; }

private:
    HMODULE m_library;
};

///////////////////////////////////////////////////////////////////////////
// windows_service_manager -- acquire a SCM handle as a resource in c'tor
//
class windows_service_manager
{
public:
    windows_service_manager(DWORD access =
            GENERIC_READ | SC_MANAGER_LOCK | SC_MANAGER_ENUMERATE_SERVICE)
        : m_scm(TWS(::OpenSCManager(NULL, NULL, access)))
    {
    }
    ~windows_service_manager()
    {
        const BOOL res = ::CloseServiceHandle(m_scm);
        ATLASSERT(res);
    }
    operator SC_HANDLE() { return m_scm; }

private:
    SC_HANDLE m_scm;
};

///////////////////////////////////////////////////////////////////////////
// windows_service -- acquire a service's handle as a resource in c'tor
//
class windows_service
{
public:
    windows_service(SC_HANDLE scm, const tstring &name,
                    DWORD access = GENERIC_READ)
        : m_service(TWS(::OpenService(scm, name.c_str(), access)))
    {
    }
    ~windows_service()
    {
        const BOOL res = ::CloseServiceHandle(m_service);
        ATLASSERT(res);
    }
    operator SC_HANDLE() { return m_service; }

private:
    SC_HANDLE m_service;
};

///////////////////////////////////////////////////////////////////////////
// scm_lock -- acquire a SCM lock as a resource in c'tor
//
class scm_lock
{
public:
    scm_lock(windows_service_manager &scm)
        : m_lock(TWS(::LockServiceDatabase(scm)))
    {
    }
    ~scm_lock()
    {
        const BOOL res = ::UnlockServiceDatabase(m_lock);
        ATLASSERT(res);
    }
private:
    SC_LOCK m_lock;
};

typedef std::vector<tstring> string_list_t;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__086297EB_478C_4D58_BCD2_403A59177EFF__INCLUDED)
