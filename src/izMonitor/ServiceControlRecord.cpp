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
    REC_STRING_PROPERTY(m_service_control);
}

STDMETHODIMP CServiceControlRecord::get_Name(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_name);
}

STDMETHODIMP CServiceControlRecord::get_Event(LONG *pVal)
{
    REC_LONG_PROPERTY(m_event);
}

STDMETHODIMP CServiceControlRecord::get_Arguments(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_arguments);
}

STDMETHODIMP CServiceControlRecord::get_Wait(LONG *pVal)
{
    REC_LONG_PROPERTY(m_wait);
}

STDMETHODIMP CServiceControlRecord::get_Component(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_component);
}
