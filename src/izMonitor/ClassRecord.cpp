// ClassRecord.cpp : Implementation of CClassRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "ClassRecord.h"
#include "props.h"

#define PROPERTY_IID IID_IClassRecord

/////////////////////////////////////////////////////////////////////////////
// CClassRecord

STDMETHODIMP CClassRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IClassRecord
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP CClassRecord::get_CLSID(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_clsid);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_Context(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_context);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_Component(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_component);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_ProgIdDefault(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_prog_id_default);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_Description(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_description);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_AppId(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_app_id);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_FileTypeMask(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_file_type_mask);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_Icon(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_icon);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_IconIndex(long *pVal)
{
    STORE_LONG_PROPERTY(m_icon_index);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_DefInprocHandler(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_def_inproc_handler);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_Argument(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_argument);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_Feature(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_feature);
    return S_OK;
}

STDMETHODIMP CClassRecord::get_Attributes(long *pVal)
{
    STORE_LONG_PROPERTY(m_attributes);
    return S_OK;
}
