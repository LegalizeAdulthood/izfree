// Generator.h : Declaration of the CGenerator

#ifndef __GENERATOR_H_
#define __GENERATOR_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGenerator
class ATL_NO_VTABLE CGenerator : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGenerator, &CLSID_Generator>,
	public IDispatchImpl<IGenerator, &IID_IGenerator, &LIBID_GUIDGENLib>
{
public:
	CGenerator()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GENERATOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGenerator)
	COM_INTERFACE_ENTRY(IGenerator)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IGenerator
public:
	STDMETHOD(Generate)(/*[out, retval]*/ BSTR *guid);
};

#endif //__GENERATOR_H_
