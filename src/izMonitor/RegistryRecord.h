// RegistryRecord.h : Declaration of the CRegistryRecord

#ifndef __REGISTRYRECORD_H_
#define __REGISTRYRECORD_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegistryRecord
class ATL_NO_VTABLE CRegistryRecord : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRegistryRecord, &CLSID_RegistryRecord>,
	public ISupportErrorInfo,
	public IDispatchImpl<IRegistryRecord, &IID_IRegistryRecord, &LIBID_IZMONITORLib>
{
public:
	CRegistryRecord()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_REGISTRYRECORD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRegistryRecord)
	COM_INTERFACE_ENTRY(IRegistryRecord)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRegistryRecord
public:
};

#endif //__REGISTRYRECORD_H_
