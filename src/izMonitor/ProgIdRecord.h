// ProgIdRecord.h : Declaration of the CProgIdRecord

#ifndef __PROGIDRECORD_H_
#define __PROGIDRECORD_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProgIdRecord
class ATL_NO_VTABLE CProgIdRecord : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProgIdRecord, &CLSID_ProgIdRecord>,
	public ISupportErrorInfo,
	public IDispatchImpl<IProgIdRecord, &IID_IProgIdRecord, &LIBID_IZMONITORLib>
{
public:
	CProgIdRecord()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PROGIDRECORD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProgIdRecord)
	COM_INTERFACE_ENTRY(IProgIdRecord)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IProgIdRecord
public:
};

#endif //__PROGIDRECORD_H_
