// ClassTable.h : Declaration of the CClassTable

#ifndef __CLASSTABLE_H_
#define __CLASSTABLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClassTable
class ATL_NO_VTABLE CClassTable : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CClassTable, &CLSID_ClassTable>,
	public ISupportErrorInfo,
	public IDispatchImpl<IClassTable, &IID_IClassTable, &LIBID_IZMONITORLib>
{
public:
	CClassTable()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ICLASSTABLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CClassTable)
	COM_INTERFACE_ENTRY(IClassTable)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IClassTable
public:
    STDMETHOD(_NewEnum)(struct IUnknown **enumerator);
	STDMETHOD(get_Item)(/*[in]*/ long row, /*[out, retval]*/ IClassRecord * *pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
};

#endif //__CLASSTABLE_H_
