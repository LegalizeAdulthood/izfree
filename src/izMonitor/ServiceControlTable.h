// ServiceControlTable.h : Declaration of the CServiceControlTable

#ifndef __SERVICECONTROLTABLE_H_
#define __SERVICECONTROLTABLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CServiceControlTable
class ATL_NO_VTABLE CServiceControlTable : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CServiceControlTable, &CLSID_ServiceControlTable>,
	public ISupportErrorInfo,
	public IDispatchImpl<IServiceControlTable, &IID_IServiceControlTable, &LIBID_IZMONITORLib>
{
public:
	CServiceControlTable()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SERVICECONTROLTABLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CServiceControlTable)
	COM_INTERFACE_ENTRY(IServiceControlTable)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IServiceControlTable
public:
};

#endif //__SERVICECONTROLTABLE_H_
