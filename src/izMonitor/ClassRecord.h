// ClassRecord.h : Declaration of the CClassRecord

#ifndef __CLASSRECORD_H_
#define __CLASSRECORD_H_

#include "resource.h"       // main symbols
#include "s_tables.h"

/////////////////////////////////////////////////////////////////////////////
// CClassRecord
class ATL_NO_VTABLE CClassRecord : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CClassRecord, &CLSID_ClassRecord>,
    public ISupportErrorInfo,
    public IDispatchImpl<IClassRecord, &IID_IClassRecord, &LIBID_IZMONITORLib>
{
public:
    CClassRecord() : m_record(0)    {}
    void Init(const s_class *rhs)   { m_record = rhs; }

DECLARE_NO_REGISTRY()
DECLARE_NOT_AGGREGATABLE(CClassRecord)

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

private:
    const s_class *m_record;
};

#endif //__CLASSRECORD_H_
