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
// AppIdTable.cpp : Implementation of CAppIdTable
#include "stdafx.h"
#include "izMonitor.h"
#include "AppIdTable.h"
#include "AppIdRecord.h"

/////////////////////////////////////////////////////////////////////////////
// CAppIdTable

#define CHECK_POINTER(var_) \
    if (!var_) \
    { \
        return Error(_T("A NULL pointer was passed for an output argument."), \
                     IID_IAppIdTable, E_POINTER); \
    } else 0

CAppIdTable::CAppIdTable() : m_table(1)
{
    m_table[0] = s_app_id(_T("Row1"), _T("remote server"),
        _T("local service"), _T("service parameters"),
        _T("dll surrogate"), 1, 2);
}

STDMETHODIMP CAppIdTable::get_Count(long *pVal)
{
    CHECK_POINTER(pVal);
    *pVal = m_table.size();
	return S_OK;
}

STDMETHODIMP CAppIdTable::_NewEnum(IUnknown **enumerator)
{
    CHECK_POINTER(enumerator);
	return S_OK;
}

STDMETHODIMP CAppIdTable::get_Item(long row, IAppIdRecord **pVal)
{
    CHECK_POINTER(pVal);
    if (row < 0 || row > m_table.size())
    {
        return Error(_T("The requested row index is outside the valid range."),
                     IID_IAppIdTable, E_INVALIDARG);
    }
    CComObject<CAppIdRecord> *rec = NULL;
    CComObject<CAppIdRecord>::CreateInstance(&rec);
    rec->Init(m_table[row]);
    const HRESULT hr = rec->QueryInterface(pVal);
    if (FAILED(hr))
    {
        delete rec;
    }
	return hr;
}

void
CAppIdTable::Add(const tstring &app_id, const tstring &remote_server,
    const tstring &local_service, const tstring &service_params,
    const tstring &dll_surrogate, DWORD activate_at_storage,
    DWORD run_as)
{
    m_table.push_back(s_app_id(app_id, remote_server, local_service,
        service_params, dll_surrogate, activate_at_storage, run_as));
}