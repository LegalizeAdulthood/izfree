// RegistryRecord.h : Declaration of the CRegistryRecord

#ifndef __REGISTRYRECORD_H_
#define __REGISTRYRECORD_H_

#include "resource.h"       // main symbols
#include "s_tables.h"

/////////////////////////////////////////////////////////////////////////////
// CRegistryRecord
class ATL_NO_VTABLE CRegistryRecord : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CRegistryRecord, &CLSID_RegistryRecord>,
    public ISupportErrorInfo,
    public IDispatchImpl<IRegistryRecord, &IID_IRegistryRecord, &LIBID_IZMONITORLib>
{
public:
    CRegistryRecord() : m_record(0)     {}
    void Init(const s_registry *rhs)    { m_record = rhs; }

DECLARE_NO_REGISTRY()
DECLARE_NOT_AGGREGATABLE(CRegistryRecord)

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
    STDMETHOD(get_Component)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Value)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Key)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_Root)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_Registry)(/*[out, retval]*/ BSTR *pVal);

private:
    const s_registry *m_record;
};

#endif //__REGISTRYRECORD_H_
