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
// Monitor.h : Declaration of the CMonitor

#ifndef __MONITOR_H_
#define __MONITOR_H_

#include "resource.h"       // main symbols
#include "AppIdRecord.h"
#include "ClassRecord.h"
#include "RegistryRecord.h"
#include "ProgIdRecord.h"
#include "TypeLibRecord.h"
#include "ServiceControlRecord.h"
#include "ServiceInstallRecord.h"
#include "s_tables.h"

///////////////////////////////////////////////////////////////////////////
// CopyVariantFromRecord
//
// Copy records and turn them into dispinterfaces during the copy.
//
// Create an instance of the wrapper class for a record, initialize it
// with the record data, query for IDispatch and hand that dispinterface
// back to the caller.
//
template <typename Wrapper, typename Record>
struct CopyVariantFromRecord
{
    static HRESULT copy(VARIANT *lhs, const Record *rhs)
    {
        typedef CComObject<Wrapper> wrapper_t;
        wrapper_t *wrapper = 0;
        HRESULT hr = wrapper_t::CreateInstance(&wrapper);
        if (SUCCEEDED(hr))
        {
            wrapper->Init(rhs);
            IDispatch *dispatch = 0;
            hr = wrapper->QueryInterface(&dispatch);
            if (SUCCEEDED(hr))
            {
                lhs->vt = VT_DISPATCH;
                lhs->pdispVal = dispatch;
            }
            else
            {
                delete wrapper;
            }
        }
        return hr;
    }
    static void init(VARIANT *lhs)      { ::VariantInit(lhs); }
    static void destroy(VARIANT *lhs)   { ::VariantClear(lhs); }
};

///////////////////////////////////////////////////////////////////////////
// DEFINE_COM_TABLE
//
// Huge macro that captures the repeated pattern in all the tables and
// their wrapper objects.  Each table exposes each row as a dispinterface
// that wraps the underlying data.  The differences in this pattern
// rely upon the names of the objects within the code.  If they differed
// only by type, then we could use a template class or function to factor
// out the commonalities.
//
// CopyVariantFromXXX
//      A specialization of the CopyVariantFromRecord class that creates
//      a wrapper object for one of the table records and initializes the
//      wrapper with the record.
//
// IXXXTableDualImpl
//      The implementation of IDispatch for the table object
//
// CComEnumVariantOnXXX
//      The implementation of IEnumVARIANT for the table
//
// IXXXTableImpl
//      The implementation of the collection interface for the table
//      (Count, Item, _NewEnum)
//
#define DEFINE_COM_TABLE(name_, record_, table_)                    \
typedef struct CopyVariantFromRecord<                               \
    C##name_##Record, record_                                       \
> CopyVariantFrom##name_;                                           \
                                                                    \
typedef IDispatchImpl<                                              \
    I##name_##Table, &IID_I##name_##Table                           \
> I##name_##TableDualImpl;                                          \
                                                                    \
typedef CComEnumOnSTL<                                              \
    IEnumVARIANT, &IID_IEnumVARIANT,                                \
    VARIANT, CopyVariantFrom##name_, table_                         \
> CComEnumVariantOn##name_;                                         \
                                                                    \
typedef ICollectionOnSTLImpl<                                       \
    I##name_##TableDualImpl, table_,                                \
    VARIANT, CopyVariantFrom##name_, CComEnumVariantOn##name_       \
> I##name_##TableImpl;                                              \
                                                                    \
class ATL_NO_VTABLE C##name_##Table :                               \
    public CComObjectRootEx<CComSingleThreadModel>,                 \
    public CComCoClass<C##name_##Table, &CLSID_##name_##Table>,     \
    public I##name_##TableImpl                                      \
{                                                                   \
public:                                                             \
    C##name_##Table() {}                                            \
                                                                    \
    DECLARE_NO_REGISTRY()                                           \
    DECLARE_NOT_AGGREGATABLE(C##name_##Table)                       \
                                                                    \
    DECLARE_PROTECT_FINAL_CONSTRUCT()                               \
                                                                    \
    BEGIN_COM_MAP(C##name_##Table)                                  \
        COM_INTERFACE_ENTRY(I##name_##Table)                        \
        COM_INTERFACE_ENTRY(IDispatch)                              \
    END_COM_MAP()                                                   \
                                                                    \
public:                                                             \
    void Add(const record_ &record)                                 \
    {                                                               \
        m_coll.push_back(record);                                   \
    }                                                               \
    void Clear()                                                    \
    {                                                               \
        m_coll.clear();                                             \
    }                                                               \
}

DEFINE_COM_TABLE(AppId, s_app_id, app_id_table_t);
DEFINE_COM_TABLE(Class, s_class, class_table_t);
DEFINE_COM_TABLE(Registry, s_registry, registry_table_t);
DEFINE_COM_TABLE(ProgId, s_prog_id, prog_id_table_t);
DEFINE_COM_TABLE(TypeLib, s_type_lib, type_lib_table_t);
DEFINE_COM_TABLE(ServiceControl, s_service_control, service_control_table_t);
DEFINE_COM_TABLE(ServiceInstall, s_service_install, service_install_table_t);

/////////////////////////////////////////////////////////////////////////////
// CMonitor
class ATL_NO_VTABLE CMonitor : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CMonitor, &CLSID_Monitor>,
    public IDispatchImpl<IMonitor, &IID_IMonitor, &LIBID_IZMONITORLib>
{
public:
    CMonitor();
    ~CMonitor();
    HRESULT FinalConstruct();
    void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_MONITOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMonitor)
    COM_INTERFACE_ENTRY(IMonitor)
    COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMonitor
public:
    STDMETHOD(get_ServiceInstallTable)(/*[out, retval]*/ IServiceInstallTable * *pVal);
    STDMETHOD(get_ServiceControlTable)(/*[out, retval]*/ IServiceControlTable * *pVal);
    STDMETHOD(get_TypeLibTable)(/*[out, retval]*/ ITypeLibTable * *pVal);
    STDMETHOD(get_ProgIdTable)(/*[out, retval]*/ IProgIdTable * *pVal);
    STDMETHOD(get_RegistryTable)(/*[out, retval]*/ IRegistryTable * *pVal);
    STDMETHOD(get_ClassTable)(/*[out, retval]*/ IClassTable * *pVal);
    STDMETHOD(WatchKey)(BSTR registry_key);
    STDMETHOD(Process)(/*[in]*/ BSTR file, /*[in]*/ BOOL service);
    STDMETHOD(get_AppIdTable)(/*[out, retval]*/ IAppIdTable * *pVal);

private:
    CComObject<CAppIdTable> *m_app_id;
    CComObject<CClassTable> *m_class;
    CComObject<CProgIdTable> *m_prog_id;
    CComObject<CRegistryTable> *m_registry;
    CComObject<CTypeLibTable> *m_type_lib;
    CComObject<CServiceControlTable> *m_service_control;
    CComObject<CServiceInstallTable> *m_service_install;
    tstring m_file;
    bool m_service;
};

#endif //__MONITOR_H_
