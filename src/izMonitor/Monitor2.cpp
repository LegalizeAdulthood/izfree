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
// Monitor2.cpp : Implementation of CMonitor::Process
#include "stdafx.h"
#include "izMonitor.h"
#include "AppIdRecord.h"
#include "Monitor.h"

#include <process.h>

tstring multi_sz(LPCTSTR);

///////////////////////////////////////////////////////////////////////////
// g_roots
//
// Text names of the various root keys that can be written to by the
// Registry table.  The order of the values in this array must correspond
// to the numeric values for the Root column of the Registry table.
//
LPCTSTR g_roots[] =
{
    _T("HKCR\\"),
    _T("HKCU\\"),
    _T("HKLM\\"),
    _T("HKU\\")
};

///////////////////////////////////////////////////////////////////////////
// registry_value
//
// Class that wraps some of the mess of dealing with registry values.  The
// c'tor takes a parent key and an index to obtain the value information
// with ::RegEnumValue.
//
class registry_value
{
public:
    registry_value(HKEY key, DWORD idx) : m_type(0), m_name(), m_data()
    {
        DWORD data_size = 0;
        TCHAR val_name[1024] = { 0 };
        DWORD name_size = NUM_OF(val_name);
        TRS(::RegEnumValue(key, idx, &val_name[0], &name_size, NULL, &m_type,
            NULL, &data_size));
        m_name = val_name;
        m_data.reserve(data_size);
        name_size = NUM_OF(val_name);
        TRS(::RegEnumValue(key, idx, &val_name[0], &name_size, NULL, &m_type,
            &m_data[0], &data_size));
    }
    ~registry_value() {}

    tstring name() const { return m_name; }
    DWORD type() const { return m_type; }
    DWORD reg_dword() const
    {
        return *reinterpret_cast<const DWORD *>(&m_data[0]);
    }
    tstring reg_sz() const
    {
        return reinterpret_cast<LPCTSTR>(&m_data[0]);
    }
    tstring reg_multi_sz() const
    {
        return multi_sz(reinterpret_cast<LPCTSTR>(&m_data[0]));
    }

    void add_registry(registry_table_t &registry,
        DWORD root, const tstring &base, const tstring &component);

private:
    DWORD m_type;
    tstring m_name;
    std::vector<BYTE> m_data;
};

///////////////////////////////////////////////////////////////////////////
// registry_key
//
// Class that wraps some of the mess of dealing with registy keys.  The
// c'tor takes a parent key and an index to obtain the key information with
// ::RegEnumKeyEx.
//
class registry_key
{
public:
    enum e_add_flags
    {
        add_default = 0x01,
        add_key     = 0x02,
        add_values  = 0x04,
        add_subkeys = 0x08,
        add_all = add_default | add_key | add_values | add_subkeys
    };
    registry_key(HKEY key, DWORD idx) : m_key(key), m_name()
    {
        FILETIME last_write;
        TCHAR name[512];
        DWORD num_name = NUM_OF(name);
        TCHAR class_name[512];
        DWORD num_class_name = NUM_OF(class_name);
        TRS(::RegEnumKeyEx(key, idx, &name[0], &num_name, NULL,
            &class_name[0], &num_class_name, &last_write));
        m_name = name;
    }
    ~registry_key() {}

    tstring name() const { return m_name; }

    void add_registry(registry_table_t &registry,
                      DWORD root, const tstring &base,
                      const tstring &component, DWORD flags = add_all);
    tstring default_sz() const;

private:
    HKEY m_key;
    tstring m_name;
};

///////////////////////////////////////////////////////////////////////////
// event_stack -- exception-safe wrapper around a vector of HANDLE resource
//
class event_stack : public std::vector<HANDLE>
{
public:
    typedef std::vector<HANDLE> base_t;
    event_stack() : base_t()
    {
        base_t::reserve(64);
    }
    ~event_stack()
    {
        while (base_t::size() > 0)
        {
            HANDLE event = base_t::back();
            const BOOL res = ::CloseHandle(event);
            ATLASSERT(res);
            base_t::pop_back();
        }
    }

    void push()
    {
        base_t::push_back(TWS(::CreateEvent(NULL, TRUE, FALSE, NULL)));
    }
};

///////////////////////////////////////////////////////////////////////////
// match_key -- inline helper
//
inline bool
match_key(const s_monitor_key &key, LPCTSTR name, LPCTSTR subkey)
{
    return cis_equal(name, key.m_name) && cis_equal(subkey, key.m_subkey);
}

