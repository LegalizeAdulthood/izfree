// FileVersion.h : Declaration of the CFileVersion

#ifndef __FILEVERSION_H_
#define __FILEVERSION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileVersion
class ATL_NO_VTABLE CFileVersion : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileVersion, &CLSID_FileVersion>,
	public IDispatchImpl<IFileVersion, &IID_IFileVersion, &LIBID_GUIDGENLib>
{
public:
	CFileVersion()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FILEVERSION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFileVersion)
	COM_INTERFACE_ENTRY(IFileVersion)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IFileVersion
public:
	STDMETHOD(get_Version)(/*[in]*/ BSTR file, /*[out, retval]*/ BSTR *pVal);
};

#endif //__FILEVERSION_H_
