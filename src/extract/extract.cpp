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
#include <iomanip>

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

///////////////////////////////////////////////////////////////////////////
// s_app_id -- structure to hold a row in the AppId table
//
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
    ~s_app_id() {}

    tstring m_app_id;
    tstring m_remote_server_name;
    tstring m_local_service;
    tstring m_service_parameters;
    tstring m_dll_surrogate;
    DWORD m_activate_at_storage;
    DWORD m_run_as_interactive_user;
};

///////////////////////////////////////////////////////////////////////////
// s_class -- structure to hold a row in the Class table
//
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
    ~s_class() {}

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

///////////////////////////////////////////////////////////////////////////
// s_registry -- structure to hold a row in the Registry table
//
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

///////////////////////////////////////////////////////////////////////////
// s_prog_id -- structure to hold a row in the ProgId table
//
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
    ~s_prog_id() {}

    tstring m_prog_id;
    tstring m_prog_id_parent;
    tstring m_class;
    tstring m_description;
    tstring m_icon;
    DWORD m_icon_index;
};

///////////////////////////////////////////////////////////////////////////
// s_type_lib -- structure to hold a row in the TypeLib table
//
struct s_type_lib
{
    s_type_lib(const tstring &lib_id, DWORD language, const tstring &component,
               DWORD version, const tstring &description,
               const tstring &directory, const tstring &feature, DWORD cost)
        : m_lib_id(lib_id),
        m_language(language),
        m_component(component),
        m_version(version),
        m_description(description),
        m_directory(directory),
        m_feature(feature),
        m_cost(cost)
    {}
    ~s_type_lib() {}

    tstring m_lib_id;
    DWORD m_language;
    tstring m_component;
    DWORD m_version;
    tstring m_description;
    tstring m_directory;
    tstring m_feature;
    DWORD m_cost;
};

///////////////////////////////////////////////////////////////////////////
// s_service_control -- structure to hold a row in the ServiceControl table
//
struct s_service_control
{
    s_service_control(const tstring &key, const tstring &name,
                      DWORD event, const tstring &args, DWORD wait,
                      const tstring &component)
        : m_service_control(key),
        m_name(name),
        m_event(event),
        m_arguments(args),
        m_wait(wait),
        m_component(component)
    {}
    ~s_service_control() {}

    tstring m_service_control;
    tstring m_name;
    DWORD m_event;
    tstring m_arguments;
    DWORD m_wait;
    tstring m_component;
};

///////////////////////////////////////////////////////////////////////////
// s_service_install -- structure to hold a row in the ServiceInstall table
//
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
    ~s_service_install() {}

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

    void add_registry(DWORD root, const tstring &base, const tstring &component);

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

    void add_registry(DWORD root, const tstring &base,
                      const tstring &component, DWORD flags = add_all);
    tstring default_sz() const;

private:
    HKEY m_key;
    tstring m_name;
};

///////////////////////////////////////////////////////////////////////////
// g_xxx_table -- Windows Installer table rows from parsing the registry
//
std::vector<s_app_id>           g_app_id_table;
std::vector<s_class>            g_class_table;
std::vector<s_registry>         g_registry_table;
std::vector<s_prog_id>          g_prog_id_table;
std::vector<s_service_control>  g_service_control_table;
std::vector<s_service_install>  g_service_install_table;
std::vector<s_type_lib>         g_type_lib_table;

///////////////////////////////////////////////////////////////////////////
// sq -- string quote; encapsulate a string in single quotes
//
inline tstring
sq(const tstring &str)
{
    return _T("'") + str + _T("'");
}

///////////////////////////////////////////////////////////////////////////
// registry_row -- append a row to the Registry table in memory
//
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

///////////////////////////////////////////////////////////////////////////
// app_id_row -- append a row to the AppId table in memory
//
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

