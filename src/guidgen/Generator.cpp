// Generator.cpp : Implementation of CGenerator
#include "stdafx.h"
#include "Guidgen.h"
#include "Generator.h"

/////////////////////////////////////////////////////////////////////////////
// CGenerator

#define NUM_OF(ary_) (sizeof(ary_)/sizeof((ary_)[0]))

STDMETHODIMP CGenerator::Generate(BSTR *guid)
{
    if (!guid)
    {
        return E_POINTER;
    }

    GUID g = { 0 };
    const HRESULT hr = ::CoCreateGuid(&g);
    if (FAILED(hr))
    {
        return hr;
    }
    OLECHAR buffer[80];
    if (!::StringFromGUID2(g, buffer, NUM_OF(buffer)))
    {
        return E_INVALIDARG;
    }
    *guid = CComBSTR(buffer).Detach();

	return S_OK;
}