///////////////////////////////////////////////////////////////////////////
// multi_sz -- format a MULTI_SZ string list for the Registry table
//
tstring
multi_sz(LPCTSTR multi)
{
    tstring result = multi;
    multi += _tcslen(multi)+1;
    while (*multi)
    {
        result += _T("[~]");
        result += multi;
        multi += _tcslen(multi)+1;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
// register_proc
//
// Return the result of the registration procedure for a file, or error.
//
HRESULT
register_proc(bool register_not_unregister, LPCTSTR file)
{
    dynamic_library dll(file);
    const char *proc_name = register_not_unregister ?
        "DllRegisterServer" : "DllUnregisterServer";
    typedef HRESULT (__stdcall *reg_proc)(void);
    reg_proc proc = reinterpret_cast<reg_proc>(
        ::GetProcAddress(dll, proc_name));
    return proc ? (*proc)() : E_POINTER;
}

///////////////////////////////////////////////////////////////////////////
// run_executable
//
// Call ::CreateProcess on a file and attempt to make it register itself.
//
HRESULT
run_executable(LPCTSTR file, const tstring &cmd_line)
{
    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    if (!::CreateProcess(file, const_cast<LPTSTR>(cmd_line.c_str()),
            NULL, NULL, false, 0, NULL, NULL, &si, &pi))
    {
        DWORD error = ::GetLastError();
        if (ERROR_BAD_EXE_FORMAT == error)
        {
            throw win32_error(error, _T(__FILE__), __LINE__,
                (tstring(file) +
                 _T(" is not a valid executable file.")).c_str());
        }
        else
        {
            throw win32_error(error, _T(__FILE__), __LINE__,
                _T("::CreateProcess"));
        }
    }
    bool wait = true;
    DWORD status = WAIT_TIMEOUT;
    while (WAIT_TIMEOUT == status)
    {
        status = ::WaitForSingleObject(pi.hProcess, 1000);
    }
    if (WAIT_OBJECT_0 == status)
    {
        DWORD exit_code = 0;
        TWS(::GetExitCodeProcess(pi.hProcess, &exit_code));
        return (0 == exit_code) ? S_OK : S_FALSE;
    }
    else
    {
        return E_FAIL;
    }
}

///////////////////////////////////////////////////////////////////////////
// register_server
//
// Self-Register a COM server in order to monitor its registration
// information.  Services are always EXEs, so just run it with '-service'.
// Otherwise, first try to use it like a DLL and then as an EXE.
//
HRESULT
register_server(LPCTSTR file, bool servicep)
{
    if (servicep)
    {
        return run_executable(file, tstring(file) + _T(" -service"));
    }

    const HRESULT hr = register_proc(true, file);
    return (E_POINTER == hr) ?
        run_executable(file, tstring(file) + _T(" -regserver")) : hr;
}

///////////////////////////////////////////////////////////////////////////
// unregister_server
//
// Make a self-registering COM server unregister itself.
//
HRESULT
unregister_server(LPCTSTR file)
{
    const HRESULT hr = register_proc(false, file);
    return (E_POINTER == hr) ?
        run_executable(file, tstring(file) + _T(" -unregserver")) : hr;
}

///////////////////////////////////////////////////////////////////////////
// capture_services
//
// Enumerates the currently installed services and returns a atring list
// of service names.
//
void
capture_services(string_list_t &services)
{
    windows_service_manager scm;
    {
        scm_lock lock(scm);
        DWORD num_services = 0;
        DWORD bytes_needed = 1;
        DWORD resume = 0;
        DWORD res = ERROR_MORE_DATA;
        std::vector<BYTE> buff(sizeof(ENUM_SERVICE_STATUS));
        while (bytes_needed)
        {
            ENUM_SERVICE_STATUS ess = { 0 };
            bytes_needed = 0;
            num_services = 0;
            resume = 0;
            res = ::EnumServicesStatus(scm, SERVICE_WIN32, SERVICE_STATE_ALL,
                reinterpret_cast<ENUM_SERVICE_STATUS *>(&buff[0]),
                buff.size(), &bytes_needed, &num_services,
                &resume);
            if (!res && bytes_needed)
            {
                buff.resize(buff.size() + bytes_needed);
            }
        }
        if (res)
        {
            const ENUM_SERVICE_STATUS *ess =
                reinterpret_cast<ENUM_SERVICE_STATUS *>(&buff[0]);
            for (UINT i = 0; i < num_services; i++)
            {
                services.push_back(ess->lpServiceName);
                ess++;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// value_subkey_count -- return the number of values and subkeys for a key
//
void
value_subkey_count(HKEY key, DWORD &num_values, DWORD &num_subkeys)
{
    TCHAR class_name[1024];
    DWORD num_class_name = NUM_OF(class_name);
    num_subkeys = 0;
    DWORD max_subkey_len = 0;
    DWORD max_class_len = 0;
    num_values = 0;
    DWORD max_value_name_len = 0;
    DWORD max_value_len = 0;
    DWORD security_len;
    FILETIME last_write;
    TRS(::RegQueryInfoKey(key, &class_name[0], &num_class_name,
        NULL, &num_subkeys, &max_subkey_len, &max_class_len, &num_values,
        &max_value_name_len, &max_value_len, &security_len, &last_write));
}

///////////////////////////////////////////////////////////////////////////
// reg_hex -- format a BYTE array as hex data for the Registry table
//
tstring
reg_hex(const std::vector<BYTE> &data)
{
    tostringstream str;
    for (UINT i = 0; i < data.size(); i++)
    {
        str << std::hex << std::setfill(_T('0')) << std::setw(2) << data[i];
    }
    return str.str();
}

///////////////////////////////////////////////////////////////////////////
// find_bad
//
// Helper routine to massage arbitrary strings into database table primary
// keys.  Returns the index of the first character that is not a letter, 
// not a digit, not a period and not an underscore.
//
inline tstring::size_type
find_bad(const tstring &str, tstring::size_type idx)
{
    return str.find_first_not_of(
        _T("abcdefghijklmnopqrstuvwxyz")
        _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
        _T("0123456789_."),
        idx);
}

///////////////////////////////////////////////////////////////////////////
// wit_identifier
//
// Given a wild and hairy string, massage it into a string that is a valid
// Windows Installer database type of Identifier.  Most often the value will
// be used as the primary key to a database table.  First, all 'bad'
// characters are replaced with underscores.  Next, multiple adjacent
// underscores are replaced by a single underscore.  Next, leading and
// trailing underscores are stripped.  Next, if the string ends with "_.",
// then this is replaced with "__", which cannot occur any other way.
// This routine is used to generate database table keys from registry
// key paths.
//
tstring
wit_identifier(const tstring &wild_key)
{
    tstring result = wild_key;
    tstring::size_type idx = find_bad(result, 0);
    for (; idx != tstring::npos; idx = find_bad(result, idx+1))
    {
        result[idx] = _T('_');
    }
    idx = result.find(_T("__"));
    for (; idx != tstring::npos; idx = result.find(_T("__")))
    {
        result.erase(idx, 1);
    }
    while (_T('_') == result[result.size()-1])
    {
        result.erase(result.size()-1, 1);
    }
    if ((_T('_') == result[result.size()-2]) &&
        (_T('.') == result[result.size()-1]))
    {
        result[result.size()-1] = _T('_');
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// registry_value::add_registry
//
// Add this value to the Registry table.
//
void
registry_value::add_registry(registry_table_t &registry,
                             DWORD root, const tstring &base,
                             const tstring &component)
{
    tostringstream Value;
    switch (type())
    {
    case REG_BINARY:
        Value << _T("#x") << reg_hex(m_data);
        break;

    case REG_DWORD:
        Value << _T("#") << reg_dword();
        break;

    case REG_SZ:
        Value << reg_sz();
        break;

    case REG_MULTI_SZ:
        Value << reg_multi_sz();
        break;

    default:
        ATLASSERT(false);
    }
    registry.push_back(s_registry(
        wit_identifier(g_roots[root] + base + _T("\\") +
                           (name().size() ? name() : tstring(_T(".")))),
        root, base, name(), Value.str(), component));
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// registry_key::default_sz -- return the default key value as a string
//
tstring
registry_key::default_sz() const
{
    DWORD type = 0;
    DWORD num_data = 0;
    TCHAR val_name[1024] = { 0 };
    DWORD num_value_name = NUM_OF(val_name);
    CRegKey key;
    TRS(key.Open(m_key, m_name.c_str(), KEY_READ));
    TRS(::RegEnumValue(key, 0, &val_name[0], &num_value_name, NULL,
        &type, NULL, &num_data));
    std::vector<BYTE> data(num_data);
    num_value_name = NUM_OF(val_name);
    TRS(::RegEnumValue(key, 0, &val_name[0], &num_value_name, NULL,
        &type, &data[0], &num_data));
    return tstring(reinterpret_cast<LPCTSTR>(&data[0]));
}

///////////////////////////////////////////////////////////////////////////
// registry_key::add_registry
//
// Add a registry key and all its values and subkeys to the Registry table.
// The given flags say what pieces should be added: the key itself, the
// values, the default value, and the subkeys.
//
void
registry_key::add_registry(registry_table_t &registry,
                           DWORD root, const tstring &base,
                           const tstring &component,
                           DWORD flags)
{
    CRegKey key;
    TRS(key.Open(m_key, m_name.c_str(), KEY_READ));
    DWORD num_values, num_subkeys;
    value_subkey_count(key, num_values, num_subkeys);

    if (!num_values && !num_subkeys)
    {
        if (flags & add_key)
        {
            registry.push_back(s_registry(
                wit_identifier(g_roots[root] + base + _T("\\") + name()),
                root, base + _T("\\") + name(), _T(""), _T(""), component));
        }
    }
    else
    {
        UINT i;
        const tstring subname = base + _T("\\") + name();
        if (flags & add_values)
        {
            for (i = 0; i < num_values; i++)
            {
                registry_value val(key, i);
                if (val.name().size() || (flags & add_default))
                {
                    val.add_registry(registry, root, subname, component);
                }
            }
        }
        if (flags & add_subkeys)
        {
            for (i = 0; i < num_subkeys; i++)
            {
                registry_key(key, i).
                    add_registry(registry, root, subname, component);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::snapshot
//
// Take a snapshot of this key's values and subkeys.
//
void
s_monitor_key::snapshot()
{
    TCHAR class_name[1024];
    DWORD num_class_name = NUM_OF(class_name);
    DWORD num_subkeys = 0;
    DWORD max_subkey_len = 0;
    DWORD max_class_len = 0;
    DWORD num_values = 0;
    DWORD max_value_name_len = 0;
    DWORD max_value_len = 0;
    DWORD security_len;
    FILETIME last_write;
    TRS(::RegQueryInfoKey(m_key, &class_name[0], &num_class_name,
        NULL, &num_subkeys, &max_subkey_len, &max_class_len, &num_values,
        &max_value_name_len, &max_value_len, &security_len, &last_write));
    DWORD i;
    for (i = 0; i < num_subkeys; i++)
    {
        FILETIME last_write;
        TCHAR child_name[512];
        DWORD num_name = NUM_OF(child_name);
        TCHAR class_name[512];
        DWORD num_class_name = NUM_OF(class_name);
        TRS(::RegEnumKeyEx(m_key, i, &child_name[0], &num_name, NULL,
            &class_name[0], &num_class_name, &last_write));
        m_subkeys.insert(child_name);
    }
    for (i = 0; i < num_values; i++)
    {
        DWORD type = 0;
        DWORD num_data = 0;
        TCHAR val_name[1024] = { 0 };
        DWORD num_value_name = NUM_OF(val_name);
        TRS(::RegEnumValue(m_key, i, &val_name[0], &num_value_name, NULL,
            &type, NULL, &num_data));
        m_values.insert(val_name);
    }
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_app_id
//
// Extract AppId table row entries from this monitored registry key.  The
// subkeys of this instance are the AppId GUIDs.
//
void
s_monitor_key::extract_app_id(app_id_table_t &appid,
                              registry_table_t &registry,
                              const tstring &component) const
{
    DWORD num_values, num_subkeys;
    value_subkey_count(m_key, num_values, num_subkeys);
    UINT i;
    if (num_values)
    {
        for (i = 0; i < num_values; i++)
        {
            registry_value val(m_key, i);
            if (m_values.find(val.name()) == m_values.end())
            {
                val.add_registry(registry, 0, m_name, component);
            }
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key subkey(m_key, i);
        if (m_subkeys.find(subkey.name()) == m_subkeys.end())
        {
            extract_app_id_entry(appid, registry, subkey, component);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_app_id_entry
//
// Scrape a row of the AppId table out of the registry, assuming that this
// key is HKCR\AppId, and subkey corresponds to the AppId's GUID key.  The
// appropriate values are scraped out into the AppId table and anything
// else is dumped in the Registry table.
//
void
s_monitor_key::extract_app_id_entry(app_id_table_t &app_id,
                                    registry_table_t &registry,
                                    const registry_key &subkey,
                                    const tstring &component) const
{
    CRegKey entry;
    TRS(entry.Open(m_key, subkey.name().c_str()));
    DWORD num_values, num_subkeys;
    value_subkey_count(entry, num_values, num_subkeys);
    UINT i;
    tstring remote_server;
    DWORD activate_stg = 0;
    tstring local_svc;
    tstring svc_params;
    DWORD run_as = 0;
    tstring dll_surr;

    tstring subname = _T("AppID\\") + subkey.name();
    for (i = 0; i < num_values; i++)
    {
        registry_value val(entry, i);
        if (cis_equal(_T("RemoteServerName"), val.name()))
        {
            remote_server = val.reg_sz();
        }
        else if (cis_equal(_T("ActivateAtStorage"), val.name()))
        {
            activate_stg = val.reg_dword();
        }
        else if (cis_equal(_T("LocalService"), val.name()))
        {
            local_svc = val.reg_sz();
        }
        else if (cis_equal(_T("ServiceParameters"), val.name()))
        {
            svc_params = val.reg_sz();
        }
        else if (cis_equal(_T("RunAs"), val.name()))
        {
            // bug: docs state that this is the value written under the RunAs
            // value, but the value is a string and the table column is an
            // integer.  RunAs in the registry doesn't have to be
            // InteractiveUser or NULL, so the table is overly restrictive
            // here, probably because the tables pretty much punt on security
            // and account names.
            run_as = cis_equal(_T("InteractiveUser"), val.reg_sz());
        }
        else if (cis_equal(_T("DllSurrogate"), val.name()))
        {
            dll_surr = val.reg_sz();
        }
        else
        {
            // no column in the AppId table, record in the Registry table
            val.add_registry(registry, 0, subname, component);
        }
    }

    // dump a row into the AppId table
    app_id.push_back(s_app_id(subkey.name(), remote_server, local_svc,
        svc_params, dll_surr, activate_stg, run_as));

    // add all subkeys, even though there shouldn't be any
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key(entry, i).add_registry(registry, 0, subname, component);
    }
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_class
//
// Extract rows of the Class table out of the registry.  This key instance
// is HKCR\CLSID.  Scrape out any new values into the Registry table and
// assume that new keys are CLSID guids, each corresponding to a row in the
// Class table.
//
void
s_monitor_key::extract_class(class_table_t &klass,
                             registry_table_t &registry,
                             const tstring &component,
                             const tstring &feature) const
{
    DWORD num_values, num_subkeys;
    value_subkey_count(m_key, num_values, num_subkeys);
    UINT i;
    if (num_values)
    {
        for (i = 0; i < num_values; i++)
        {
            registry_value val(m_key, i);
            if (m_values.find(val.name()) == m_values.end())
            {
                val.add_registry(registry, 0, m_name, component);
            }
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key subkey(m_key, i);
        if (m_subkeys.find(subkey.name()) == m_subkeys.end())
        {
            extract_clsid_entry(klass, registry, subkey, component, feature);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_clsid_entry
//
// Extract a row of the Class table from a HKCR\CLSID\{guid} key in the
// registry.  Anything not directly created by the Class table is dumped
// into the Registry table.
//
void
s_monitor_key::extract_clsid_entry(class_table_t &klass,
                                   registry_table_t &registry,
                                   const registry_key &subkey,
                                   const tstring &component,
                                   const tstring &feature) const
{
    CRegKey entry;
    TRS(entry.Open(m_key, subkey.name().c_str()));
    DWORD num_values, num_subkeys;
    value_subkey_count(entry, num_values, num_subkeys);
    UINT i;
    tstring context;
    tstring prog_id;
    tstring description;
    tstring app_id;
    tstring icon;
    DWORD icon_index = 0;

    const tstring subname = _T("CLSID\\") + subkey.name();
    for (i = 0; i < num_values; i++)
    {
        registry_value val(entry, i);
        if (!val.name().size())
        {
            description = val.reg_sz();
        }
        else if (cis_equal(_T("AppID"), val.name()))
        {
            app_id = val.reg_sz();
        }
        else
        {
            // no column in the Class table, record in the Registry table
            val.add_registry(registry, 0, subname, component);
        }
    }

    for (i = 0; i < num_subkeys; i++)
    {
        registry_key key(entry, i);
        if (cis_equal(_T("LocalServer"), key.name()) ||
            cis_equal(_T("LocalServer32"), key.name()) ||
            cis_equal(_T("InprocServer"), key.name()) ||
            cis_equal(_T("InprocServer32"), key.name()))
        {
            if (!context.size())
            {
                context = key.name();
                // add leftovers to Registry table
                key.add_registry(registry, 0, subname, component,
                    registry_key::add_values | registry_key::add_subkeys);
            }
            else
            {
                ::ODS(_T("COM Server context set twice!\n"));
                THR(E_UNEXPECTED);
            }
        }
        else if (cis_equal(_T("DefaultIcon"), key.name()))
        {
            icon = key.default_sz();
            const tstring::size_type comma = icon.rfind(_T(","));
            if (comma != tstring::npos)
            {
                tistringstream str(icon.substr(comma+1));
                str >> icon_index;
            }
            // add leftovers to Registry table
            key.add_registry(registry, 0, subname, component,
                registry_key::add_values | registry_key::add_subkeys);
        }
        else if (cis_equal(_T("ProgId"), key.name()))
        {
            prog_id = key.default_sz();
            // add leftovers to Registry table
            key.add_registry(registry, 0, subname, component,
                registry_key::add_values | registry_key::add_subkeys);
        }
        else if (cis_equal(_T("VersionIndependentProgId"), key.name()))
        {
            // the ProgId table takes care of the default value for this key,
            // but there may be additional keys and values lurking there
            key.add_registry(registry, 0, subname, component,
                registry_key::add_values | registry_key::add_subkeys);
        }
        else
        {
            // some random key -- put it in the Registry table verbatim
            key.add_registry(registry, 0, subname, component);
        }
    }

    // add a row to the class table for this CLSID
    klass.push_back(s_class(subkey.name(), context, component, prog_id,
        description, app_id, _T(""), icon, icon_index, _T(""), _T(""),
        feature, 0));
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_prog_id
//
// Extract new entries under HKCR\ as new rows of the ProgId table.
//
void
s_monitor_key::extract_prog_id(prog_id_table_t &prog_id,
                               registry_table_t &registry,
                               const tstring &component) const
{
    DWORD num_values, num_subkeys;
    value_subkey_count(m_key, num_values, num_subkeys);
    UINT i;
    if (num_values)
    {
        for (i = 0; i < num_values; i++)
        {
            registry_value val(m_key, i);
            if (m_values.find(val.name()) == m_values.end())
            {
                // add unexpected values to the Registry table
                val.add_registry(registry, 0, m_name, component);
            }
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key subkey(m_key, i);
        const tstring name = subkey.name();
        if (m_subkeys.find(name) == m_subkeys.end())
        {
            if (name[0] == _T('.') || (tstring::npos == name.find(_T("."))))
            {
                // doesn't look like a ProgId, add to Registry table
                subkey.add_registry(registry, 0, m_name, component);
            }
            else
            {
                // looks like a progId with at least one '.' inside the string
                extract_prog_id_entry(prog_id, registry, subkey, component);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_prog_id_entry
//
// Extract information from a new entry in HKCR as a ProgId.
//
void
s_monitor_key::extract_prog_id_entry(prog_id_table_t &prog_id,
                                     registry_table_t &registry,
                                     const registry_key &subkey,
                                     const tstring &component) const
{
    CRegKey progid;
    TRS(progid.Open(m_key, subkey.name().c_str()));
    DWORD num_values, num_subkeys;
    value_subkey_count(progid, num_values, num_subkeys);
    tstring parent;
    tstring clsid;
    tstring icon;
    DWORD icon_index = 0;

    tstring subname = m_name + _T("\\") + subkey.name();
    UINT i;
    for (i = 0; i < num_values; i++)
    {
        registry_value val(progid, i);
        if (val.name().size())
        {
            registry_value(progid, i).
                add_registry(registry, 0, subname, component);
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key progid_subkey(progid, i);
        if (cis_equal(_T("CLSID"), progid_subkey.name()))
        {
            clsid = progid_subkey.default_sz();
        }
        else if (cis_equal(_T("CurVer"), progid_subkey.name()))
        {
            parent = progid_subkey.default_sz();
        }
        else if (cis_equal(_T("DefaultIcon"), progid_subkey.name()))
        {
            const tstring def = progid_subkey.default_sz();
            const tstring::size_type comma = def.rfind(_T(","));
            icon = def.substr(0, comma);
            if (comma != tstring::npos)
            {
                tistringstream str(def.substr(comma+1));
                str >> icon_index;
            }
        }
        else
        {
            progid_subkey.add_registry(registry, 0, subname, component);
        }
    }
    prog_id.push_back(s_prog_id(subkey.name(), parent, clsid,
        subkey.default_sz(), icon, icon_index));
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_registry
//
// Extract all new things under a monitored registry key into the Registry
// table.
//
void
s_monitor_key::extract_registry(registry_table_t &registry,
                                const tstring &component) const
{
    DWORD num_values, num_subkeys;
    value_subkey_count(m_key, num_values, num_subkeys);
    UINT i;
    if (num_values)
    {
        for (i = 0; i < num_values; i++)
        {
            registry_value val(m_key, i);
            if (m_values.find(val.name()) == m_values.end())
            {
                val.add_registry(registry, 0, m_name, component);
            }
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key subkey(m_key, i);
        if (m_subkeys.find(subkey.name()) == m_subkeys.end())
        {
            subkey.add_registry(registry, 0, m_name, component);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_type_lib
//
// Scan through the monitored key HKCR\TypeLib to look for new LibId subkeys
//
void
s_monitor_key::extract_type_lib(type_lib_table_t &type_lib,
                                registry_table_t &registry,
                                const tstring &component,
                                const tstring &feature) const
{
    DWORD num_values, num_subkeys;
    value_subkey_count(m_key, num_values, num_subkeys);
    UINT i;
    if (num_values)
    {
        for (i = 0; i < num_values; i++)
        {
            registry_value val(m_key, i);
            if (m_values.find(val.name()) == m_values.end())
            {
                val.add_registry(registry, 0, m_name, component);
            }
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key subkey(m_key, i);
        if (m_subkeys.find(subkey.name()) == m_subkeys.end())
        {
            extract_type_lib_entry(type_lib, registry, subkey,
                component, feature);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// is_version_number
//
// Returns true if the string looks like a version number: it has only
// digits and periods and doesn't begin with a period.
//
bool
is_version_number(const tstring &str)
{
    return !str.size() || ((str[0] != _T('.')) &&
        (tstring::npos == str.find_first_not_of(_T("0123456789."))));
}

///////////////////////////////////////////////////////////////////////////
// is_number -- returns true if the string consists entirely of digits
//
bool
is_number(const tstring &str)
{
    return !str.size() ||
        (tstring::npos == str.find_first_not_of(_T("0123456789")));
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_type_lib_entry
//
// Extract a row of the TypeLib table from the registry.  The TypeLib
// COM registry entries are fairly deep, so we have to do quite a bit
// of work to find the entries we want to scrape out for our component.
//
// The entries have the form:
//
// TypeLib\{guid}\<major.minor>:
// \<language>\win32 = <path>
// \FLAGS = 0
// \HELPDIR = <path>
//
//      subkey is HKCR\TypeLib\{guid}
//  ver_subkey is HKCR\TypeLib\{guid}\<major.minor>
// lang_subkey is HKCR\TypeLib\{guid}\<major.minor>\<language>
//
void
s_monitor_key::extract_type_lib_entry(type_lib_table_t &type_lib,
                                      registry_table_t &registry,
                                      const registry_key &subkey,
                                      const tstring &component,
                                      const tstring &feature) const
{
    CRegKey entry;
    TRS(entry.Open(m_key, subkey.name().c_str()));
    DWORD num_values, num_subkeys;
    value_subkey_count(entry, num_values, num_subkeys);

    UINT i;
    DWORD language = 0;
    DWORD version = 0;
    tstring description;
    tstring directory;

    bool lib_found = false;
    tstring subname = _T("TypeLib\\") + subkey.name();
    for (i = 0; i < num_values; i++)
    {
        registry_value(entry, i).
            add_registry(registry, 0, subname, component);
    }

    // add all subkeys, even though there shouldn't be any
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key key(entry, i);
        if (!is_version_number(key.name()))
        {
            // add unrecognized keys to Registry table
            key.add_registry(registry, 0, subname, component);
        }
        else
        {
            // it is a version number, look for our library
            {
                tistringstream str(key.name());
                DWORD major, minor;
                str >> major;
                str.ignore(1); // consume the '.'
                str >> minor;
                version = 256*major + minor;
            }
            description = key.default_sz();

            CRegKey ver;
            ver.Open(entry, key.name().c_str());
            DWORD num_ver_values = 0;
            DWORD num_ver_subkeys = 0;
            value_subkey_count(ver, num_ver_values, num_ver_subkeys);

            tstring ver_subname = subname + _T("\\") + key.name();
            UINT j;
            for (j = 0; j < num_ver_values; j++)
            {
                registry_value val(ver, j);
                if (val.name().size())
                {
                    registry_value(ver, j).
                        add_registry(registry, 0, ver_subname, component);
                }
            }

            for (j = 0; j < num_ver_subkeys; j++)
            {
                registry_key ver_subkey(ver, j);
                if (is_number(ver_subkey.name()))
                {
                    {
                        tistringstream str(ver_subkey.name());
                        str >> language;
                    }
                    CRegKey lang;
                    TRS(lang.Open(ver, ver_subkey.name().c_str()));
                    DWORD num_lang_values = 0;
                    DWORD num_lang_subkeys = 0;
                    value_subkey_count(lang, num_lang_values,
                        num_lang_subkeys);
                    
                    tstring lang_subname =
                        ver_subname + _T("\\") + ver_subkey.name();
                    UINT k;
                    for (k = 0; k < num_lang_values; k++)
                    {
                        registry_value(lang, k).add_registry(registry, 0,
                            lang_subname, component);
                    }

                    for (k = 0; k < num_lang_subkeys; k++)
                    {
                        registry_key lang_subkey(lang, k);
                        if (cis_equal(_T("win32"), lang_subkey.name()))
                        {
                            tstring def = lang_subkey.default_sz();
                            if (cis_equal(component,
                                def.substr(def.size()- component.size())))
                            {
                                lib_found = true;
                            }
                            else
                            {
                                // add unrecognized keys to Registry table
                                lang_subkey.add_registry(registry, 0,
                                    lang_subname, component);
                            }
                        }
                        else
                        {
                            // add unrecognized keys to Registry table
                            lang_subkey.add_registry(registry, 0,
                                lang_subname, component);
                        }
                    }
                }
                else if (cis_equal(_T("FLAGS"), ver_subkey.name()))
                {
                    // the TypeLib table takes care of this, skip it
                }
                else if (cis_equal(_T("HELPDIR"), ver_subkey.name()))
                {
                    // record help directory
                    directory = ver_subkey.default_sz();
                }
                else
                {
                    // add unrecognized keys to Registry table
                    ver_subkey.
                        add_registry(registry, 0, ver_subname, component);
                }
            }
        }
    }

    // whew!
    if (lib_found)
    {
        // add a row to the class table for this LibID
        type_lib.push_back(s_type_lib(subkey.name(), language, component,
            version, description, directory, feature, 0));
    }
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// CMonitor::diff_services
//
// Compare currently installed services to a list of services previously
// installed to determine the names of services added or removed during
// registration.
//
void
CMonitor::diff_services()
{
    string_list_t current;
    capture_services(current);

    string_list_t current_not_services;
    UINT i;
    for (i = 0; i < current.size(); i++)
    {
        string_list_t::const_iterator me =
            std::find(m_services.begin(), m_services.end(), current[i]);
        if (me == m_services.end())
        {
            current_not_services.push_back(current[i]);
        }
    }

    string_list_t services_not_current;
    for (i = 0; i < m_services.size(); i++)
    {
        string_list_t::iterator me =
            std::find(current.begin(), current.end(), m_services[i]);
        if (me == current.end())
        {
            services_not_current.push_back(m_services[i]);
        }
    }

    DWORD count = 0;
    for (i = 0; i < services_not_current.size(); i++)
    {
        tostringstream key;
        key << _T("sc_") << m_component << _T("_") << ++count;
        m_service_control->Add(s_service_control(key.str(),
            services_not_current[i],
            8, // msidbServiceControlDelete
            _T(""), 0, m_component));
    }
    for (i = 0; i < current_not_services.size(); i++)
    {
        windows_service_manager scm;
        windows_service svc(scm, current_not_services[i].c_str());
        DWORD size_needed = 0;
        // this fails with buffer size too small, which is intentional
        ::QueryServiceConfig(svc, NULL, 0, &size_needed);
        std::vector<BYTE> buff(size_needed);
        QUERY_SERVICE_CONFIG *config =
            reinterpret_cast<QUERY_SERVICE_CONFIG *>(&buff[0]);
        TWS(::QueryServiceConfig(svc, config, buff.size(), &size_needed));

        tostringstream key;
        key << _T("si_") << m_component << _T("_") << (1+i);
        size_needed = 0;
        SERVICE_DESCRIPTION sd;
        TWS(::QueryServiceConfig2(svc, SERVICE_CONFIG_DESCRIPTION,
            reinterpret_cast<BYTE *>(&sd), sizeof(sd), &size_needed));
        m_service_install->Add(s_service_install(key.str(),
            current_not_services[i], config->lpDisplayName,
            config->dwServiceType, config->dwStartType,
            config->dwErrorControl, config->lpLoadOrderGroup,
            multi_sz(config->lpDependencies),
            cis_equal(_T("LocalSystem"), config->lpServiceStartName) ?
                _T("") : config->lpServiceStartName,
            _T(""), _T(""), m_component,
            sd.lpDescription ? sd.lpDescription : _T("")));
    }
}

///////////////////////////////////////////////////////////////////////////
// CMonitor::dump_tables
//
// Scrape the captured registration information to the Windows Installer
// database.
//
void
CMonitor::dump_tables()
{
    for (UINT i = 0; i < m_keys.size(); i++)
    {
        // AppId table
        if (match_key(m_keys[i], _T("HKCR"), _T("AppID")))
        {
            m_keys[i].extract_app_id(m_app_id->m_coll, m_registry->m_coll,
                m_component);
        }
        // Class table
        else if (match_key(m_keys[i], _T("HKCR"), _T("CLSID")))
        {
            m_keys[i].extract_class(m_class->m_coll, m_registry->m_coll,
                m_component, m_feature);
        }
        // TypeLib table
        else if (match_key(m_keys[i], _T("HKCR"), _T("TypeLib")))
        {
            m_keys[i].extract_type_lib(m_type_lib->m_coll, m_registry->m_coll,
                m_component, m_feature);
        }
        // ProgId, Extension table, MIME table, Verb table
        else if (match_key(m_keys[i], _T("HKCR"), _T("")))
        {
            m_keys[i].extract_prog_id(m_prog_id->m_coll, m_registry->m_coll,
                m_component);
        }
        // Registry table
        else
        {
            m_keys[i].extract_registry(m_registry->m_coll, m_component);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// CMonitor::register_threadproc
//
// Thread procedure for the registration thread.  The registration thread
// registers the COM server and sets an event to notify the main thread that
// registration has completed.
//
void __cdecl
CMonitor::register_threadproc(void *pv)
{
    ATLASSERT(pv);
    thread_args *args = static_cast<thread_args *>(pv);

    args->m_result = S_OK;
    try
    {
        com_runtime com;
        THR(register_server(args->m_file.c_str(), args->m_service));
    }
    catch (const hresult_error &bang)
    {
        args->m_result = bang.m_hr;
        args->m_bang = static_cast<source_error>(bang);
    }
    catch (const source_error &bang)
    {
        args->m_result = E_FAIL;
        args->m_bang = bang;
    }
    catch (...)
    {
        args->m_result = E_FAIL;
        args->m_bang = source_error(_T(__FILE__), __LINE__,
            _T("Unexpected exception"));
    }
    const BOOL res = ::SetEvent(args->m_event);
    ATLASSERT(res);
}

/////////////////////////////////////////////////////////////////////////////
// CMonitor::Process
//
// Process the given file as a COM server and self-register it.  Using the
// information written into the registry during self-registration, extract
// rows into the various Windows Installer database tables.  If the file
// is a service, then service changes are written into the service related
// database tables.
//
STDMETHODIMP
CMonitor::Process(BSTR file, BOOL service, BSTR component, BSTR feature)
{
    USES_CONVERSION;
    m_file = W2T(file);
    m_service = (service != 0);
    m_component = W2T(component);
    m_feature = W2T(feature);

    THR_TRY();

    // clear out anything in database tables from last run
    m_app_id->Clear();
    m_class->Clear();
    m_prog_id->Clear();
    m_registry->Clear();
    m_service_control->Clear();
    m_service_install->Clear();
    m_type_lib->Clear();

    event_stack events;
    events.push();

    // unregister the existing server so that our snapshot shows the new keys
    THR(unregister_server(m_file.c_str()));

    // if necessary, capture a list of system services
    if (m_service)
    {
        capture_services(m_services);
    }

    // start monitoring the registry keys
    UINT i;
    for (i = 0; i < m_keys.size(); i++)
    {
        const HANDLE event = TWS(::CreateEvent(NULL, TRUE, FALSE, NULL));
        TRS(::RegNotifyChangeKeyValue(m_keys[i].m_key, FALSE,
            REG_NOTIFY_CHANGE_NAME, event, TRUE));
        events.push_back(event);
        m_keys[i].snapshot();
    }

    // launch the registration thread
    thread_args args(m_file.c_str(), events[0], m_service);
    DWORD thread_id = 0;
    unsigned long thread_handle =
        TCR(_beginthread(register_threadproc, 0, &args));

    // keep processing notifications until the registration thread completes
    bool more = true;
    while (more)
    {
        for (UINT offset = 0; offset < events.size(); offset += 64)
        {
            const UINT count = min(events.size() - offset, 64);
            const DWORD res =
                ::WaitForMultipleObjects(count, &events[offset], FALSE, 200);
            if ((res >= WAIT_OBJECT_0) && (res-WAIT_OBJECT_0 < count))
            {
                const DWORD which = res-WAIT_OBJECT_0;
                if (which)
                {
                    s_monitor_key &target = m_keys[offset + which - 1];
                    target.m_modified = true;
                    TWS(::ResetEvent(events[offset + which]));
                }
                else
                {
                    // event 0 tells us the thread is done.
                    more = false;
                }
            }
            else if (WAIT_TIMEOUT != res)
            {
                // ::WaitForMultipleObjects freaked
                tostringstream buff;
                for (UINT i = 0; i < events.size(); i++)
                {
                    buff << i << _T(": ") << (void *)(events[i])
                        << _T("\n");
                }
                ::ODS(buff);
                TWS(::GetLastError());
                ATLASSERT(false);
                more = false;
            }
        }
    }

    if (FAILED(args.m_result))
    {
        return Error(args.m_bang.m_msg.c_str(), IID_IMonitor, args.m_result);
    }

    // dump the gathered information
    dump_tables();
    if (m_service)
    {
        // ServiceInstall table, ServiceControl table
        diff_services();
    }

    THR_CATCH_EI(IID_IMonitor);

    return S_OK;
}
