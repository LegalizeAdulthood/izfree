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

/////////////////////////////////////////////////////////////////////////////
// THR_TRY, THR_CATCH, THR_CATCH_EI
//
// Uniform error handling macros
//
#define THR_TRY() if (1) try { 0

// returns HRESULT
#define THR_CATCH() } catch (const hresult_error &bang) { \
return bang.m_hr; } catch (...) { return E_UNEXPECTED; } else 0

// returns HRESULT + ISupportsErrorInfo
#define THR_CATCH_EI(iid_) } catch (const source_error &bang) { \
return Error(bang.m_msg.c_str(), iid_, E_UNEXPECTED); } catch (...) { \
return Error(_T("Unexpected exception."), iid_, E_UNEXPECTED); } else 0

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

///////////////////////////////////////////////////////////////////////////
// thread_args
//
// Structure containing arguments passed to the registration thread.
//
struct thread_args
{
    thread_args(const tstring &file, HANDLE event, bool service)
        : m_file(file),
        m_event(event),
        m_service(service),
        m_result(S_OK),
        m_bang(_T(__FILE__), __LINE__, _T(""))
    {}
    tstring m_file;
    HANDLE m_event;
    bool m_service;
    HRESULT m_result;
    source_error m_bang;
};

///////////////////////////////////////////////////////////////////////////
// s_monitor_key -- structure to monitor a registry key's differences
//
struct s_monitor_key
{
    s_monitor_key()
        : m_root(0),
        m_key(0),
        m_name(),
        m_subkey(),
        m_modified(false),
        m_values(),
        m_subkeys()
    {}
    s_monitor_key(HKEY root, LPCTSTR name, LPCTSTR subkey = NULL)
        : m_root(root),
        m_key(0),
        m_name(name),
        m_subkey(subkey ? subkey : _T("")),
        m_modified(false),
        m_values(),
        m_subkeys()
    {
        CRegKey tmp;
        TRS(tmp.Open(root, subkey, KEY_READ));
        m_key = tmp.Detach();
    }
    s_monitor_key(const s_monitor_key &rhs)
        : m_root(rhs.m_root),
        m_key(0),
        m_name(rhs.m_name),
        m_subkey(rhs.m_subkey),
        m_modified(rhs.m_modified),
        m_values(rhs.m_values),
        m_subkeys(rhs.m_subkeys)
    {
        if (rhs.m_key)
        {
            CRegKey tmp;
            TRS(tmp.Open(rhs.m_root, rhs.m_subkey.c_str(), KEY_READ));
            m_key = tmp.Detach();
        }
    }
    ~s_monitor_key()
    {
        if (m_key)
        {
            const LONG res = ::RegCloseKey(m_key);
            ATLASSERT(res == ERROR_SUCCESS);
        }
        m_key = 0;
    }

    HANDLE subscribe();
    void unsubscribe();

    void snapshot();
    void extract_app_id(app_id_table_t &appid,
                        registry_table_t &registry,
                        const tstring &component) const;
    void extract_app_id_entry(app_id_table_t &appid,
                              registry_table_t &registry,
                              const registry_key &subkey,
                              const tstring &component) const;
    void extract_class(class_table_t &klass,
                       registry_table_t &registry,
                       const tstring &component,
                       const tstring &feature) const;
    void extract_clsid_entry(class_table_t &klass,
                             registry_table_t &registry,
                             const registry_key &subkey,
                             const tstring &component,
                             const tstring &feature) const;
    void extract_prog_id(prog_id_table_t &prog_id,
                         registry_table_t &registry,
                         const tstring &component) const;
    void extract_prog_id_entry(prog_id_table_t &prog_id,
                               registry_table_t &registry,
                               const registry_key &subkey,
                               const tstring &component) const;
    void extract_registry(registry_table_t &registry,
                          const tstring &component) const;
    void extract_type_lib(type_lib_table_t &type_lib,
                          registry_table_t &registry,
                          const tstring &component,
                          const tstring &feature) const;
    void extract_type_lib_entry(type_lib_table_t &type_lib,
                                registry_table_t &registry,
                                const registry_key &subkey,
                                const tstring &component,
                                const tstring &feature) const;

    HKEY m_root;
    HKEY m_key;
    tstring m_name;
    tstring m_subkey;
    bool m_modified;

    std::set<tstring> m_values;
    std::set<tstring> m_subkeys;
};

/////////////////////////////////////////////////////////////////////////////
// CMonitor
class ATL_NO_VTABLE CMonitor
    : public CComObjectRootEx<CComSingleThreadModel>,
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
    STDMETHOD(get_Feature)(BSTR *pVal);
    STDMETHOD(get_Component)(BSTR *pVal);
    STDMETHOD(ClearKeys)();
    STDMETHOD(get_Service)(long *pVal);
    STDMETHOD(get_File)(BSTR *pVal);
    STDMETHOD(get_ServiceInstallTable)(IServiceInstallTable **pVal);
    STDMETHOD(get_ServiceControlTable)(IServiceControlTable **pVal);
    STDMETHOD(get_TypeLibTable)(ITypeLibTable **pVal);
    STDMETHOD(get_ProgIdTable)(IProgIdTable **pVal);
    STDMETHOD(get_RegistryTable)(IRegistryTable **pVal);
    STDMETHOD(get_ClassTable)(IClassTable **pVal);
    STDMETHOD(WatchKey)(BSTR registry_key);
    STDMETHOD(Process)(BSTR file, BOOL service,
                       BSTR component, BSTR feature);
    STDMETHOD(get_AppIdTable)(IAppIdTable * *pVal);

private:
    void dump_tables();
    void diff_services();

    // database tables scraped out of the registry
    CComObject<CAppIdTable>          *m_app_id;
    CComObject<CClassTable>          *m_class;
    CComObject<CProgIdTable>         *m_prog_id;
    CComObject<CRegistryTable>       *m_registry;
    CComObject<CTypeLibTable>        *m_type_lib;
    CComObject<CServiceControlTable> *m_service_control;
    CComObject<CServiceInstallTable> *m_service_install;

    tstring m_file;                     // file being processed
    tstring m_component;                // component name used in tables
    tstring m_feature;                  // feature name used in tables
    bool m_service;                     // true to extract service tables

    std::vector<s_monitor_key> m_keys;  // registry keys being monitored
    string_list_t m_services;           // captured list of services

    // threadproc for registration thread
    static void __cdecl register_threadproc(void *pv);
};

#endif //__MONITOR_H_
