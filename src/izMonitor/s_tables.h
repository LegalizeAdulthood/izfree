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
#if !defined(S_TABLES_H)
#define S_TABLES_H

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

#endif
