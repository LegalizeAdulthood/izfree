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
// extract.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

LPCTSTR g_roots[] =
{
    _T("HKCR\\"),
    _T("HKCU\\"),
    _T("HKLM\\"),
    _T("HKU\\")
};

///////////////////////////////////////////////////////////////////////////
// thread_args
//
// Structure containing arguments passed to the registration thread.
//
struct thread_args
{
    LPCTSTR m_file;
    HANDLE m_event;
    bool m_servicep;
};

struct s_app_id
{
    s_app_id(const tstring &app_id, const tstring &remote_server,
        const tstring &local_service, const tstring &service_params,
        const tstring &dll_surrogate, DWORD activate_at_storage,
        DWORD run_as)
        : m_app_id(app_id),
        m_remote_server_name(remote_server),
        m_local_service(local_service),
        m_service_parameters(service_params),
        m_activate_at_storage(activate_at_storage),
        m_run_as_interactive_user(run_as)
    {}
    tstring m_app_id;
    tstring m_remote_server_name;
    tstring m_local_service;
    tstring m_service_parameters;
    tstring m_dll_surrogate;
    DWORD m_activate_at_storage;
    DWORD m_run_as_interactive_user;
};

struct s_class
{
    s_class(const tstring &clsid, const tstring &context,
            const tstring &component, const tstring &prog_id,
            const tstring &description, const tstring &app_id,
            const tstring &file_mask, const tstring &icon,
            DWORD icon_index, const tstring &def_inproc_handler,
            const tstring &argument, const tstring &feature,
            DWORD attributes)
        : m_clsid(clsid),
        m_context(context),
        m_component(component),
        m_prog_id_default(prog_id),
        m_description(description),
        m_app_id(app_id),
        m_file_type_mask(file_mask),
        m_icon(icon),
        m_icon_index(icon_index),
        m_def_inproc_handler(def_inproc_handler),
        m_argument(argument),
        m_feature(feature),
        m_attributes(attributes)
    {}
    tstring m_clsid;
    tstring m_context;
    tstring m_component;
    tstring m_prog_id_default;
    tstring m_description;
    tstring m_app_id;
    tstring m_file_type_mask;
    tstring m_icon;
    DWORD m_icon_index;
    tstring m_def_inproc_handler;
    tstring m_argument;
    tstring m_feature;
    DWORD m_attributes;
};

struct s_registry
{
    s_registry(const tstring &registry, DWORD root, const tstring &key,
               const tstring &name, const tstring &value,
               const tstring &component)
        : m_registry(registry), m_root(root), m_key(key), m_name(name),
        m_value(value), m_component(component)
    {}
    ~s_registry() {}

    tstring m_registry;
    DWORD m_root;
    tstring m_key;
    tstring m_name;
    tstring m_value;
    tstring m_component;
};

struct s_prog_id
{
    s_prog_id(const tstring &prog_id, const tstring &parent,
              const tstring &class_key, const tstring &description,
              const tstring &icon, DWORD icon_index)
        : m_prog_id(prog_id),
        m_prog_id_parent(parent),
        m_class(class_key),
        m_description(description),
        m_icon(icon),
        m_icon_index(icon_index)
    {}
    tstring m_prog_id;
    tstring m_prog_id_parent;
    tstring m_class;
    tstring m_description;
    tstring m_icon;
    DWORD m_icon_index;
};

struct s_service_install
{
    s_service_install(const tstring &key, const tstring &name,
                      const tstring &display_name, DWORD service_type,
                      DWORD start_type, DWORD error_control,
                      const tstring &load_order_group,
                      const tstring &dependencies, const tstring &start_name,
                      const tstring &password, const tstring &arguments,
                      const tstring &component, const tstring &description)
        : m_service_install(key),
        m_name(name),
        m_display_name(display_name),
        m_service_type(service_type),
        m_start_type(start_type),
        m_error_control(error_control),
        m_load_order_group(load_order_group),
        m_dependencies(dependencies),
        m_start_name(start_name),
        m_password(password),
        m_arguments(arguments),
        m_component(component),
        m_description(description)
    {}
    tstring m_service_install;
    tstring m_name;
    tstring m_display_name;
    DWORD m_service_type;
    DWORD m_start_type;
    DWORD m_error_control;
    tstring m_load_order_group;
    tstring m_dependencies;
    tstring m_start_name;
    tstring m_password;
    tstring m_arguments;
    tstring m_component;
    tstring m_description;
};

