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
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>

#pragma warning(push)
#pragma warning(disable: 4786)
#include <algorithm>
#include <set>
#include <sstream>
#include <vector>
#pragma warning(pop)

#include <process.h>

#include <tchar.h>
#include <atlbase.h>

//-------------------------------------------------------------------------
#define NUM_OF(ary_) (sizeof(ary_)/sizeof((ary_)[0]))

//-------------------------------------------------------------------------
typedef std::basic_string<TCHAR> tstring;
typedef std::basic_ostringstream<TCHAR> tostringstream;

//-------------------------------------------------------------------------
struct thread_args
{
    LPCTSTR m_file;
    HANDLE m_event;
    bool m_servicep;
};

//-------------------------------------------------------------------------
inline void ODS(const tstring &s)          { ::OutputDebugString(s.c_str()); }
inline void ODS(const tostringstream &s)   { ::OutputDebugString(s.str().c_str()); }

//-------------------------------------------------------------------------
#define TRS(expr_) \
    check_registry((expr_), _T(__FILE__), __LINE__, _T(#expr_))
#define TWS(expr_) \
    check_win32((expr_), _T(__FILE__), __LINE__, _T(#expr_))
#define TCR(expr_) \
    check_cruntime((expr_), _T(__FILE__), __LINE__, _T(#expr_))
#define THR(expr_) \
    check_hr((expr_), _T(__FILE__), __LINE__, _T(#expr_))

//-------------------------------------------------------------------------
struct source_error
{
    source_error(LPCTSTR file, UINT line, LPCTSTR msg)
        : m_file(file), m_line(line), m_msg(msg) {}
    LPCTSTR m_file;
    UINT m_line;
    LPCTSTR m_msg;
};

//-------------------------------------------------------------------------
struct win32_error : source_error
{
    win32_error(DWORD result, LPCTSTR file, UINT line, LPCTSTR msg)
        : m_result(result), source_error(file, line, msg) {}
    DWORD m_result;
};

//-------------------------------------------------------------------------
struct crt_error : source_error
{
    crt_error(unsigned long result, LPCTSTR file, UINT line, LPCTSTR msg)
        : m_result(result), source_error(file, line, msg) {}
    unsigned long m_result;
};

//-------------------------------------------------------------------------
struct hresult_error : source_error
{
    hresult_error(HRESULT hr, LPCTSTR file, UINT line, LPCTSTR msg)
        : m_hr(hr), source_error(file, line, msg) {}
    HRESULT m_hr;
};

//-------------------------------------------------------------------------
template <typename T>
T
check_win32(T result, LPCTSTR file, UINT line, LPCTSTR context)
{
    if (!result)
    {
        tostringstream buff;
        buff << file << _T("(") << line << _T("): ") << context << _T("\n");
        const DWORD last = ::GetLastError();
        if (last)
        {
            TCHAR msg[1024] = { 0 };
            const DWORD count = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                NULL, ::GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                &msg[0], NUM_OF(msg), NULL);
            if (count)
            {
                buff << _T("   '") << msg << _T("\n");
            }
        }
        ::ODS(buff);
        throw win32_error((DWORD) result, file, line, context);
    }
    return result;
}

//-------------------------------------------------------------------------
template <typename T>
T
check_cruntime(T result, LPCTSTR file, UINT line, LPCTSTR context)
{
    if (-1 == result)
    {
        tostringstream buff;
        buff << file << _T("(") << line << _T("): ") << context << _T("\n");
        if (errno && (errno <= _sys_nerr))
        {
            USES_CONVERSION;
            buff << _T("   '") << A2T(strerror(errno)) << _T("\n");
        }
        ::ODS(buff);
        throw crt_error(result, file, line, context);
    }
    return result;
}

//-------------------------------------------------------------------------
LONG
check_registry(LONG result, LPCTSTR file, UINT line, LPCTSTR context);
HRESULT
check_hr(HRESULT hr, LPCTSTR file, UINT line, LPCTSTR context);


//-------------------------------------------------------------------------
class reg_override
{
public:
    reg_override(HKEY key, LPCTSTR redirect)
        : m_key(key),
        m_redirect()
    {
        ::SetLastError(0);
        TRS(m_redirect.Create(HKEY_LOCAL_MACHINE, redirect));
        TRS(::RegOverridePredefKey(m_key, m_redirect));
    }

    ~reg_override()
    {
        LONG res = ::RegOverridePredefKey(m_key, NULL);
        ATLASSERT(ERROR_SUCCESS == res);
        res = m_redirect.Close();
        ATLASSERT(ERROR_SUCCESS == res);
    }

    HKEY redirect() const { return m_redirect; }
    HKEY key() const { return m_key; }

private:
    HKEY m_key;
    CRegKey m_redirect;
};

//-------------------------------------------------------------------------
class com_runtime
{
public:
    com_runtime() { THR(::CoInitializeEx(NULL, COINIT_MULTITHREADED)); }
    ~com_runtime() { ::CoUninitialize(); }
};

//-------------------------------------------------------------------------
class dynamic_library
{
public:
    dynamic_library(LPCTSTR file);
    ~dynamic_library();
    operator HMODULE() const;
private:
    tstring m_file;
    HMODULE m_library;
};

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
class windows_service
{
public:
    windows_service(SC_HANDLE scm, LPCTSTR name, DWORD access = GENERIC_READ)
        : m_name(name),
        m_service(TWS(::OpenService(scm, name, access)))
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
    tstring m_name;
};

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
struct s_monitor_key
{
    s_monitor_key()
        : m_key(NULL),
        m_name(),
        m_subkey(),
        m_modified(false),
        m_values(),
        m_subkeys()
    {}
    s_monitor_key(HKEY root, LPCTSTR name, LPCTSTR subkey = NULL)
        : m_key(root),
        m_name(name),
        m_subkey(subkey ? subkey : ""),
        m_modified(false),
        m_values(),
        m_subkeys()
    {}
    ~s_monitor_key() {}

    void snapshot();
    void diff();

    HKEY m_key;
    tstring m_name;
    tstring m_subkey;
    bool m_modified;

    std::set<tstring> m_values;
    std::set<tstring> m_subkeys;
};

typedef std::vector<tstring> string_list_t;

//-------------------------------------------------------------------------
class reg_monitor
{
public:
    reg_monitor(LPCTSTR file, bool servicep);
    ~reg_monitor();

    reg_monitor &add(HKEY key, LPCTSTR name, LPCTSTR subkey = NULL);

    void process();

private:
    tstring m_file;
    bool m_servicep;
    std::vector<s_monitor_key> m_keys;
    std::vector<HANDLE> m_events;
    std::set<tstring> m_values;
    std::set<tstring> m_subkeys;

    static void __cdecl register_threadproc(void *pv);

    void snapshot(const s_monitor_key &key);
    void dump_tables(const string_list_t &services);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
