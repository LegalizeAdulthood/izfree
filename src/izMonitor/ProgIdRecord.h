// ProgIdRecord.h : Declaration of the CProgIdRecord

#ifndef __PROGIDRECORD_H_
#define __PROGIDRECORD_H_

#include "resource.h"       // main symbols
#include "s_tables.h"

/////////////////////////////////////////////////////////////////////////////
// CProgIdRecord
class ATL_NO_VTABLE CProgIdRecord : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CProgIdRecord, &CLSID_ProgIdRecord>,
    public ISupportErrorInfo,
    public IDispatchImpl<IProgIdRecord, &IID_IProgIdRecord, &LIBID_IZMONITORLib>
{
public:
    CProgIdRecord() : m_record(0)       {}
    void Init(const s_prog_id *record)  { m_record = record; }

DECLARE_NO_REGISTRY()
DECLARE_NOT_AGGREGATABLE(CProgIdRecord)

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
    STDMETHOD(get_IconIndex)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_Icon)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Class)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Parent)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_ProgId)(/*[out, retval]*/ BSTR *pVal);

private:
    const s_prog_id *m_record;
};

#endif //__PROGIDRECORD_H_
