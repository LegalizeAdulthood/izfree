// ServiceInstallTable.h : Declaration of the CServiceInstallTable

#ifndef __SERVICEINSTALLTABLE_H_
#define __SERVICEINSTALLTABLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CServiceInstallTable
class ATL_NO_VTABLE CServiceInstallTable : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CServiceInstallTable, &CLSID_ServiceInstallTable>,
	public IDispatchImpl<IServiceInstallTable, &IID_IServiceInstallTable, &LIBID_IZMONITORLib>
{
public:
	CServiceInstallTable()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SERVICEINSTALLTABLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CServiceInstallTable)
	COM_INTERFACE_ENTRY(IServiceInstallTable)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IServiceInstallTable
public:
};

#endif //__SERVICEINSTALLTABLE_H_
