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
// Monitor.cpp : Implementation of CMonitor
#include "stdafx.h"
#include "izMonitor.h"
#include "Monitor.h"
#include "AppIdRecord.h"

/////////////////////////////////////////////////////////////////////////////
// CMonitor

#define CHECK_POINTER(var_) \
    if (!var_) \
    { \
        return Error(_T("A NULL pointer was passed for an output argument."), \
                     IID_IMonitor, E_POINTER); \
    } else 0

CMonitor::CMonitor()
    : m_app_ids(NULL)
{
}

CMonitor::~CMonitor()
{
}

HRESULT
CMonitor::FinalConstruct()
{
    CComObject<CAppIdTable>::CreateInstance(&m_app_ids);
    m_app_ids->AddRef();
    return S_OK;
}

void
CMonitor::FinalRelease()
{
    m_app_ids->Release();
    m_app_ids = 0;
}

STDMETHODIMP
CMonitor::get_AppIdTable(IAppIdTable **pVal)
{
    CHECK_POINTER(pVal);
    *pVal = m_app_ids;
    (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP
CMonitor::Process(BSTR file, BOOL service)
{
    USES_CONVERSION;
    m_file = W2T(file);
    m_service = (service != 0);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CMonitor::WatchKey(BSTR registry_key)
{
    USES_CONVERSION;
    tstring key = W2T(registry_key);
    tstring::size_type whack = key.find(_T("\\"));
    const tstring root = (whack != tstring::npos) ? key.substr(0, whack) : key;
    if (cis_equal(_T("HKCR"), root) || cis_equal(_T("HKEY_CLASSES_ROOT"), root))
    {
    }
    else if (cis_equal(_T("HKCU"), root)
             || cis_equal(_T("HKEY_CURRENT_USER"), root))
    {
    }
    else if (cis_equal(_T("HKLM"), root)
             || cis_equal(_T("HKEY_LOCAL_MACHINE"), root))
    {
    }
    else if (cis_equal(_T("HKU"), root)
             || cis_equal(_T("HKEY_USERS"), root))
    {
    }
    else
    {
        return Error(_T("An invalid registry key root was specified."),
                     IID_IMonitor, E_INVALIDARG);
    }

	return S_OK;
}
