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
// ServiceControlRecord.h : Declaration of the CServiceControlRecord

#ifndef __SERVICECONTROLRECORD_H_
#define __SERVICECONTROLRECORD_H_

#include "resource.h"       // main symbols
#include "s_tables.h"

/////////////////////////////////////////////////////////////////////////////
// CServiceControlRecord
class ATL_NO_VTABLE CServiceControlRecord : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CServiceControlRecord, &CLSID_ServiceControlRecord>,
    public ISupportErrorInfo,
    public IDispatchImpl<IServiceControlRecord, &IID_IServiceControlRecord, &LIBID_IZMONITORLib>
{
public:
    CServiceControlRecord() : m_record(0)       {}
    void Init(const s_service_control *record)  { m_record = record; }

DECLARE_NO_REGISTRY()
DECLARE_NOT_AGGREGATABLE(CServiceControlRecord)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CServiceControlRecord)
    COM_INTERFACE_ENTRY(IServiceControlRecord)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IServiceControlRecord
public:
    STDMETHOD(get_Component)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Wait)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_Arguments)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Event)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_ServiceControl)(/*[out, retval]*/ BSTR *pVal);

private:
    const s_service_control *m_record;
};

#endif //__SERVICECONTROLRECORD_H_
