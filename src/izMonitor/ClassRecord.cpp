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
    REC_STRING_PROPERTY(m_clsid);
}

STDMETHODIMP CClassRecord::get_Context(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_context);
}

STDMETHODIMP CClassRecord::get_Component(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_component);
}

STDMETHODIMP CClassRecord::get_ProgIdDefault(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_prog_id_default);
}

STDMETHODIMP CClassRecord::get_Description(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_description);
}

STDMETHODIMP CClassRecord::get_AppId(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_app_id);
}

STDMETHODIMP CClassRecord::get_FileTypeMask(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_file_type_mask);
}

STDMETHODIMP CClassRecord::get_Icon(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_icon);
}

STDMETHODIMP CClassRecord::get_IconIndex(long *pVal)
{
    REC_LONG_PROPERTY(m_icon_index);
}

STDMETHODIMP CClassRecord::get_DefInprocHandler(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_def_inproc_handler);
}

STDMETHODIMP CClassRecord::get_Argument(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_argument);
}

STDMETHODIMP CClassRecord::get_Feature(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_feature);
}

STDMETHODIMP CClassRecord::get_Attributes(long *pVal)
{
    REC_LONG_PROPERTY(m_attributes);
}
