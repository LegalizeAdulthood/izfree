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

#include <fstream>
#include <iomanip>
#include <ios>
#include <sstream>
#include <vector>

#include <shellapi.h>
#include <tchar.h>

///////////////////////////////////////////////////////////////////////////
// VXD_VERSION_RESOURCE
//
// Resource structure embedded within a VXD file
//
#pragma pack(push, 1)
// this structure must be byte-aligned
struct VXD_VERSION_RESOURCE
{
    char cType;
    WORD wID;
    char cName;
    WORD wOrdinal;
    WORD wFlags;
    DWORD dwResSize;
    BYTE bVerData;
};
#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////
// NUM_OF() -- return size of fixed-size array
//
#define NUM_OF(ary_) (sizeof(ary_)/sizeof((ary_)[0]))

///////////////////////////////////////////////////////////////////////////
// tstring, tostringstream -- TCHAR string helpers
//
typedef std::basic_string<TCHAR> tstring;
typedef std::basic_ostringstream<TCHAR> tostringstream;

tstring error_message(DWORD error = ::GetLastError());

///////////////////////////////////////////////////////////////////////////
// e_failure -- structure to hold error context information.
//
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

///////////////////////////////////////////////////////////////////////////
// check_win32
//
// Check the return value from a Win32 function for error.
//
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

///////////////////////////////////////////////////////////////////////////
// TWS -- Throw on Win32 Status
//
#define TWS(expr_) check_win32(expr_, _T(__FILE__), __LINE__, _T(#expr_))

///////////////////////////////////////////////////////////////////////////
// library
//
// Dynamic library resource wrapper.
//
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

///////////////////////////////////////////////////////////////////////////
// error_message -- format an error message from the system
//
tstring
error_message(DWORD error)
{
    TCHAR buffer[2048] = { 0 };
    ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, NUM_OF(buffer),
        NULL);
    return buffer;
}

///////////////////////////////////////////////////////////////////////////
// version_resource -- return a the version number from a VS_FIXEDFILEINFO
//
tstring
version_resource(void *block)
{
    // Yse the ANSI version here, as VXDs only have ANSI resources
    VS_FIXEDFILEINFO *ffi = 0;
    LPSTR sub_block = "\\";
    UINT len = 0;
    TWS(::VerQueryValueA(block, sub_block, reinterpret_cast<void **>(&ffi),
        &len));

    tostringstream version;
    version << ((ffi->dwFileVersionMS >> 16) & 0xFFFF) << _T(".")
        << (ffi->dwFileVersionMS & 0xFFFF) << _T(".")
        << ((ffi->dwFileVersionLS >> 16) & 0xFFFF) << _T(".")
        << (ffi->dwFileVersionLS & 0xFFFF);
    return version.str();
}

///////////////////////////////////////////////////////////////////////////
// TEST_FALSE -- test an expression, and if false return the empty string
//
#define TEST_FALSE(expr_)   \
    if (!(expr_))           \
    {                       \
        return _T("");      \
    } else 0

///////////////////////////////////////////////////////////////////////////
// file_version
//
// Extract the version number resource as a tstring.  First, open the
// file and examine its magic number information to determine if its
// a file starting 
//
tstring
file_version(const tstring &filename)
{
    try
    {
        USES_CONVERSION;
        std::ifstream file(T2CA(filename.c_str()),
            std::ios_base::in | std::ios_base::binary);
        TEST_FALSE(file);

        // first, check for the DOS header at the front
        IMAGE_DOS_HEADER dos = { 0 };
        TEST_FALSE(file.read(reinterpret_cast<char *>(&dos), sizeof(dos)));
        TEST_FALSE(IMAGE_DOS_SIGNATURE == dos.e_magic);

        // now look for the PE header that follows
        IMAGE_NT_HEADERS nt = { 0 };
        TEST_FALSE(file.seekg(dos.e_lfanew, std::ios_base::beg));
        TEST_FALSE(file.read(reinterpret_cast<char *>(&nt), sizeof(nt)));
        if (IMAGE_NT_SIGNATURE == nt.Signature)
        {
            file.close();
            LPTSTR file_arg = const_cast<LPTSTR>(filename.c_str());
            std::vector<BYTE> buff(::GetFileVersionInfoSize(file_arg, 0));
            TWS(::GetFileVersionInfo(file_arg, NULL, buff.size(), &buff[0]));
            return version_resource(&buff[0]);
        }

        // ok, its a valid executable, but not a PE executable
        TEST_FALSE(IMAGE_VXD_SIGNATURE == nt.Signature);

        // its a VXD file, get the VXD version number
        const IMAGE_VXD_HEADER *vxd =
            reinterpret_cast<IMAGE_VXD_HEADER *>(&nt);
        TEST_FALSE(vxd->e32_winreslen != 0);
        TEST_FALSE(file.seekg(vxd->e32_winresoff, std::ios_base::beg));
        std::vector<char> buff(vxd->e32_winreslen);
        TEST_FALSE(file.read(&buff[0], buff.size()));
        VXD_VERSION_RESOURCE *vxd_ver =
            reinterpret_cast<VXD_VERSION_RESOURCE *>(&buff[0]);
        return version_resource(&vxd_ver->bVerData);
    }
    catch (...)
    {
        // fall through
    }
    return _T("");
}

/////////////////////////////////////////////////////////////////////////////
// CFileVersion::get_Version
//
// Return the file version from a PE executable or VXD executable, otherwise
// return the empty string.
//
STDMETHODIMP
CFileVersion::get_Version(BSTR file, BSTR *pVal)
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