tstring
reg_hex()
{
    return _T("deadbeef");
}

tstring
reg_multi_sz()
{
    return _T("[~]");
}

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
    DWORD reg_dword() const { return *reinterpret_cast<const DWORD *>(&m_data[0]); }
    tstring reg_sz() const { return reinterpret_cast<LPCTSTR>(&m_data[0]); }

    void add_registry(DWORD root, const tstring &base, const tstring &component);

private:
    DWORD m_type;
    tstring m_name;
    std::vector<BYTE> m_data;
};

class registry_key
{
public:
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

    void add_registry(DWORD root, const tstring &base, const tstring &component);
    tstring default_sz() const;

private:
    HKEY m_key;
    tstring m_name;
};

std::vector<s_app_id>           g_app_id_table;
std::vector<s_class>            g_class_table;
std::vector<s_registry>         g_registry_table;
std::vector<s_prog_id>          g_prog_id_table;
std::vector<s_service_install>  g_service_install_table;

tstring sq(const tstring &);

inline bool
cis_equal(LPCTSTR lhs, const tstring &rhs)
{
    return (_tcslen(lhs) == rhs.size()) && (_tcsicmp(lhs, rhs.c_str()) == 0);
}

void
registry_row(const tstring &registry, DWORD root, const tstring &key,
             const tstring &name, const tstring &value,
             const tstring &component)
{
    g_registry_table.
        push_back(s_registry(registry, root, key, name, value, component));

    tostringstream msg;
    msg << _T("Registry: ") << sq(registry) << _T(", ") << root << _T(", ")
        << sq(key) << _T(", ") << sq(name) << _T(", ")
        << sq(value) << _T(", ") << sq(component) << _T("\n");
    ::ODS(msg);
}

void
app_id_row(const tstring &app_id, const tstring &remote_server,
           const tstring &local_service, const tstring &service_params,
           const tstring &dll_surrogate, DWORD activate_at_storage,
           DWORD run_as)
{
    g_app_id_table.push_back(s_app_id(app_id, remote_server, local_service,
        service_params, dll_surrogate, activate_at_storage, run_as));
        
    tostringstream msg;
    msg << _T("AppId: ") << sq(app_id) << _T(", ") << sq(remote_server)
        << _T(", ") << sq(local_service) << _T(", ") << sq(service_params)
        << _T(", ") << sq(dll_surrogate) << _T(", ") << activate_at_storage
        << _T(", ") << run_as << _T("\n");
    ::ODS(msg);
}

void
class_row(const tstring &clsid, const tstring &context,
          const tstring &component, const tstring &prog_id,
          const tstring &description, const tstring &app_id,
          const tstring &file_mask, const tstring &icon,
          DWORD icon_index, const tstring &def_inproc_handler,
          const tstring &argument, const tstring &feature,
          DWORD attributes)
{
    g_class_table.push_back(s_class(clsid, context, component, prog_id,
        description, app_id, file_mask, icon, icon_index, def_inproc_handler,
        argument, feature, attributes));
    tostringstream msg;
    msg << _T("Class: ") << sq(clsid) << _T(", ") << sq(context)
        << _T(", ") << sq(component) << _T(", ") << sq(prog_id)
        << _T(", ") << sq(description) << _T(", ") << sq(app_id)
        << _T(", ") << sq(file_mask) << _T(", ") << sq(icon)
        << _T(", ") << icon_index << _T(", ") << sq(def_inproc_handler)
        << _T(", ") << sq(argument) << _T(", ") << sq(feature)
        << _T(", ") << attributes << _T("\n");
    ::ODS(msg);
}

