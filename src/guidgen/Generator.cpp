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
// Generator.cpp : Implementation of CGenerator
#include "stdafx.h"
#include "Guidgen.h"
#include "Generator.h"

/////////////////////////////////////////////////////////////////////////////
// CGenerator

#define NUM_OF(ary_) (sizeof(ary_)/sizeof((ary_)[0]))

STDMETHODIMP CGenerator::Generate(BSTR *guid)
{
    if (!guid)
    {
        return E_POINTER;
    }

    GUID g = { 0 };
    const HRESULT hr = ::CoCreateGuid(&g);
    if (FAILED(hr))
    {
        return hr;
    }
    OLECHAR buffer[80];
    if (!::StringFromGUID2(g, buffer, NUM_OF(buffer)))
    {
        return E_INVALIDARG;
    }
    *guid = CComBSTR(buffer).Detach();

	return S_OK;
}
