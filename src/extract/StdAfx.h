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

///////////////////////////////////////////////////////////////////////////
// NUM_OF -- gets the size of a fixed-size array
//
#define NUM_OF(ary_) (sizeof(ary_)/sizeof((ary_)[0]))

///////////////////////////////////////////////////////////////////////////
// tstring, tostringstream -- C++ standard library strings of TCHARs
//
typedef std::basic_string<TCHAR> tstring;
typedef std::basic_ostringstream<TCHAR> tostringstream;
typedef std::basic_istringstream<TCHAR> tistringstream;

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
    LPCTSTR m_file;
    UINT m_line;
    LPCTSTR m_msg;
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
    com_runtime() { THR(::CoInitializeEx(NULL, COINIT_MULTITHREADED)); }
    ~com_runtime() { ::CoUninitialize(); }
};

///////////////////////////////////////////////////////////////////////////
// dynamic_library -- LoadLibrary a file as a resource in c'tor
//
class dynamic_library
{
public:
    dynamic_library(LPCTSTR file);
    ~dynamic_library();
    operator HMODULE() const { return m_library; }

private:
    tstring m_file;
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

///////////////////////////////////////////////////////////////////////////
// s_monitor_key -- structure to monitor a registry key's differences
//
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
    void extract_app_id(const tstring &component) const;
    void extract_app_id_entry(const registry_key &subkey,
                              const tstring &component) const;
    void extract_class(const tstring &component) const;
    void extract_clsid_entry(const registry_key &subkey,
                             const tstring &component) const;
    void extract_prog_id(const tstring &component) const;
    void extract_prog_id_entry(const registry_key &subkey,
                               const tstring &component) const;
    void extract_registry(const tstring &component) const;
    void extract_type_lib(const tstring &component) const;
    void extract_type_lib_entry(const registry_key &subkey,
                                const tstring &component) const;

    HKEY m_key;
    tstring m_name;
    tstring m_subkey;
    bool m_modified;

    std::set<tstring> m_values;
    std::set<tstring> m_subkeys;
};

typedef std::vector<tstring> string_list_t;

///////////////////////////////////////////////////////////////////////////
// reg_monitor
//
// Self-Register a COM server and monitor the registry for changes, dumping
// them back out as Windows Installer database information.
//
class reg_monitor
{
public:
    reg_monitor(LPCTSTR file, bool servicep);
    ~reg_monitor() {}

    reg_monitor &add(HKEY key, LPCTSTR name, LPCTSTR subkey = NULL);

    void process();

private:
    tstring m_file;
    bool m_servicep;
    tstring m_component;
    std::vector<s_monitor_key> m_keys;
    std::vector<HANDLE> m_events;
    string_list_t m_services;

    static void __cdecl register_threadproc(void *pv);

    void dump_tables();
    void diff_services();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
