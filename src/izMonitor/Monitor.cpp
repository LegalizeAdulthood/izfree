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
// CMonitor

CMonitor::CMonitor()
    : m_app_id(NULL),
    m_class(NULL),
    m_prog_id(NULL),
    m_registry(NULL),
    m_type_lib(NULL),
    m_service_control(NULL),
    m_service_install(NULL)
{
}

CMonitor::~CMonitor()
{
}

HRESULT
CMonitor::FinalConstruct()
{
    try
    {
        construct_table(m_app_id);
        construct_table(m_class);
        construct_table(m_prog_id);
        construct_table(m_registry);
        construct_table(m_type_lib);
        construct_table(m_service_control);
        construct_table(m_service_install);
    }
    catch (const hresult_error &bang)
    {
        return bang.m_hr;
    }
    catch (...)
    {
        return E_UNEXPECTED;
    }

    return S_OK;
}

void
CMonitor::FinalRelease()
{
    release_table(m_class);
    release_table(m_prog_id);
    release_table(m_registry);
    release_table(m_type_lib);
    release_table(m_service_control);
    release_table(m_service_install);
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