///////////////////////////////////////////////////////////////////////////
// check_registry
//
// Checks the return values from ::RegXXX functions.  These functions don't
// set the value of ::GetLastError(), so they have to be treated special.
// Throw an exception on failure.
//
LONG
check_registry(LONG result, LPCTSTR file, UINT line, LPCTSTR context)
{
    if (ERROR_SUCCESS != result)
    {
        tostringstream buff;
        buff << file << _T("(") << line << _T("): ") << context << _T("\n");
        TCHAR msg[1024] = { 0 };
        const DWORD count = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, result, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &msg[0], NUM_OF(msg), NULL);
        if (count)
        {
            buff << _T("   '") << msg << _T("\n");
        }
        ::ODS(buff);
        throw win32_error(result, file, line, context);
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
// check_hr
//
// Throw an exception on a FAILED HRESULT.
//
HRESULT
check_hr(HRESULT hr, LPCTSTR file, UINT line, LPCTSTR context)
{
    if (FAILED(hr))
    {
        tostringstream buff;
        buff << file << _T("(") << line << _T("): ") << context << _T("\n");
        TCHAR msg[1024] = { 0 };
        const DWORD count = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &msg[0], NUM_OF(msg), NULL);
        if (count)
        {
            buff << _T("   '") << msg << _T("\n");
        }
        ::ODS(buff);
        throw hresult_error(hr, file, line, context);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////
// dynamic_library::dynamic_library
//
// Create a wrapper for a dynamic library if we could load it.
//
dynamic_library::dynamic_library(LPCTSTR file)
    : m_file(file),
    m_library(TWS(::LoadLibrary(file)))
{
}

///////////////////////////////////////////////////////////////////////////
// dynamic_library::~dynamic_library
//
// Free the library loaded in the c'tor.
//
dynamic_library::~dynamic_library()
{
    const BOOL res = ::FreeLibrary(m_library);
    ATLASSERT(res);
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
    TWS(::CreateProcess(file, const_cast<LPTSTR>(cmd_line.c_str()), NULL,
        NULL, false, 0, NULL, NULL, &si, &pi));
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
// dump_service
//
// Dumps information about a newly created service
//
void
dump_service(const tstring &name)
{
    windows_service_manager scm;
    windows_service service(scm, name.c_str());
    DWORD size_needed = 0;
    // this fails with buffer size too small, which is intentional
    ::QueryServiceConfig(service, NULL, 0, &size_needed);
    std::vector<BYTE> buff(size_needed);
    QUERY_SERVICE_CONFIG *config =
        reinterpret_cast<QUERY_SERVICE_CONFIG *>(&buff[0]);
    TWS(::QueryServiceConfig(service, config, buff.size(), &size_needed));
}

///////////////////////////////////////////////////////////////////////////
// diff_services
//
// Compare currently installed services to a list of services previously
// installed to determine the names of services added or removed during
// registration.
//
void
diff_services(const string_list_t &services)
{
    string_list_t current;
    capture_services(current);

    string_list_t current_not_services;
    UINT i;
    for (i = 0; i < current.size(); i++)
    {
        string_list_t::const_iterator me =
            std::find(services.begin(), services.end(), current[i]);
        if (me == services.end())
        {
            current_not_services.push_back(current[i]);
        }
    }

    string_list_t services_not_current;
    for (i = 0; i < services.size(); i++)
    {
        string_list_t::iterator me =
            std::find(current.begin(), current.end(), services[i]);
        if (me == current.end())
        {
            services_not_current.push_back(services[i]);
        }
    }

    for (i = 0; i < services_not_current.size(); i++)
    {
        ::ODS(_T("- ") + services_not_current[i] + _T("\n"));
    }
    for (i = 0; i < current_not_services.size(); i++)
    {
        ::ODS(_T("+ ") + current_not_services[i] + _T("\n"));
        dump_service(current_not_services[i]);
    }
}

///////////////////////////////////////////////////////////////////////////
// enum_values
//
// Enumerate values in the registry.
//
void
enum_values(HKEY key, const tstring &name, UINT num_values)
{
    if (num_values)
    {
        ::ODS(_T("[") + name + _T("]\n"));
    }
    DWORD i;
    for (i = 0; i < num_values; i++)
    {
        DWORD type = 0;
        DWORD num_data = 0;
        TCHAR val_name[1024] = { 0 };
        DWORD num_value_name = NUM_OF(val_name);
        TRS(::RegEnumValue(key, i, &val_name[0], &num_value_name, NULL,
            &type, NULL, &num_data));
        std::vector<BYTE> data(num_data);
        num_value_name = NUM_OF(val_name);
        TRS(::RegEnumValue(key, i, &val_name[0], &num_value_name, NULL,
            NULL, &data[0], &num_data));
        tostringstream buff;
        buff << _T("\"") << val_name << _T("\" = ");
        switch (type)
        {
        case REG_DWORD:
            buff << *reinterpret_cast<DWORD *>(&data[0]);
            break;

        case REG_SZ:
            buff << _T("\"") << reinterpret_cast<LPTSTR>(&data[0]) << _T("\"");
            break;

        default:
            ATLASSERT(false);
        }
        buff << _T("\n");
        ::ODS(buff);
    }
}

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
// enum_registry
//
// Enumerate a hive in the registry.
//
void
enum_registry(HKEY key, const tstring &name)
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
    long res = ::RegQueryInfoKey(key, &class_name[0], &num_class_name,
        NULL, &num_subkeys, &max_subkey_len, &max_class_len, &num_values,
        &max_value_name_len, &max_value_len, &security_len, &last_write);
    if (ERROR_FILE_NOT_FOUND == res)
    {
        return;
    }

    enum_values(key, name, num_values);
    std::vector<tstring> children;
    UINT i;
    for (i = 0; i < num_subkeys; i++)
    {
        FILETIME last_write;
        TCHAR child_name[512];
        DWORD num_name = NUM_OF(child_name);
        TCHAR class_name[512];
        DWORD num_class_name = NUM_OF(class_name);
        TRS(::RegEnumKeyEx(key, i, &child_name[0], &num_name, NULL,
            &class_name[0], &num_class_name, &last_write));
        children.push_back(child_name);
    }
    for (i = 0; i < num_subkeys; i++)
    {
        tstring child = children.back();
        children.pop_back();
        CRegKey subkey;
        TRS(subkey.Open(key, child.c_str(), KEY_READ));
        enum_registry(subkey, name + _T("\\") + child);
    }
}

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

void
dbg_table(const s_monitor_key &key, LPCTSTR header)
{
    ::ODS(_T("\n") +
        (header + (_T(": ") + key.m_name)) + _T("\\") + key.m_subkey + _T("\n"));
}

void
s_monitor_key::extract_app_id(const tstring &component) const
{
    dbg_table(*this, _T("AppId Table"));

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
                val.add_registry(0, m_name, component);
            }
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key subkey(m_key, i);
        if (m_subkeys.find(subkey.name()) == m_subkeys.end())
        {
            extract_app_id_entry(subkey, component);
        }
    }
}