///////////////////////////////////////////////////////////////////////////
// class_row -- append a row to the Class table in memory
//
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
// type_lib_row -- append a row to the TypeLib table in memory
//
void
type_lib_row(const tstring &lib_id, DWORD language, const tstring &component,
             DWORD version, const tstring &description,
             const tstring &directory, const tstring &feature, DWORD cost)
{
    g_type_lib_table.push_back(s_type_lib(lib_id, language, component,
        version, description, directory, feature, cost));
    tostringstream msg;
    msg << _T("TypeLib: ") << sq(lib_id) << _T(", ") << language << _T(", ")
        << sq(component) << _T(", ") << version << _T(", ") << sq(description)
        << _T(", ") << sq(directory) << _T(", ") << sq(feature) << _T(", ")
        << cost << _T("\n");
    ::ODS(msg);
}

///////////////////////////////////////////////////////////////////////////
// prog_id_row -- append a row to the ProgId table in memory
//
void
prog_id_row(const tstring &progid, const tstring &parent, const tstring &clsid,
            const tstring &description, const tstring &icon, DWORD icon_index)
{
    g_prog_id_table.push_back(s_prog_id(progid, parent, clsid, description,
        icon, icon_index));
    tostringstream msg;
    msg << _T("ProgId: ") << sq(progid) << _T(", ") << sq(parent) << _T(", ")
        << sq(clsid) << _T(", ") << sq(description) << _T(", ")
        << sq(icon) << _T(", ") << icon_index << _T("\n");
    ::ODS(msg);
}

///////////////////////////////////////////////////////////////////////////
// service_control_row -- append a row to the ServiceControl table in memory
//
void
service_control_row(const tstring &key, const tstring &name,
                    DWORD event, const tstring &args, DWORD wait,
                    const tstring &component)
{
    g_service_control_table.push_back(
        s_service_control(key, name, event, args, wait, component));
    tostringstream msg;
    msg << _T("ServiceControl: ") << sq(key) << _T(", ") << sq(name)
        << _T(", ") << event << _T(", ") << sq(args) << _T(", ") << wait
        << _T(", ") << sq(component) << _T("\n");
    ::ODS(msg);
}

