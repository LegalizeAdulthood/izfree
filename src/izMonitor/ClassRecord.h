// ClassRecord.h : Declaration of the CClassRecord

#ifndef __CLASSRECORD_H_
#define __CLASSRECORD_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClassRecord
class ATL_NO_VTABLE CClassRecord : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CClassRecord, &CLSID_ClassRecord>,
	public ISupportErrorInfo,
	public IDispatchImpl<IClassRecord, &IID_IClassRecord, &LIBID_IZMONITORLib>
{
public:
	CClassRecord()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CLASSRECORD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CClassRecord)
	COM_INTERFACE_ENTRY(IClassRecord)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IClassRecord
public:
	STDMETHOD(get_Attributes)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Feature)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Argument)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_DefInprocHandler)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_IconIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Icon)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_FileTypeMask)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_AppId)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ProgIdDefault)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Component)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Context)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_CLSID)(/*[out, retval]*/ BSTR *pVal);
};

#endif //__CLASSRECORD_H_