inline tstring::size_type
find_bad(const tstring &str, tstring::size_type idx)
{
    return str.find_first_not_of(
        _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"), idx);
}

tstring
primary_key(const tstring &wild_key)
{
    tstring result = wild_key;
    tstring::size_type idx;
    for (idx = find_bad(result, 0);
         idx != tstring::npos;
         idx = find_bad(result, idx+1))
    {
        result[idx] = _T('_');
    }
    for (idx = result.find(_T("__"), 0);
         idx != tstring::npos;
         idx = result.find(_T("__"), idx))
    {
        result.erase(idx, 1);
    }
    while (_T('_') == result[result.size()-1])
    {
        result.erase(result.size()-1, 1);
    }
    return result;
}

inline tstring sq(const tstring &str) { return _T("'") + str + _T("'"); }

void
registry_value::add_registry(DWORD root, const tstring &base,
                             const tstring &component)
{
    tstring Registry;
    tstring Name;
    tostringstream Value;

    Registry = primary_key(g_roots[root] + base);
    Name = name();
    //buff << _T("[") << base << _T("]\n\"") << name() << _T("\" = ");
    switch (type())
    {
    case REG_BINARY:
        Value << _T("#x") << reg_hex();
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
    ::registry_row(Registry, root, base, Name, Value.str(), component);
}

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

void
registry_key::add_registry(DWORD root, const tstring &base,
                           const tstring &component)
{
    CRegKey key;
    TRS(key.Open(m_key, m_name.c_str(), KEY_READ));
    DWORD num_values, num_subkeys;
    value_subkey_count(key, num_values, num_subkeys);

    if (!num_values && !num_subkeys)
    {
        ::registry_row(primary_key(g_roots[root] + base + _T("\\") + name()),
            root, base + _T("\\") + name(), _T(""), _T(""), component);
    }
    else
    {
        UINT i;
        const tstring subname = base + _T("\\") + name();
        for (i = 0; i < num_values; i++)
        {
            registry_value(key, i).add_registry(root, subname, component);
        }
        for (i = 0; i < num_subkeys; i++)
        {
            registry_key(key, i).add_registry(root, subname, component);
        }
    }
}

/*
    for each subkey in AppId
        guid = subkey
        description = default value
        foreach (name, value) in guid
            if (name = "RemoteServerName") then
                remote_server_name = value
            else if (name = "ActivateAtStorage") then
                activate_at_storage = value
            else if (name = "LocalService") then
                local_service = value
            else if (name = "ServiceParameters") then
                service_parameters = value
            else if (name = "RunAs") then
                run_as_interactive_user = value
            else if (name = "DllSurrogate") then
                dll_surrogate = value
            else
                add_registry name, value
            endif
        next
        add_app_id guid, remote_server_name, local_service, service_parameters,
            dll_surrogate, activate_at_storage, run_as_interactive_user
    next
*/
void
s_monitor_key::extract_app_id_entry(const registry_key &subkey,
                                    const tstring &component) const
{
    CRegKey entry;
    TRS(entry.Open(m_key, subkey.name().c_str()));
    DWORD num_values, num_subkeys;
    value_subkey_count(entry, num_values, num_subkeys);
    UINT i;
    tstring AppId;
    tstring RemoteServerName;
    DWORD ActivateAtStorage = 0;
    tstring LocalService;
    tstring ServiceParameters;
    DWORD RunAs = 0;
    tstring DllSurrogate;

    AppId = subkey.name();
    tstring subname = _T("AppID\\");
    for (i = 0; i < num_values; i++)
    {
        registry_value val(entry, i);
        if (cis_equal(_T("RemoteServerName"), val.name()))
        {
            RemoteServerName = val.reg_sz();
        }
        else if (cis_equal(_T("ActivateAtStorage"), val.name()))
        {
            ActivateAtStorage = val.reg_dword();
        }
        else if (cis_equal(_T("LocalService"), val.name()))
        {
            LocalService = val.reg_sz();
        }
        else if (cis_equal(_T("ServiceParameters"), val.name()))
        {
            ServiceParameters = val.reg_sz();
        }
        else if (cis_equal(_T("RunAs"), val.name()))
        {
            RunAs = cis_equal(_T("InteractiveUser"), val.reg_sz());
        }
        else if (cis_equal(_T("DllSurrogate"), val.name()))
        {
            DllSurrogate = val.reg_sz();
        }
        else
        {
            // no column in the AppId table, record in the Registry table
            val.add_registry(0, subname + subkey.name(), component);
        }
    }

    ::app_id_row(AppId, RemoteServerName, LocalService, ServiceParameters,
        DllSurrogate, ActivateAtStorage, RunAs);

    // add all subkeys, even though there shouldn't be any
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key(entry, i).
            add_registry(0, subname + subkey.name(), component);
    }
}

void
s_monitor_key::extract_class(const tstring &component) const
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
                val.add_registry(0, m_name, component);
            }
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key subkey(m_key, i);
        if (m_subkeys.find(subkey.name()) == m_subkeys.end())
        {
            extract_clsid_entry(subkey, component);
        }
    }
}