///////////////////////////////////////////////////////////////////////////
// service_install_row -- append a row to the ServiceInstall table in memory
//
void
service_install_row(const tstring &key, const tstring &name,
                    const tstring &display_name, DWORD service_type,
                    DWORD start_type, DWORD error_control,
                    const tstring &load_order_group,
                    const tstring &dependencies, const tstring &start_name,
                    const tstring &password, const tstring &arguments,
                    const tstring &component, const tstring &description)
{
    g_service_install_table.push_back(
        s_service_install(key, name, display_name, service_type, start_type,
            error_control, load_order_group, dependencies, start_name,
            password, arguments, component, description));
    tostringstream msg;
    msg << _T("ServiceInstall: ") << sq(key) << _T(", ") << sq(name) << _T(", ")
        << sq(display_name) << _T(", ") << service_type << _T(", ")
        << start_type << _T(", ") << error_control << _T(", ")
        << sq(load_order_group) << _T(", ") << sq(dependencies) << _T(", ")
        << sq(start_name) << _T(", ") << sq(password) << _T(", ")
        << sq(arguments) << _T(", ") << sq(component) << _T(", ")
        << sq(description) << _T("\n");
    ::ODS(msg);
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
// cis_equal -- case-insensitive string equality predicate
//
inline bool
cis_equal(LPCTSTR lhs, const tstring &rhs)
{
    return (_tcslen(lhs) == rhs.size()) && (_tcsicmp(lhs, rhs.c_str()) == 0);
}
inline bool
cis_equal(const tstring &lhs, const tstring &rhs)
{
    return cis_equal(lhs.c_str(), rhs);
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
        buff << file << _T("(") << line << _T("): ") << result << _T(" = ")
            << context << _T("\n");
        TCHAR msg[1024] = { 0 };
        const DWORD count = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, result, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &msg[0], NUM_OF(msg), NULL);
        if (count)
        {
            buff << _T("   '") << msg << _T("\n");
        }
        ::ODS(buff);
        throw win32_error(result, file, line, buff.str().c_str());
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
        buff << file << _T("(") << line << _T("): 0x") << std::hex
            << std::setfill(_T('0')) << std::setw(8) << hr << _T(" = ")
            << context << _T("\n");
        TCHAR msg[1024] = { 0 };
        const DWORD count = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &msg[0], NUM_OF(msg), NULL);
        if (count)
        {
            buff << _T("   '") << msg << _T("'\n");
        }
        ::ODS(buff);
        throw hresult_error(hr, file, line, buff.str().c_str());
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
// add_service
//
// Dumps information about a newly created service into the ServiceInstall
// table.
//
void
add_service(const tstring &name, const tstring &component, DWORD idx)
{
    windows_service_manager scm;
    windows_service svc(scm, name.c_str());
    DWORD size_needed = 0;
    // this fails with buffer size too small, which is intentional
    ::QueryServiceConfig(svc, NULL, 0, &size_needed);
    std::vector<BYTE> buff(size_needed);
    QUERY_SERVICE_CONFIG *config =
        reinterpret_cast<QUERY_SERVICE_CONFIG *>(&buff[0]);
    TWS(::QueryServiceConfig(svc, config, buff.size(), &size_needed));

    tostringstream key;
    key << _T("si_") << component << _T("_") << (1+idx);
    size_needed = 0;
    SERVICE_DESCRIPTION sd;
    TWS(::QueryServiceConfig2(svc, SERVICE_CONFIG_DESCRIPTION,
        reinterpret_cast<BYTE *>(&sd), sizeof(sd), &size_needed));
    ::service_install_row(key.str(), name, config->lpDisplayName,
        config->dwServiceType, config->dwStartType, config->dwErrorControl,
        config->lpLoadOrderGroup, multi_sz(config->lpDependencies),
        cis_equal(_T("LocalSystem"), config->lpServiceStartName) ?
            _T("") : config->lpServiceStartName,
        _T(""), _T(""), component,
        sd.lpDescription ? sd.lpDescription : _T(""));
}

///////////////////////////////////////////////////////////////////////////
// diff_services
//
// Compare currently installed services to a list of services previously
// installed to determine the names of services added or removed during
// registration.
//
void
reg_monitor::diff_services()
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
        ::service_control_row(key.str(), services_not_current[i],
            8, // msidbServiceControlDelete
            _T(""), 0, m_component);
    }
    for (i = 0; i < current_not_services.size(); i++)
    {
        add_service(current_not_services[i], m_component, i);
    }
}

#if 0
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
#endif

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

#if 0
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
#endif

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
s_monitor_key::extract_app_id(const tstring &component) const
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
            extract_app_id_entry(subkey, component);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// find_bad
//
// Helper routine to massage arbitrary strings into database table primary
// keys.  Returns the index of the first character that is not a letter, 
// not a digit and not an underscore.
//
inline tstring::size_type
find_bad(const tstring &str, tstring::size_type idx)
{
    return str.find_first_not_of(
        _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"),
        idx);
}

///////////////////////////////////////////////////////////////////////////
// primary_key
//
// Given a wild and hairy string, massage it into a string that is useful
// as the primary key to a database table.  First, all 'bad' characters are
// replaced with underscores.  Next, multiple adjacent underscores are
// replaced by a single underscore.  Finally, leading and trailing
// underscores are stripped.  This routine is used to generate database
// table keys from registry key paths.
//
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

