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
// Monitor.h : Declaration of the CMonitor

#ifndef __MONITOR_H_
#define __MONITOR_H_

#include "resource.h"       // main symbols
#include "AppIdTable.h"

/////////////////////////////////////////////////////////////////////////////
// CMonitor
class ATL_NO_VTABLE CMonitor : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CMonitor, &CLSID_Monitor>,
    public IDispatchImpl<IMonitor, &IID_IMonitor, &LIBID_IZMONITORLib>
{
public:
    CMonitor();
    ~CMonitor();
    HRESULT FinalConstruct();
    void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_MONITOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMonitor)
    COM_INTERFACE_ENTRY(IMonitor)
    COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMonitor
public:
    STDMETHOD(get_ServiceInstallTable)(/*[out, retval]*/ IServiceInstallTable * *pVal);
    STDMETHOD(get_ServiceControlTable)(/*[out, retval]*/ IServiceControlTable * *pVal);
    STDMETHOD(get_TypeLibTable)(/*[out, retval]*/ ITypeLibTable * *pVal);
    STDMETHOD(get_ProgIdTable)(/*[out, retval]*/ IProgIdTable * *pVal);
    STDMETHOD(get_RegistryTable)(/*[out, retval]*/ IRegistryTable * *pVal);
    STDMETHOD(get_ClassTable)(/*[out, retval]*/ IClassTable * *pVal);
    STDMETHOD(WatchKey)(BSTR registry_key);
    STDMETHOD(Process)(/*[in]*/ BSTR file, /*[in]*/ BOOL service);
    STDMETHOD(get_AppIdTable)(/*[out, retval]*/ IAppIdTable * *pVal);

private:
    CComObject<CAppIdTable> *m_app_ids;
    tstring m_file;
    bool m_service;
};

#endif //__MONITOR_H_
