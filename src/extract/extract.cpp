// extract.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
dynamic_library::dynamic_library(LPCTSTR file)
    : m_file(file),
    m_library(TWS(::LoadLibrary(file)))
{
}

//-------------------------------------------------------------------------
dynamic_library::~dynamic_library()
{
    const BOOL res = ::FreeLibrary(m_library);
    ATLASSERT(res);
}

//-------------------------------------------------------------------------
dynamic_library::operator HMODULE() const
{
    return m_library;
}

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
HRESULT
run_executable(LPCTSTR file, const tstring &cmd_line)
{
    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    TWS(::CreateProcess(file, const_cast<LPTSTR>(cmd_line.c_str()), NULL, NULL, false,
        0, NULL, NULL, &si, &pi));
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

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
HRESULT
unregister_server(LPCTSTR file)
{
    const HRESULT hr = register_proc(false, file);
    return (E_POINTER == hr) ?
        run_executable(file, tstring(file) + _T(" -unregserver")) : hr;
}

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
reg_monitor::~reg_monitor()
{
}

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
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
s_monitor_key::diff()
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
    UINT i;
    if (num_values)
    {
        tostringstream buff;
        buff << _T("[") << m_name << _T("]\n");
        UINT num_new = 0;

        for (i = 0; i < num_values; i++)
        {
            DWORD type = 0;
            DWORD num_data = 0;
            TCHAR val_name[1024] = { 0 };
            DWORD num_value_name = NUM_OF(val_name);
            TRS(::RegEnumValue(m_key, i, &val_name[0], &num_value_name, NULL,
                &type, NULL, &num_data));
            if (m_values.find(val_name) == m_values.end())
            {
                num_new++;

                std::vector<BYTE> data(num_data);
                num_value_name = NUM_OF(val_name);
                TRS(::RegEnumValue(m_key, i, &val_name[0], &num_value_name, NULL,
                    NULL, &data[0], &num_data));

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
            }
        }
        if (num_new)
        {
            ::ODS(buff);
        }
    }
    for (i = 0; i < num_subkeys; i++)
    {
        FILETIME last_write;
        TCHAR buff[512];
        DWORD num_name = NUM_OF(buff);
        TCHAR class_name[512];
        DWORD num_class_name = NUM_OF(class_name);
        TRS(::RegEnumKeyEx(m_key, i, &buff[0], &num_name, NULL,
            &class_name[0], &num_class_name, &last_write));
        if (m_subkeys.find(buff) == m_subkeys.end())
        {
            CRegKey new_key;
            TRS(new_key.Open(m_key, buff));
            tstring name(m_name);
            if (m_subkey.length())
            {
                name += _T("\\") + m_subkey;
            }
            enum_registry(new_key, name + _T("\\") + buff);
        }
    }
}

//-------------------------------------------------------------------------
void
reg_monitor::process()
{
    string_list_t services;
    THR(unregister_server(m_file.c_str()));
    if (m_servicep)
    {
        capture_services(services);
    }

    UINT i;
    for (i = 0; i < m_keys.size(); i++)
    {
        const HANDLE event = TWS(::CreateEvent(NULL, TRUE, FALSE, NULL));
        TRS(::RegNotifyChangeKeyValue(m_keys[i].m_key, FALSE,
            REG_NOTIFY_CHANGE_NAME, event, TRUE));
        m_events.push_back(event);
        m_keys[i].snapshot();
    }

    thread_args args = { m_file.c_str(), m_events[0], m_servicep };
    DWORD thread_id = 0;
    unsigned long thread_handle =
        TCR(_beginthread(register_threadproc, 0, &args));

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
                ::ODS(target.m_name + _T("\\") + target.m_subkey + _T(" changed.\n"));
            }
            else
            {
                more = false;
            }
        }
        else
        {
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

    dump_tables(services);
}

void
reg_monitor::dump_tables(const string_list_t &services)
{
    for (UINT i = 0; i < m_keys.size(); i++)
    {
        if (m_keys[i].m_name == _T("HKCR"))
        {
            if (m_keys[i].m_subkey == _T("AppID"))
            {
                // AppId table
                ::OutputDebugString(_T("\nAppId Table\n"));
                m_keys[i].diff();
            }
            else if (m_keys[i].m_subkey == _T("CLSID"))
            {
                // Class table
                ::OutputDebugString(_T("\nClass Table\n"));
                m_keys[i].diff();
            }
            else if (m_keys[i].m_subkey == _T("Interface"))
            {
                // TypeLib table
                ::OutputDebugString(_T("\nTypeLib Table, IIDs\n"));
                m_keys[i].diff();
            }
            else if (m_keys[i].m_subkey == _T("TypeLib"))
            {
                // TypeLib table
                ::OutputDebugString(_T("\nTypeLib Table\n"));
                m_keys[i].diff();
            }
            else if (m_keys[i].m_subkey == _T(""))
            {
                // ProgId, Extension table, MIME table, Verb table
                ::OutputDebugString(_T("\nProgId, Extension, MIME, Verb Tables\n"));
                m_keys[i].diff();
            }
            else
            {
                // Registry table?
                ::OutputDebugString(_T("\nRegistry Table, HKCR\\?\n"));
                m_keys[i].diff();
                ATLASSERT(0);
            }
        }
        else if (m_keys[i].m_name == _T("HKLM"))
        {
            // Registry table
                ::OutputDebugString(_T("\nRegistry Table, HKLM\n"));
            m_keys[i].diff();
        }
        else if (m_keys[i].m_name == _T("HKCU"))
        {
            // Registry table
                ::OutputDebugString(_T("\nRegistry Table, HKCU\n"));
            m_keys[i].diff();
        }
        else if (m_keys[i].m_name == _T("HKEY_USERS"))
        {
            // Registry table
                ::OutputDebugString(_T("\nRegistry Table, HKEY_USERS\n"));
            m_keys[i].diff();
        }
        else if (m_keys[i].m_name == _T("HKEY_CURRENT_CONFIG"))
        {
            // Registry table
            ::OutputDebugString(_T("\nRegistry Table, HKEY_CURRENT_CONFIG\n"));
            m_keys[i].diff();
        }
        else
        {
            // Registry table
            ::OutputDebugString((_T("\nRegistry Table, ") + m_keys[i].m_name +
                _T("?\n")).c_str());
            m_keys[i].diff();
            ATLASSERT(0);
        }
    }
    if (m_servicep)
    {
        // ServiceInstall table, ServiceControl table
        ::OutputDebugString(_T("\nServiceInstall, ServiceControl Table\n"));
        diff_services(services);
    }
}

//-------------------------------------------------------------------------
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
