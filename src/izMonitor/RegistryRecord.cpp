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
