// ServiceControlRecord.cpp : Implementation of CServiceControlRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "ServiceControlRecord.h"
#include "props.h"

#define PROPERTY_IID IID_IServiceControlRecord

/////////////////////////////////////////////////////////////////////////////
// CServiceControlRecord

STDMETHODIMP CServiceControlRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IServiceControlRecord
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP CServiceControlRecord::get_ServiceControl(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_service_control);
    return S_OK;
}

STDMETHODIMP CServiceControlRecord::get_Name(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_name);
    return S_OK;
}

STDMETHODIMP CServiceControlRecord::get_Event(LONG *pVal)
{
    STORE_LONG_PROPERTY(m_event);
    return S_OK;
}

STDMETHODIMP CServiceControlRecord::get_Arguments(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_arguments);
    return S_OK;
}

STDMETHODIMP CServiceControlRecord::get_Wait(LONG *pVal)
{
    STORE_LONG_PROPERTY(m_wait);
    return S_OK;
}

STDMETHODIMP CServiceControlRecord::get_Component(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_component);
    return S_OK;
}
