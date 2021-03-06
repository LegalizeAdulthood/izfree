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
// TypeLibRecord.cpp : Implementation of CTypeLibRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "TypeLibRecord.h"
#include "props.h"

#define PROPERTY_IID IID_ITypeLibRecord

/////////////////////////////////////////////////////////////////////////////
// CTypeLibRecord

STDMETHODIMP CTypeLibRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_ITypeLibRecord
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP CTypeLibRecord::get_LibID(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_lib_id);
}

STDMETHODIMP CTypeLibRecord::get_Language(LONG *pVal)
{
    REC_LONG_PROPERTY(m_language);
}

STDMETHODIMP CTypeLibRecord::get_Component(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_component);
}

STDMETHODIMP CTypeLibRecord::get_Version(LONG *pVal)
{
    REC_LONG_PROPERTY(m_version);
}

STDMETHODIMP CTypeLibRecord::get_Description(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_description);
}

STDMETHODIMP CTypeLibRecord::get_Directory(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_directory);
}

STDMETHODIMP CTypeLibRecord::get_Feature(BSTR *pVal)
{
    REC_STRING_PROPERTY(m_feature);
}

STDMETHODIMP CTypeLibRecord::get_Cost(LONG *pVal)
{
    REC_LONG_PROPERTY(m_cost);
}
