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
#include "AppIdRecord.h"
#include "Monitor.h"

#include <process.h>

/////////////////////////////////////////////////////////////////////////////
// CHECK_POINTER
//
#define CHECK_POINTER(var_)                                                 \
if (!var_)                                                                  \
{                                                                           \
    return Error(_T("A NULL pointer was passed for an output argument."),   \
              IID_IMonitor, E_POINTER);                                     \
} else 0

// RETURN_TABLE
#define RETURN_TABLE(member_)   \
    CHECK_POINTER(pVal);        \
    *pVal = member_;            \
    (*pVal)->AddRef()

/////////////////////////////////////////////////////////////////////////////
// construct_table
//
// Create an instance of a table wrapper object and AddRef() on success.
//
template <typename Wrapper>
void
construct_table(CComObject<Wrapper> *&table)
{
    THR(CComObject<Wrapper>::CreateInstance(&table));
    table->AddRef();
}

/////////////////////////////////////////////////////////////////////////////
// release_table
//
// Release a table acquired in construct_table.
//
template <typename Wrapper>
void
release_table(CComObject<Wrapper> *&table)
{
    table->Release();
    table = 0;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CMonitor c'tor, d'tor
//
CMonitor::CMonitor()
    : m_app_id(NULL),
    m_class(NULL),
    m_prog_id(NULL),
    m_registry(NULL),
    m_type_lib(NULL),
    m_service_control(NULL),
    m_service_install(NULL),
    m_file(),
    m_component(),
    m_service(false),
    m_keys(),
    m_services()
{
    m_keys.reserve(64);
}

CMonitor::~CMonitor()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMonitor::FinalConstruct
//
// Construct all the table objects we will fill up while scraping the
// registry.
//
HRESULT
CMonitor::FinalConstruct()
{
    THR_TRY();
    construct_table(m_app_id);
    construct_table(m_class);
    construct_table(m_prog_id);
    construct_table(m_registry);
    construct_table(m_type_lib);
    construct_table(m_service_control);
    construct_table(m_service_install);
    THR_CATCH();

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CMonitor::FinalRelease
//
// Release all the table objects.
//
void
CMonitor::FinalRelease()
{
    release_table(m_app_id);
    release_table(m_class);
    release_table(m_prog_id);
    release_table(m_registry);
    release_table(m_service_control);
    release_table(m_service_install);
    release_table(m_type_lib);
}

///////////////////////////////////////////////////////////////////////////
// CMonitor::WatchKey
//
// Add a registry key to the list of keys that will be monitored during
// registration.  Since Windows Installer only supports writing keys into
// HKCR, HKCU, HKLM, and HKU, return E_INVALIDARG for any other root hive.
//
STDMETHODIMP
CMonitor::WatchKey(BSTR registry_key)
{
    USES_CONVERSION;
    HKEY root = 0;
    tstring key = W2T(registry_key);
    const tstring::size_type whack = key.find(_T("\\"));
    const tstring root_name = (whack != tstring::npos) ?
        key.substr(0, whack) : key;
    if (cis_equal(_T("HKCR"), root_name) ||
        cis_equal(_T("HKEY_CLASSES_ROOT"), root_name))
    {
        root = HKEY_CLASSES_ROOT;
    }
    else if (cis_equal(_T("HKCU"), root_name)
             || cis_equal(_T("HKEY_CURRENT_USER"), root_name))
    {
        root = HKEY_CURRENT_USER;
    }
    else if (cis_equal(_T("HKLM"), root_name)
             || cis_equal(_T("HKEY_LOCAL_MACHINE"), root_name))
    {
        root = HKEY_LOCAL_MACHINE;
    }
    else if (cis_equal(_T("HKU"), root_name)
             || cis_equal(_T("HKEY_USERS"), root_name))
    {
        root = HKEY_USERS;
    }
    else
    {
        return Error(_T("An invalid registry key root was specified."),
                     IID_IMonitor, E_INVALIDARG);
    }

    THR_TRY();
    if (whack != tstring::npos)
    {
        const tstring subkey = key.substr(whack+1);
        CRegKey tmp;
        TRS(tmp.Open(root, subkey.c_str(), KEY_READ));
        m_keys.push_back(s_monitor_key(tmp.Detach(), root_name.c_str(),
                                       subkey.c_str()));
    }
    else
    {
        m_keys.push_back(s_monitor_key(root, root_name.c_str()));
    }
    THR_CATCH_EI(IID_IMonitor);

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CMonitor::get_file
//
// Get the last file set through Process, or the empty string if Process
// has not yet been called.
//
STDMETHODIMP
CMonitor::get_File(BSTR *pVal)
{
    CHECK_POINTER(pVal);
    *pVal = CComBSTR(m_file.c_str()).Detach();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CMonitor::get_Service
//
// Get the last service flag set through Process, or false if Process
// has not yet been called.
//
STDMETHODIMP CMonitor::get_Service(long *pVal)
{
    CHECK_POINTER(pVal);
    *pVal = static_cast<long>(m_service);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CMonitor::get_XXXTable
//
// Table accessors; just hand back a copy of the internal interface pointer
// after AddRef'ing it.
//
STDMETHODIMP
CMonitor::get_AppIdTable(IAppIdTable **pVal)
{
    RETURN_TABLE(m_app_id);
    return S_OK;
}

STDMETHODIMP
CMonitor::get_ClassTable(IClassTable **pVal)
{
    RETURN_TABLE(m_class);
    return S_OK;
}

STDMETHODIMP
CMonitor::get_RegistryTable(IRegistryTable **pVal)
{
    RETURN_TABLE(m_registry);
    return S_OK;
}

STDMETHODIMP
CMonitor::get_ProgIdTable(IProgIdTable **pVal)
{
    RETURN_TABLE(m_prog_id);
    return S_OK;
}

STDMETHODIMP
CMonitor::get_TypeLibTable(ITypeLibTable **pVal)
{
    RETURN_TABLE(m_type_lib);
    return S_OK;
}
STDMETHODIMP
CMonitor::get_ServiceControlTable(IServiceControlTable **pVal)
{
    RETURN_TABLE(m_service_control);
    return S_OK;
}

STDMETHODIMP
CMonitor::get_ServiceInstallTable(IServiceInstallTable **pVal)
{
    RETURN_TABLE(m_service_install);
    return S_OK;
}

STDMETHODIMP
CMonitor::ClearKeys()
{
    while (m_keys.size())
    {
        m_keys.pop_back();
    }

	return S_OK;
}
