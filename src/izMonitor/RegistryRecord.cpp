// RegistryRecord.cpp : Implementation of CRegistryRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "RegistryRecord.h"
#include "props.h"

#define PROPERTY_IID IID_IRegistryRecord

/////////////////////////////////////////////////////////////////////////////
// CRegistryRecord

STDMETHODIMP CRegistryRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IRegistryRecord
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP CRegistryRecord::get_Registry(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_registry);
    return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Root(LONG *pVal)
{
    STORE_LONG_PROPERTY(m_root);
    return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Key(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_key);
    return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Name(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_name);
    return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Value(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_value);
    return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Component(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_component);
    return S_OK;
}
