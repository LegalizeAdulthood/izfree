// izfree Tools for Windows Installer
// Copyright (C) 2001-2002 Pahvant Technologies, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
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