///////////////////////////////////////////////////////////////////////////
// registry_value::add_registry
//
// Add this value to the Registry table.
//
void
registry_value::add_registry(DWORD root, const tstring &base,
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
    ::registry_row(primary_key(g_roots[root] + base + _T("\\") +
                               (name().size() ? name() : tstring(_T("nul")))),
        root, base, name(), Value.str(), component);
}

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
registry_key::add_registry(DWORD root, const tstring &base,
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
            ::registry_row(primary_key(g_roots[root] + base + _T("\\") + name()),
                root, base + _T("\\") + name(), _T(""), _T(""), component);
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
                    val.add_registry(root, subname, component);
                }
            }
        }
        if (flags & add_subkeys)
        {
            for (i = 0; i < num_subkeys; i++)
            {
                registry_key(key, i).add_registry(root, subname, component);
            }
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
s_monitor_key::extract_app_id_entry(const registry_key &subkey,
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
            val.add_registry(0, subname, component);
        }
    }

    // dump a row into the AppId table
    ::app_id_row(subkey.name(), remote_server, local_svc, svc_params,
        dll_surr, activate_stg, run_as);

    // add all subkeys, even though there shouldn't be any
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key(entry, i).add_registry(0, subname, component);
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

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_clsid_entry
//
// Extract a row of the Class table from a HKCR\CLSID\{guid} key in the
// registry.  Anything not directly created by the Class table is dumped
// into the Registry table.
//
void
s_monitor_key::extract_clsid_entry(const registry_key &subkey,
                                   const tstring &component) const
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
            val.add_registry(0, subname, component);
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
                key.add_registry(0, subname, component,
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
            key.add_registry(0, subname, component,
                registry_key::add_values | registry_key::add_subkeys);
        }
        else if (cis_equal(_T("ProgId"), key.name()))
        {
            prog_id = key.default_sz();
            // add leftovers to Registry table
            key.add_registry(0, subname, component,
                registry_key::add_values | registry_key::add_subkeys);
        }
        else if (cis_equal(_T("VersionIndependentProgId"), key.name()))
        {
            // the ProgId table takes care of the default value for this key,
            // but there may be additional keys and values lurking there
            key.add_registry(0, subname, component,
                registry_key::add_values | registry_key::add_subkeys);
        }
        else
        {
            // some random key -- put it in the Registry table verbatim
            key.add_registry(0, subname, component);
        }
    }

    // add a row to the class table for this CLSID
    ::class_row(subkey.name(), context, component, prog_id, description,
        app_id, _T(""), icon, icon_index, _T(""), _T(""), component, 0);
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_prog_id
//
// Extract new entries under HKCR\ as new rows of the ProgId table.
//
void
s_monitor_key::extract_prog_id(const tstring &component) const
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
                val.add_registry(0, m_name, component);
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
                subkey.add_registry(0, m_name, component);
            }
            else
            {
                // looks like a progId with at least one '.' inside the string
                extract_prog_id_entry(subkey, component);
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
s_monitor_key::extract_prog_id_entry(const registry_key &subkey,
                                     const tstring &component) const
{
    CRegKey progid;
    TRS(progid.Open(m_key, subkey.name().c_str()));
    DWORD num_values, num_subkeys;
    value_subkey_count(progid, num_values, num_subkeys);
    tstring ProgId = subkey.name();
    tstring ProgId_Parent;
    tstring CLSID;
    tstring Description = subkey.default_sz();
    tstring Icon;
    DWORD IconIndex = 0;

    tstring subname = m_name + _T("\\") + subkey.name();
    UINT i;
    for (i = 0; i < num_values; i++)
    {
        registry_value val(progid, i);
        if (val.name().size())
        {
            registry_value(progid, i).add_registry(0, subname, component);
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key progid_subkey(progid, i);
        if (cis_equal(_T("CLSID"), progid_subkey.name()))
        {
            CLSID = progid_subkey.default_sz();
        }
        else if (cis_equal(_T("CurVer"), progid_subkey.name()))
        {
            ProgId_Parent = progid_subkey.default_sz();
        }
        else if (cis_equal(_T("DefaultIcon"), progid_subkey.name()))
        {
            const tstring def = progid_subkey.default_sz();
            const tstring::size_type comma = def.rfind(_T(","));
            Icon = def.substr(0, comma);
            if (comma != tstring::npos)
            {
                tistringstream str(def.substr(comma+1));
                str >> IconIndex;
            }
        }
        else
        {
            progid_subkey.add_registry(0, subname, component);
        }
    }
    ::prog_id_row(ProgId, ProgId_Parent, CLSID, Description, Icon, IconIndex);
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_registry
//
// Extract all new things under a monitored registry key into the Registry
// table.
//
void
s_monitor_key::extract_registry(const tstring &component) const
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
            subkey.add_registry(0, m_name, component);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// s_monitor_key::extract_type_lib
//
// Scan through the monitored key HKCR\TypeLib to look for new LibId subkeys
//
void
s_monitor_key::extract_type_lib(const tstring &component) const
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
            extract_type_lib_entry(subkey, component);
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
s_monitor_key::extract_type_lib_entry(const registry_key &subkey,
                                     const tstring &component) const
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
        registry_value(entry, i).add_registry(0, subname, component);
    }

    // add all subkeys, even though there shouldn't be any
    for (i = 0; i < num_subkeys; i++)
    {
        registry_key key(entry, i);
        if (!is_version_number(key.name()))
        {
            // add unrecognized keys to Registry table
            key.add_registry(0, subname, component);
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
                        add_registry(0, ver_subname, component);
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
                    value_subkey_count(lang, num_lang_values, num_lang_subkeys);
                    
                    tstring lang_subname =
                        ver_subname + _T("\\") + ver_subkey.name();
                    UINT k;
                    for (k = 0; k < num_lang_values; k++)
                    {
                        registry_value(lang, k).
                            add_registry(0, lang_subname, component);
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
                                lang_subkey.add_registry(0, lang_subname,
                                    component);
                            }
                        }
                        else
                        {
                            // add unrecognized keys to Registry table
                            lang_subkey.add_registry(0, lang_subname, component);
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
                    ver_subkey.add_registry(0, ver_subname, component);
                }
            }
        }
    }

    if (lib_found)
    {
        // add a row to the class table for this LibID
        ::type_lib_row(subkey.name(), language, component, version, description,
            directory, component, 0);
    }
}

