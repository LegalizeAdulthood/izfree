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
// AppIdTable.h : Declaration of the CAppIdTable

#ifndef __APPIDTABLE_H_
#define __APPIDTABLE_H_

#include "resource.h"       // main symbols
#include "s_tables.h"
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CAppIdTable
class ATL_NO_VTABLE CAppIdTable : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAppIdTable, &CLSID_AppIdTable>,
	public IDispatchImpl<IAppIdTable, &IID_IAppIdTable, &LIBID_IZMONITORLib>
{
public:
    CAppIdTable();

    void Add(const tstring &app_id, const tstring &remote_server,
        const tstring &local_service, const tstring &service_params,
        const tstring &dll_surrogate, DWORD activate_at_storage,
        DWORD run_as);

DECLARE_REGISTRY_RESOURCEID(IDR_APPIDTABLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAppIdTable)
	COM_INTERFACE_ENTRY(IAppIdTable)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IAppIdTable
public:
	STDMETHOD(get_Item)(/*[in]*/ long row, /*[out, retval]*/ IAppIdRecord * *pVal);
	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **enumerator);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);

private:
    std::vector<s_app_id> m_table;
};

#endif //__APPIDTABLE_H_