void
s_monitor_key::extract_clsid_entry(const registry_key &subkey,
                                   const tstring &component) const
{
    CRegKey entry;
    TRS(entry.Open(m_key, subkey.name().c_str()));
    DWORD num_values, num_subkeys;
    value_subkey_count(entry, num_values, num_subkeys);
    UINT i;
    tstring CLSID;
    tstring Context;
    tstring ProgId_Default;
    tstring Description;
    tstring AppId;
    tstring FileTypeMask;
    tstring Icon;
    DWORD IconIndex = 0;
    tstring DefInprocHandler;
    tstring Argument;
    tstring Feature;
    DWORD Attributes = 0;

    CLSID = subkey.name();
    tstring subname = _T("CLSID\\") + CLSID;
    for (i = 0; i < num_values; i++)
    {
        registry_value val(entry, i);
        if (!val.name().size())
        {
            Description = val.reg_sz();
        }
        else if (cis_equal(_T("AppID"), val.name()))
        {
            AppId = val.reg_sz();
        }
        else
        {
            // no column in the AppId table, record in the Registry table
            val.add_registry(0, subname, component);
        }
    }

    // add all subkeys, even though there shouldn't be any
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key key(entry, i);
        if (cis_equal(_T("LocalServer"), key.name()) ||
            cis_equal(_T("LocalServer32"), key.name()) ||
            cis_equal(_T("InprocServer"), key.name()) ||
            cis_equal(_T("InprocServer32"), key.name()))
        {
            if (!Context.size())
            {
                Context = key.name();
                // key.add_registry(0, subname, component, false);
            }
            else
            {
                ::ODS(_T("COM Server context set twice!\n"));
                THR(E_UNEXPECTED);
            }
        }
        else if (cis_equal(_T("DefaultIcon"), key.name()))
        {
            Icon = key.default_sz();
            // key.add_registry(0, subname, component, false);
        }
        else if (cis_equal(_T("ProgId"), key.name()))
        {
            ProgId_Default = key.default_sz();
            // key.add_registry(0, subname, component, false);
        }
        else
        {
            key.add_registry(0, subname, component);
        }
    }
    ::class_row(CLSID, Context, component, ProgId_Default, Description,
        AppId, FileTypeMask, Icon, IconIndex, DefInprocHandler, Argument,
        Feature, Attributes);
}

