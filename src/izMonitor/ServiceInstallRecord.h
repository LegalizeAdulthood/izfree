// ServiceInstallRecord.h : Declaration of the CServiceInstallRecord

#ifndef __SERVICEINSTALLRECORD_H_
#define __SERVICEINSTALLRECORD_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CServiceInstallRecord
class ATL_NO_VTABLE CServiceInstallRecord : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CServiceInstallRecord, &CLSID_ServiceInstallRecord>,
    public ISupportErrorInfo,
	public IDispatchImpl<IServiceInstallRecord, &IID_IServiceInstallRecord, &LIBID_IZMONITORLib>
{
public:
	CServiceInstallRecord()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SERVICEINSTALLRECORD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CServiceInstallRecord)
	COM_INTERFACE_ENTRY(IServiceInstallRecord)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IServiceInstallRecord
public:
};

#endif //__SERVICEINSTALLRECORD_H_
