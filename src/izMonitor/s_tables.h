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
///////////////////////////////////////////////////////////////////////////
// s_tables.h
//
// Data structures defining the table records extracted by izMonitor.
//
#if !defined(S_TABLES_H)
#define S_TABLES_H

#include <vector>
#include "tstring.h"

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
    s_app_id()
        : m_app_id(),
        m_remote_server_name(),
        m_local_service(),
        m_service_parameters(),
        m_activate_at_storage(0),
        m_run_as_interactive_user(0)
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
    s_class()
        : m_clsid(),
        m_context(),
        m_component(),
        m_prog_id_default(),
        m_description(),
        m_app_id(),
        m_file_type_mask(),
        m_icon(),
        m_icon_index(0),
        m_def_inproc_handler(),
        m_argument(),
        m_feature(),
        m_attributes(0)
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
    s_registry()
        : m_registry(),
        m_root(0),
        m_key(),
        m_name(),
        m_value(),
        m_component()
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
    s_prog_id()
        : m_prog_id(),
        m_prog_id_parent(),
        m_class(),
        m_description(),
        m_icon(),
        m_icon_index(0)
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
    s_type_lib()
        : m_lib_id(),
        m_language(0),
        m_component(),
        m_version(0),
        m_description(),
        m_directory(),
        m_feature(),
        m_cost(0)
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
    s_service_control()
        : m_service_control(),
        m_name(),
        m_event(0),
        m_arguments(),
        m_wait(0),
        m_component()
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
    s_service_install()
        : m_service_install(),
        m_name(),
        m_display_name(),
        m_service_type(0),
        m_start_type(0),
        m_error_control(0),
        m_load_order_group(),
        m_dependencies(),
        m_start_name(),
        m_password(),
        m_arguments(),
        m_component(),
        m_description()
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
// xxx_table_t -- typedefs for the table containers
//
typedef std::vector<s_app_id> app_id_table_t;
typedef std::vector<s_class> class_table_t;
typedef std::vector<s_registry> registry_table_t;
typedef std::vector<s_prog_id> prog_id_table_t;
typedef std::vector<s_type_lib> type_lib_table_t;
typedef std::vector<s_service_control> service_control_table_t;
typedef std::vector<s_service_install> service_install_table_t;

#endif
