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
// ProgIdRecord.h : Declaration of the CProgIdRecord

#ifndef __PROGIDRECORD_H_
#define __PROGIDRECORD_H_

#include "resource.h"       // main symbols
#include "s_tables.h"

/////////////////////////////////////////////////////////////////////////////
// CProgIdRecord
class ATL_NO_VTABLE CProgIdRecord : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CProgIdRecord, &CLSID_ProgIdRecord>,
    public ISupportErrorInfo,
    public IDispatchImpl<IProgIdRecord, &IID_IProgIdRecord, &LIBID_IZMONITORLib>
{
public:
    CProgIdRecord() : m_record(0)       {}
    void Init(const s_prog_id *record)  { m_record = record; }

DECLARE_NO_REGISTRY()
DECLARE_NOT_AGGREGATABLE(CProgIdRecord)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProgIdRecord)
    COM_INTERFACE_ENTRY(IProgIdRecord)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IProgIdRecord
public:
    STDMETHOD(get_IconIndex)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_Icon)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Class)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Parent)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_ProgId)(/*[out, retval]*/ BSTR *pVal);

private:
    const s_prog_id *m_record;
};

#endif //__PROGIDRECORD_H_
