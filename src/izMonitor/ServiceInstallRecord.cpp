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
    REC_STRING_PROPERTY(m_service_install);
}

STDMETHODIMP CServiceInstallRecord::get_Name(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_name);
}

STDMETHODIMP CServiceInstallRecord::get_DisplayName(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_display_name);
}

STDMETHODIMP CServiceInstallRecord::get_ServiceType(LONG *pVal)
{
    REC_LONG_PROPERTY(m_service_type);
}

STDMETHODIMP CServiceInstallRecord::get_StartType(LONG *pVal)
{
    REC_LONG_PROPERTY(m_start_type);
}

STDMETHODIMP CServiceInstallRecord::get_ErrorControl(LONG *pVal)
{
    REC_LONG_PROPERTY(m_error_control);
}

STDMETHODIMP CServiceInstallRecord::get_LoadOrderGroup(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_load_order_group);
}

STDMETHODIMP CServiceInstallRecord::get_Dependencies(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_dependencies);
}

STDMETHODIMP CServiceInstallRecord::get_StartName(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_start_name);
}

STDMETHODIMP CServiceInstallRecord::get_Password(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_password);
}

STDMETHODIMP CServiceInstallRecord::get_Arguments(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_arguments);
}

STDMETHODIMP CServiceInstallRecord::get_Component(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_component);
}

STDMETHODIMP CServiceInstallRecord::get_Description(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_description);
}