void
s_monitor_key::extract_prog_id(const tstring &component) const
{
}

void
s_monitor_key::extract_registry(const tstring &component) const
{
}

void
s_monitor_key::extract_typelib(const tstring &component) const
{
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::diff
//
// Report a difference between this key's snapshot and its current settings
// in the registry.
//
#if 0
void
s_monitor_key::diff() const
{
    DWORD num_values, num_subkeys;
    value_subkey_count(m_key, num_values, num_subkeys);
    UINT i;
    if (num_values)
    {
        tostringstream buff;
        buff << _T("[") << m_name << _T("]\n");
        UINT num_new = 0;

        for (i = 0; i < num_values; i++)
        {
            registry_value val(m_key, i);
            if (m_values.find(val.name()) == m_values.end())
            {
                num_new++;

                buff << _T("\"") << val.name() << _T("\" = ");
                switch (val.type())
                {
                case REG_DWORD:
                    buff << val.reg_dword();
                    break;

                case REG_SZ:
                    buff << _T("\"") << val.reg_sz() << _T("\"");
                    break;

                default:
                    ATLASSERT(false);
                }
                buff << _T("\n");
            }
        }
        if (num_new)
        {
            ::ODS(buff);
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key subkey(m_key, i);
        if (m_subkeys.find(subkey.name()) == m_subkeys.end())
        {
            CRegKey new_key;
            TRS(new_key.Open(m_key, subkey.name().c_str()));
            tstring name(m_name);
            if (m_subkey.length())
            {
                name += _T("\\") + m_subkey;
            }
            enum_registry(new_key, name + _T("\\") + subkey.name());
        }
    }
}
#endif

///////////////////////////////////////////////////////////////////////////
// reg_monitor::reg_monitor
//
// C'tor reserves space and creates an event for notification.
//
reg_monitor::reg_monitor(LPCTSTR file, bool servicep)
    : m_file(file),
    m_servicep(servicep),
    m_keys(),
    m_events(),
    m_values(),
    m_subkeys()
{
    m_keys.reserve(64);
    m_events.reserve(64);
    m_events.push_back(TWS(::CreateEvent(NULL, TRUE, FALSE, NULL)));
}

///////////////////////////////////////////////////////////////////////////
// reg_monitor::add
//
// Add a registry key/subkey for monitoring.
//
reg_monitor &
reg_monitor::add(HKEY key, LPCTSTR name, LPCTSTR subkey)
{
    ATLASSERT(key && name);
    if (subkey)
    {
        CRegKey tmp;
        TRS(tmp.Open(key, subkey, KEY_READ));
        m_keys.push_back(s_monitor_key(tmp.Detach(), name, subkey));
    }
    else
    {
        m_keys.push_back(s_monitor_key(key, name));
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////
// reg_monitor::register_threadproc
//
// Thread procedure for the registration thread.  The registration thread
// registers the COM server and sets an event to notify the main thread that
// registration has completed.
//
void __cdecl
reg_monitor::register_threadproc(void *pv)
{
    ATLASSERT(pv);
    try
    {
        thread_args *args = static_cast<thread_args *>(pv);
        THR(register_server(args->m_file, args->m_servicep));
        TWS(::SetEvent(args->m_event));
    }
    catch (...)
    {
        ATLASSERT(false);
    }
}

///////////////////////////////////////////////////////////////////////////
// reg_monitor::process
//
// Perform the registration process for a COM server and monitor the current
// set of registry keys for changes.  Report the changes after the COM server
// has been registered.  The changes contain the registration information for
// the COM server.
//
void
reg_monitor::process()
{
    // unregister the existing server so that our snapshot shows the new keys
    THR(unregister_server(m_file.c_str()));

    // if necessary, capture a list of system services
    string_list_t services;
    if (m_servicep)
    {
        capture_services(services);
    }

    // start monitoring the registry keys
    UINT i;
    for (i = 0; i < m_keys.size(); i++)
    {
        const HANDLE event = TWS(::CreateEvent(NULL, TRUE, FALSE, NULL));
        TRS(::RegNotifyChangeKeyValue(m_keys[i].m_key, FALSE,
            REG_NOTIFY_CHANGE_NAME, event, TRUE));
        m_events.push_back(event);
        m_keys[i].snapshot();
    }

    // launch the registration thread
    thread_args args = { m_file.c_str(), m_events[0], m_servicep };
    DWORD thread_id = 0;
    unsigned long thread_handle =
        TCR(_beginthread(register_threadproc, 0, &args));

    // keep processing notifications until the registration thread completes
    bool more = true;
    while (more)
    {
        const DWORD res = ::WaitForMultipleObjects(m_events.size(),
            &m_events[0], FALSE, INFINITE);
        if ((res >= WAIT_OBJECT_0) && (res-WAIT_OBJECT_0 < m_events.size()))
        {
            const DWORD which = res-WAIT_OBJECT_0;
            if (which)
            {
                s_monitor_key &target = m_keys[which-1];
                target.m_modified = true;
                TWS(::ResetEvent(m_events[which]));
                ::ODS(target.m_name + _T("\\") + target.m_subkey +
                    _T(" changed.\n"));
            }
            else
            {
                // event 0 tells us the thread is done.
                more = false;
            }
        }
        else
        {
            // ::WaitForMultipleObjects freaked
            tostringstream buff;
            for (UINT i = 0; i < m_events.size(); i++)
            {
                buff << i << _T(": ") << (void *)(m_events[i])
                    << _T("\n");
            }
            ::ODS(buff);
            TWS(::GetLastError());
            ATLASSERT(false);
            more = false;
        }
    }

    // dump the gathered information
    dump_tables(services);
}

///////////////////////////////////////////////////////////////////////////
// match_key -- inline helper
//
inline bool
match_key(const s_monitor_key &key, LPCTSTR name, LPCTSTR subkey)
{
    return cis_equal(name, key.m_name) && cis_equal(subkey, key.m_subkey);
}

///////////////////////////////////////////////////////////////////////////
// reg_monitor::dump_tables
//
// Dump the captured registration information to the Windows Installer
// database.
void
reg_monitor::dump_tables(const string_list_t &services)
{
    const tstring::size_type whack = m_file.rfind(_T("\\"));
    const tstring base = (tstring::npos == whack) ?
        m_file : m_file.substr(whack+1);
    for (UINT i = 0; i < m_keys.size(); i++)
    {
        // AppId table
        if (match_key(m_keys[i], _T("HKCR"), _T("AppID")))
        {
            m_keys[i].extract_app_id(base);
        }
        // Class table
        else if (match_key(m_keys[i], _T("HKCR"), _T("CLSID")))
        {
            m_keys[i].extract_class(base);
        }
        // TypeLib table
        else if (match_key(m_keys[i], _T("HKCR"), _T("Interface")))
        {
            // skip these
            1;
        }
        else if (match_key(m_keys[i], _T("HKCR"), _T("TypeLib")))
        {
            m_keys[i].extract_typelib(base);
        }
        // ProgId, Extension table, MIME table, Verb table
        else if (match_key(m_keys[i], _T("HKCR"), _T("")))
        {
            m_keys[i].extract_prog_id(base);
        }
        // Registry table
        else
        {
            m_keys[i].extract_registry(base);
        }
    }
    if (m_servicep)
    {
        // ServiceInstall table, ServiceControl table
        ::ODS(_T("\nServiceInstall, ServiceControl Table\n"));
        diff_services(services);
    }
}

///////////////////////////////////////////////////////////////////////////
// WinMain -- test the whole thing with a stub service EXE COM server
//
int APIENTRY
WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    bool servicep = true;
    LPCTSTR extract_file = 
        _T("C:\\tmp\\service\\Debug\\service.exe");

    try
    {
        com_runtime com;
        reg_monitor monitor(extract_file, servicep);
        monitor.add(HKEY_CLASSES_ROOT, _T("HKCR"), _T("AppID"))
            .add(HKEY_CLASSES_ROOT, _T("HKCR"), _T("CLSID"))
            .add(HKEY_CLASSES_ROOT, _T("HKCR"), _T("Interface"))
            .add(HKEY_CLASSES_ROOT, _T("HKCR"), _T("TypeLib"))
            .add(HKEY_CLASSES_ROOT, _T("HKCR"))
            .add(HKEY_CURRENT_CONFIG, _T("HKEY_CURRENT_CONFIG"))
            .add(HKEY_CURRENT_USER, _T("HKCU"), _T("Software"))
            .add(HKEY_CURRENT_USER, _T("HKCU"))
            .add(HKEY_LOCAL_MACHINE, _T("HKLM"), _T("Software"))
            .add(HKEY_LOCAL_MACHINE, _T("HKLM"))
            .add(HKEY_USERS, _T("HKEY_USERS"));
        monitor.process();
    }
    catch (...)
    {
        ATLASSERT(false);
        return -1;
    }

    return 0;
}
