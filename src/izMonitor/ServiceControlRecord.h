// ServiceControlRecord.h : Declaration of the CServiceControlRecord

#ifndef __SERVICECONTROLRECORD_H_
#define __SERVICECONTROLRECORD_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CServiceControlRecord
class ATL_NO_VTABLE CServiceControlRecord : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CServiceControlRecord, &CLSID_ServiceControlRecord>,
	public ISupportErrorInfo,
	public IDispatchImpl<IServiceControlRecord, &IID_IServiceControlRecord, &LIBID_IZMONITORLib>
{
public:
	CServiceControlRecord()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SERVICECONTROLRECORD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CServiceControlRecord)
	COM_INTERFACE_ENTRY(IServiceControlRecord)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IServiceControlRecord
public:
};

#endif //__SERVICECONTROLRECORD_H_
