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
// test.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <iomanip>
#include <sstream>

#include <tchar.h>

#include <atlbase.h>

#import "../guidgen.tlb" no_namespace named_guids raw_interfaces_only

typedef std::basic_string<TCHAR> tstring;
typedef std::basic_ostringstream<TCHAR> tostringstream;

class HResult
{
public:
    HResult(HRESULT hr) : m_hr(hr) {}
    ~HResult() {}

    operator HRESULT() const { return m_hr; }
private:
    HRESULT m_hr;
};

HRESULT
check_hr(HRESULT hr, LPCTSTR file, UINT line)
{
    if (FAILED(hr))
    {
        tostringstream buff;
        buff << file << _T("(") << line << _T(")")
            << _T(": Unexpected failure HRESULT 0x")
            << std::setw(8) << std::setfill(_T('0')) << std::hex
            << hr << _T("\n");
        ::OutputDebugString(buff.str().c_str());

        throw HResult(hr);
    }
    return hr;
}

#define THR(hr_) check_hr(hr_, _T(__FILE__), __LINE__)

class ComRuntime
{
public:
    ComRuntime()
    {
        THR(::CoInitialize(NULL));
    }
    ~ComRuntime()
    {
        ::CoUninitialize();
    }
};

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    try
    {
        ComRuntime com;

        CComPtr<IGenerator> generator;
        THR(generator.CoCreateInstance(L"izfree.Guidgen"));

        CComBSTR guid;
        THR(generator->Generate(&guid));
        USES_CONVERSION;
        ::OutputDebugString((_T("izfree.Guidgen: ") + tstring(W2T(guid)) +
            _T("\n")).c_str());

        CComPtr<IFileVersion> fv;
        THR(fv.CoCreateInstance(L"izfree.FileVersion"));
        CComBSTR version;
        CComBSTR file(L"C:\\winnt\\system32\\atiicdxx.vxd");
        THR(fv->get_Version(file, &version));
        ::OutputDebugString((_T("izfree.FileVersion: ") +
            tstring(W2T(version)) + _T("\n")).c_str());
    }
    catch (const HResult &bang)
    {
        return bang;
    }

	return 0;
}



