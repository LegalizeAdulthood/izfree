// ProgIdTable.h : Declaration of the CProgIdTable

#ifndef __PROGIDTABLE_H_
#define __PROGIDTABLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProgIdTable
class ATL_NO_VTABLE CProgIdTable : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProgIdTable, &CLSID_ProgIdTable>,
	public ISupportErrorInfo,
	public IDispatchImpl<IProgIdTable, &IID_IProgIdTable, &LIBID_IZMONITORLib>
{
public:
	CProgIdTable()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PROGIDTABLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProgIdTable)
	COM_INTERFACE_ENTRY(IProgIdTable)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IProgIdTable
public:
};

#endif //__PROGIDTABLE_H_