///////////////////////////////////////////////////////////////////////////
// reg_monitor::reg_monitor
//
// C'tor reserves space and creates an event for notification.
//
reg_monitor::reg_monitor(const tstring &file, bool servicep)
    : m_file(file),
    m_servicep(servicep),
    m_keys(),
    m_events(),
    m_component()
{
    m_keys.reserve(64);
    m_events.reserve(64);
    m_events.push_back(TWS(::CreateEvent(NULL, TRUE, FALSE, NULL)));
    const tstring::size_type whack = m_file.rfind(_T("\\"));
    m_component = (tstring::npos != whack) ? m_file.substr(whack+1) : m_file;
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
    if (m_servicep)
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
    dump_tables();
    if (m_servicep)
    {
        // ServiceInstall table, ServiceControl table
        diff_services();
    }
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
// Scrape the captured registration information to the Windows Installer
// database.
//
void
reg_monitor::dump_tables()
{
    for (UINT i = 0; i < m_keys.size(); i++)
    {
        // AppId table
        if (match_key(m_keys[i], _T("HKCR"), _T("AppID")))
        {
            m_keys[i].extract_app_id(m_component);
        }
        // Class table
        else if (match_key(m_keys[i], _T("HKCR"), _T("CLSID")))
        {
            m_keys[i].extract_class(m_component);
        }
        // TypeLib table
        else if (match_key(m_keys[i], _T("HKCR"), _T("TypeLib")))
        {
            m_keys[i].extract_type_lib(m_component);
        }
        // ProgId, Extension table, MIME table, Verb table
        else if (match_key(m_keys[i], _T("HKCR"), _T("")))
        {
            m_keys[i].extract_prog_id(m_component);
        }
        // Registry table
        else
        {
            m_keys[i].extract_registry(m_component);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
// usage -- report command line usage in a message box
//
int
usage()
{
    ::MessageBox(0, _T("Usage: extract.exe [options] SERVER\n\n")
        _T("Extracts COM registration information from the file SERVER.\n\n")
        _T("[options] include:\n\n")
        _T("/service  - SERVER is a Windows NT service\n"),
        _T("Usage:"), MB_OK);
    return 1;
}

///////////////////////////////////////////////////////////////////////////
// parse_args -- parse a command line into an argument list
//
string_list_t
parse_args(LPCTSTR command_line)
{
    string_list_t args;
    const tstring cmd_line = command_line;

    tstring::size_type start = 0;
    tstring::size_type stop = 0;
    while (stop != tstring::npos)
    {
        if (cmd_line[start] == _T('"'))
        {
            start = 1;
            stop = cmd_line.find(_T("\""), start);
            if (tstring::npos == stop)
            {
                usage();
                return string_list_t();
            }
        }
        else
        {
            stop = cmd_line.find(_T(" "), start);
        }
        if (stop == tstring::npos)
        {
            args.push_back(cmd_line.substr(start));
        }
        else
        {
            args.push_back(cmd_line.substr(start, stop-start));
        }
        start = stop+1;
    }

    return args;
}

///////////////////////////////////////////////////////////////////////////
// log_error -- log an unexpected error that we handled.
//
void
log_error(const source_error &bang)
{
    ::MessageBox(0, bang.m_msg.c_str(), _T("Unexpected internal failure:"),
                 MB_OK);
#if 0
    ofstream log_file(temp_file(), ios::out | ios::append);
    USES_CONVERSION;
    log_file << timestamp() << " Unexpected internal failure:\n"
        << T2A(bang.m_file) << "(" << bang.m_line << "): "
        << T2A(bang.m_msg) << "\n";
#endif
}

///////////////////////////////////////////////////////////////////////////
// log_unexpected -- log an unexpected fatal error
//
void
log_unexpected()
{
    ::MessageBox(0, _T("My brains have been removed with an ice-cream scoop.\n")
        _T("I am dead."), _T("Unexpected fatal failure."), MB_OK);
#if 0
    ofstream log_file(temp_file(), ios::out | ios::append);
    USES_CONVERSION;
    log_file << timestamp() << " Unexpected fatal failure:\n"
#endif
}

///////////////////////////////////////////////////////////////////////////
// WinMain -- test the whole thing with a stub service EXE COM server
//
int APIENTRY
_tWinMain(HINSTANCE, HINSTANCE, LPTSTR command_line, int)
{
    string_list_t args = parse_args(command_line);
    bool servicep = false;
    string_list_t::iterator i;
    for (i = args.begin(); i != args.end(); ++i)
    {
        if (cis_equal(_T("/service"), *i) ||
            cis_equal(_T("-service"), *i))
        {
            args.erase(i);
            servicep = true;
        }
    }
    if (args.size() != 1)
    {
        return usage();
    }

    try
    {
        com_runtime com;
        reg_monitor monitor(args[0], servicep);
        monitor.add(HKEY_CLASSES_ROOT, _T("HKCR"), _T("AppID"))
            .add(HKEY_CLASSES_ROOT, _T("HKCR"), _T("CLSID"))
            // This isn't needed as the interfaces are registered
            // when the type library is registered.
            // .add(HKEY_CLASSES_ROOT, _T("HKCR"), _T("Interface"))
            .add(HKEY_CLASSES_ROOT, _T("HKCR"), _T("TypeLib"))
            .add(HKEY_CLASSES_ROOT, _T("HKCR"))
            .add(HKEY_CURRENT_USER, _T("HKCU"), _T("Software"))
            .add(HKEY_CURRENT_USER, _T("HKCU"))
            .add(HKEY_LOCAL_MACHINE, _T("HKLM"), _T("Software"))
            .add(HKEY_LOCAL_MACHINE, _T("HKLM"))
            .add(HKEY_USERS, _T("HKEY_USERS"));
        monitor.process();
    }
    catch (const source_error &bang)
    {
        log_error(bang);
        return 2;
    }
    catch (...)
    {
        log_unexpected();
        return 3;
    }

    return 0;
}
