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
// AppIdRecord.h : Declaration of the CAppIdRecord

#ifndef __APPIDRECORD_H_
#define __APPIDRECORD_H_

#include "resource.h"       // main symbols
#include "s_tables.h"

/////////////////////////////////////////////////////////////////////////////
// CAppIdRecord
class ATL_NO_VTABLE CAppIdRecord : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAppIdRecord, &CLSID_AppIdRecord>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAppIdRecord, &IID_IAppIdRecord, &LIBID_IZMONITORLib>
{
public:
    CAppIdRecord();
    void Init(const s_app_id &app_id);

DECLARE_REGISTRY_RESOURCEID(IDR_APPIDRECORD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAppIdRecord)
	COM_INTERFACE_ENTRY(IAppIdRecord)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAppIdRecord
public:
	STDMETHOD(get_RunAsInteractiveUser)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_ActivateAtStorage)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_DllSurrogate)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ServiceParameters)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_LocalService)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_RemoteServerName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_AppId)(/*[out, retval]*/ BSTR *pVal);

private:
    s_app_id m_app_id;
};

#endif //__APPIDRECORD_H_
