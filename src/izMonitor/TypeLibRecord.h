// TypeLibRecord.h : Declaration of the CTypeLibRecord

#ifndef __TYPELIBRECORD_H_
#define __TYPELIBRECORD_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTypeLibRecord
class ATL_NO_VTABLE CTypeLibRecord : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTypeLibRecord, &CLSID_TypeLibRecord>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITypeLibRecord, &IID_ITypeLibRecord, &LIBID_IZMONITORLib>
{
public:
	CTypeLibRecord()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TYPELIBRECORD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTypeLibRecord)
	COM_INTERFACE_ENTRY(ITypeLibRecord)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITypeLibRecord
public:
};

#endif //__TYPELIBRECORD_H_
