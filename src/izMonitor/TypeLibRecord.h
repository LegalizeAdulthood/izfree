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
	STDMETHOD(get_Cost)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_Feature)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Directory)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_Component)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Language)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_LibID)(/*[out, retval]*/ BSTR *pVal);
};

#endif //__TYPELIBRECORD_H_
