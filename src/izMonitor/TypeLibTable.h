// TypeLibTable.h : Declaration of the CTypeLibTable

#ifndef __TYPELIBTABLE_H_
#define __TYPELIBTABLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTypeLibTable
class ATL_NO_VTABLE CTypeLibTable : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTypeLibTable, &CLSID_TypeLibTable>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITypeLibTable, &IID_ITypeLibTable, &LIBID_IZMONITORLib>
{
public:
	CTypeLibTable()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TYPELIBTABLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTypeLibTable)
	COM_INTERFACE_ENTRY(ITypeLibTable)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITypeLibTable
public:
};

#endif //__TYPELIBTABLE_H_
