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
// ClassRecord.h : Declaration of the CClassRecord

#ifndef __CLASSRECORD_H_
#define __CLASSRECORD_H_

#include "resource.h"       // main symbols
#include "s_tables.h"

/////////////////////////////////////////////////////////////////////////////
// CClassRecord
class ATL_NO_VTABLE CClassRecord : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CClassRecord, &CLSID_ClassRecord>,
    public ISupportErrorInfo,
    public IDispatchImpl<IClassRecord, &IID_IClassRecord, &LIBID_IZMONITORLib>
{
public:
    CClassRecord() : m_record(0)    {}
    void Init(const s_class *rhs)   { m_record = rhs; }

DECLARE_NO_REGISTRY()
DECLARE_NOT_AGGREGATABLE(CClassRecord)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CClassRecord)
    COM_INTERFACE_ENTRY(IClassRecord)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IClassRecord
public:
    STDMETHOD(get_Attributes)(/*[out, retval]*/ long *pVal);
    STDMETHOD(get_Feature)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Argument)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_DefInprocHandler)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_IconIndex)(/*[out, retval]*/ long *pVal);
    STDMETHOD(get_Icon)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_FileTypeMask)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_AppId)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_ProgIdDefault)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Component)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Context)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_CLSID)(/*[out, retval]*/ BSTR *pVal);

private:
    const s_class *m_record;
};

#endif //__CLASSRECORD_H_
