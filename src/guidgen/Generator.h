// izfree Tools for Windows Installer 1.0
// Copyright (C) 2001 Pahvant Technologies, Inc.
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
