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
// FileVersion.cpp : Implementation of CFileVersion
#include "stdafx.h"
#include "Guidgen.h"
#include "FileVersion.h"

#include <sstream>
#include <iomanip>
#include <vector>

#include <shellapi.h>
#include <tchar.h>

#define NUM_OF(ary_) (sizeof(ary_)/sizeof((ary_)[0]))

typedef std::basic_string<TCHAR> tstring;
typedef std::basic_ostringstream<TCHAR> tostringstream;

/////////////////////////////////////////////////////////////////////////////
// CFileVersion

tstring error_message(DWORD error = ::GetLastError());

struct e_failure
{
    e_failure(const tstring &file, UINT line, const tstring &context,
            DWORD error, const tstring &message) :
    m_file(file), m_line(line), m_context(context),
    m_error(error), m_message(message) {}

    tstring m_file;
    UINT m_line;
    tstring m_context;
    DWORD m_error;
    tstring m_message;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
T
check_win32(T expr, LPCTSTR file, UINT line, LPCTSTR context)
{
    if (!expr)
    {
        tostringstream buff;
        buff << file << _T("(") << line << _T("): ") << context << _T("\n");
        ::OutputDebugString(buff.str().c_str());
        DWORD error = ::GetLastError();
        throw e_failure(file, line, context, error, error_message(error));
    }
    return expr;
}

////////////////////////////////////////////////////////////////////////////////
#define TWS(expr_) check_win32(expr_, _T(__FILE__), __LINE__, _T(#expr_))

////////////////////////////////////////////////////////////////////////////////
struct VS_VERSIONINFO
{
    WORD wLength;
    WORD wValueLength;
    WORD wType;
    WCHAR szKey[16];
    VS_FIXEDFILEINFO Value;
    WORD Padding;
    WORD Children;
};

class library
{
public:
    library(const tstring &file)
        : m_handle(TWS(::LoadLibrary(file.c_str())))
    {}
    ~library()
    {
        const BOOL result = ::FreeLibrary(m_handle);
        ATLASSERT(result);
    }
    operator HMODULE() const { return m_handle; }
private:
    HMODULE m_handle;
};

////////////////////////////////////////////////////////////////////////////////
tstring
error_message(DWORD error)
{
    TCHAR buffer[2048] = { 0 };
    ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, NUM_OF(buffer),
        NULL);
    return buffer;
}

////////////////////////////////////////////////////////////////////////////////
tstring
file_version(tstring file)
{
    try
    {
        library module(file);
        TCHAR filename[MAX_PATH] = { 0 };
        TWS(::GetModuleFileName(module, filename, NUM_OF(filename)));
        std::vector<BYTE> buff(::GetFileVersionInfoSize(filename, 0));
        TWS(::GetFileVersionInfo(filename, NULL, buff.size(), &buff[0]));
        const VS_FIXEDFILEINFO &ffi =
            reinterpret_cast<VS_VERSIONINFO *>(&buff[0])->Value;

        tostringstream version;
        version << ((ffi.dwFileVersionMS >> 16) & 0xFFFF) << _T(".")
            << (ffi.dwFileVersionMS & 0xFFFF) << _T(".")
            << ((ffi.dwFileVersionLS >> 16) & 0xFFFF) << _T(".")
            << (ffi.dwFileVersionLS & 0xFFFF);
        return version.str();
    }
    catch (...)
    {
        return _T("0.0");
    }
}

STDMETHODIMP CFileVersion::get_Version(BSTR file, BSTR *pVal)
{
    if (!pVal)
    {
        return Error(_T("A NULL pointer was passed for an output argument."),
                     IID_IFileVersion, E_POINTER);
    }
    USES_CONVERSION;
    *pVal = CComBSTR(file_version(W2T(file)).c_str()).Detach();

	return S_OK;
}
