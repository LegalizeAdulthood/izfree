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
// ProgIdRecord.cpp : Implementation of CProgIdRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "ProgIdRecord.h"
#include "props.h"

#define PROPERTY_IID IID_IProgIdRecord

/////////////////////////////////////////////////////////////////////////////
// CProgIdRecord

STDMETHODIMP CProgIdRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IProgIdRecord
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP CProgIdRecord::get_ProgId(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_prog_id);
    return S_OK;
}

STDMETHODIMP CProgIdRecord::get_Parent(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_prog_id_parent);
    return S_OK;
}

STDMETHODIMP CProgIdRecord::get_Class(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_class);
    return S_OK;
}

STDMETHODIMP CProgIdRecord::get_Description(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_description);
    return S_OK;
}

STDMETHODIMP CProgIdRecord::get_Icon(BSTR *pVal)
{
    STORE_STRING_PROPERTY(m_icon);
    return S_OK;
}

STDMETHODIMP CProgIdRecord::get_IconIndex(LONG *pVal)
{
    STORE_LONG_PROPERTY(m_icon_index);
    return S_OK;
}
