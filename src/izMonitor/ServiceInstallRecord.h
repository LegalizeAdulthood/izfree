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
// ServiceInstallRecord.h : Declaration of the CServiceInstallRecord

#ifndef __SERVICEINSTALLRECORD_H_
#define __SERVICEINSTALLRECORD_H_

#include "resource.h"       // main symbols
#include "s_tables.h"

/////////////////////////////////////////////////////////////////////////////
// CServiceInstallRecord
class ATL_NO_VTABLE CServiceInstallRecord : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CServiceInstallRecord, &CLSID_ServiceInstallRecord>,
    public ISupportErrorInfo,
    public IDispatchImpl<IServiceInstallRecord, &IID_IServiceInstallRecord, &LIBID_IZMONITORLib>
{
public:
    CServiceInstallRecord() : m_record(0)       {}
    void Init(const s_service_install *record)  { m_record = record; }

DECLARE_NO_REGISTRY()
DECLARE_NOT_AGGREGATABLE(CServiceInstallRecord)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CServiceInstallRecord)
    COM_INTERFACE_ENTRY(IServiceInstallRecord)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IServiceInstallRecord
public:
    STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Component)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Arguments)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Password)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_StartName)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Dependencies)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_LoadOrderGroup)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_ErrorControl)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_StartType)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_ServiceType)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_DisplayName)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_ServiceInstall)(/*[out, retval]*/ BSTR *pVal);

private:
    const s_service_install *m_record;
};

#endif //__SERVICEINSTALLRECORD_H_
