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
// TypeLibRecord.h : Declaration of the CTypeLibRecord

#ifndef __TYPELIBRECORD_H_
#define __TYPELIBRECORD_H_

#include "resource.h"       // main symbols
#include "s_tables.h"

/////////////////////////////////////////////////////////////////////////////
// CTypeLibRecord
class ATL_NO_VTABLE CTypeLibRecord : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CTypeLibRecord, &CLSID_TypeLibRecord>,
    public ISupportErrorInfo,
    public IDispatchImpl<ITypeLibRecord, &IID_ITypeLibRecord, &LIBID_IZMONITORLib>
{
public:
    CTypeLibRecord()                    {}
    void Init(const s_type_lib *record) { m_record = record; }

DECLARE_NO_REGISTRY()
DECLARE_NOT_AGGREGATABLE(CTypeLibRecord)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTypeLibRecord)
    COM_INTERFACE_ENTRY(ITypeLibRecord)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITypeLibRecord
public:
    STDMETHOD(get_Cost)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_Feature)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Directory)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Version)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_Component)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Language)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_LibID)(/*[out, retval]*/ BSTR *pVal);

private:
    const s_type_lib *m_record;
};

#endif //__TYPELIBRECORD_H_
