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
// AppIdRecord.cpp : Implementation of CAppIdRecord
#include "stdafx.h"
#include "izMonitor.h"
#include "AppIdRecord.h"

/////////////////////////////////////////////////////////////////////////////
// CAppIdRecord

#define CHECK_PROPERTY_POINTER() \
if (!pVal) \
{ \
    return Error(_T("A NULL pointer was passed for an output argument."), \
        IID_IAppIdRecord, E_POINTER); \
} else 0
#define STORE_STRING_PROPERTY(member_) \
    *pVal = CComBSTR(m_app_id.member_.c_str()).Detach()

CAppIdRecord::CAppIdRecord()
    : m_app_id(_T("{guid}"), _T("remote server"), _T("local service"),
               _T("service params"), _T("dll surrogate"), 0, 0)
{
}

void
CAppIdRecord::Init(const s_app_id &app_id)
{
    m_app_id = app_id;
}

STDMETHODIMP CAppIdRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAppIdRecord
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAppIdRecord::get_AppId(BSTR *pVal)
{
	CHECK_PROPERTY_POINTER();
    STORE_STRING_PROPERTY(m_app_id);
	return S_OK;
}

STDMETHODIMP CAppIdRecord::get_RemoteServerName(BSTR *pVal)
{
	CHECK_PROPERTY_POINTER();
    STORE_STRING_PROPERTY(m_remote_server_name);
	return S_OK;
}

STDMETHODIMP CAppIdRecord::get_LocalService(BSTR *pVal)
{
	CHECK_PROPERTY_POINTER();
    STORE_STRING_PROPERTY(m_local_service);
	return S_OK;
}

STDMETHODIMP CAppIdRecord::get_ServiceParameters(BSTR *pVal)
{
	CHECK_PROPERTY_POINTER();
    STORE_STRING_PROPERTY(m_app_id);
	return S_OK;
}

STDMETHODIMP CAppIdRecord::get_DllSurrogate(BSTR *pVal)
{
	CHECK_PROPERTY_POINTER();
    STORE_STRING_PROPERTY(m_app_id);
	return S_OK;
}

STDMETHODIMP CAppIdRecord::get_ActivateAtStorage(LONG *pVal)
{
	CHECK_PROPERTY_POINTER();
    *pVal = m_app_id.m_activate_at_storage;
	return S_OK;
}

STDMETHODIMP CAppIdRecord::get_RunAsInteractiveUser(LONG *pVal)
{
	CHECK_PROPERTY_POINTER();
    *pVal = m_app_id.m_run_as_interactive_user;
	return S_OK;
}
