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
#if !defined(PROPS_H)
#define PROPS_H

#define CHECK_PROPERTY_POINTER()                                            \
if (!pVal)                                                                  \
{                                                                           \
    return Error(_T("A NULL pointer was passed for an output argument."),   \
        PROPERTY_IID, E_POINTER);                                           \
} else 0

#define STORE_STRING_PROPERTY(member_)                      \
    CHECK_PROPERTY_POINTER();                               \
    *pVal = CComBSTR(m_record->member_.c_str()).Detach()

#define STORE_LONG_PROPERTY(member_)    \
    CHECK_PROPERTY_POINTER();           \
    *pVal = m_record->member_

#endif
