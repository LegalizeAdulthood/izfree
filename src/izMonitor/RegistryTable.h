// RegistryTable.h : Declaration of the CRegistryTable

#ifndef __REGISTRYTABLE_H_
#define __REGISTRYTABLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegistryTable
class ATL_NO_VTABLE CRegistryTable : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRegistryTable, &CLSID_RegistryTable>,
	public ISupportErrorInfo,
	public IDispatchImpl<IRegistryTable, &IID_IRegistryTable, &LIBID_IZMONITORLib>
{
public:
	CRegistryTable()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_REGISTRYTABLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRegistryTable)
	COM_INTERFACE_ENTRY(IRegistryTable)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRegistryTable
public:
};

#endif //__REGISTRYTABLE_H_
