// ServiceInstallRecord.cpp : Implementation of CServiceInstallRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "ServiceInstallRecord.h"
#include "props.h"

#define PROPERTY_IID IID_IServiceInstallRecord

/////////////////////////////////////////////////////////////////////////////
// CServiceInstallRecord

STDMETHODIMP CServiceInstallRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IServiceInstallRecord
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP CServiceInstallRecord::get_ServiceInstall(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_service_install);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Name(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_name);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_DisplayName(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_display_name);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_ServiceType(LONG *pVal)
{
    STORE_LONG_PROPERTY(m_service_type);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_StartType(LONG *pVal)
{
    STORE_LONG_PROPERTY(m_start_type);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_ErrorControl(LONG *pVal)
{
    STORE_LONG_PROPERTY(m_error_control);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_LoadOrderGroup(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_load_order_group);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Dependencies(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_dependencies);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_StartName(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_start_name);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Password(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_password);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Arguments(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_arguments);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Component(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_component);
    return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Description(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_description);
    return S_OK;
}
