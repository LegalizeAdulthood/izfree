// test.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <iomanip>
#include <sstream>

#include <tchar.h>

#include <atlbase.h>

#import "../guidgen.tlb" no_namespace named_guids raw_interfaces_only

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
        THR(generator.CoCreateInstance(L"Guidgen.Generator"));

        CComBSTR guid;
        THR(generator->Generate(&guid));
        USES_CONVERSION;
        ::OutputDebugString(W2T(guid));
    }
    catch (const HResult &bang)
    {
        return bang;
    }

	return 0;
}



