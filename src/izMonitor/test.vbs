' izfree Tools for Windows Installer
' Copyright (C) 2001-2002 Pahvant Technologies, Inc.
'
' This program is free software; you can redistribute it and/or modify
' it under the terms of the GNU General Public License as published by
' the Free Software Foundation; either version 2 of the License, or
' (at your option) any later version.
'
' This program is distributed in the hope that it will be useful,
' but WITHOUT ANY WARRANTY; without even the implied warranty of
' MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
' GNU General Public License for more details.
'
' You should have received a copy of the GNU General Public License
' along with this program; if not, write to the Free Software
' Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
'
function app_id_str(rec)
    app_id_str = "AppId: " & rec.AppId & vbCRLF &_
        "RemoteServerName: " & rec.RemoteServerName & vbCRLF &_
        "LocalService: " & rec.LocalService & vbCRLF &_
        "ServiceParameters: " & rec.ServiceParameters & vbCRLF &_
        "DllSurrogate: " & rec.DllSurrogate & vbCRLF &_
        "ActivateAtStorage: " & rec.ActivateAtStorage & vbCRLF &_
        "RunAsInteractiveUser: " & rec.RunAsInteractiveUser & vbCRLF
end function

sub test_monitor
    dim mon : set mon = CreateObject("izfree.Monitor")
    mon.WatchKey "HKLM\Software"
    mon.WatchKey "HKCU\Software"
    mon.WatchKey "HKU\Software"
    mon.WatchKey "HKCR\CLSID"
    mon.Process "NUL:", false
    dim table : set table = mon.AppIdTable
    dim msg : msg = "Count: " & table.Count & vbCRLF & vbCRLF
    dim appid : for each appid in table
        msg = msg & app_id_str(appid) & vbCRLF
    next
    wscript.echo msg
    ' this should fail
    'mon.WatchKey "HKEY_CURRENT_CONFIG\Software\Pahvant"
end sub

test_monitor
