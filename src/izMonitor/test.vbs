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

function class_str(rec)
    class_str = "Class: " & rec.CLSID & vbCRLF &_
        "context: " & rec.context & vbCRLF &_
        "component: " & rec.component & vbCRLF &_
        "prog_id_default: " & rec.ProgIdDefault & vbCRLF &_
        "description: " & rec.description & vbCRLF &_
        "app_id: " & rec.AppId & vbCRLF &_
        "file_type_mask: " & rec.FileTypeMask & vbCRLF &_
        "icon: " & rec.icon & vbCRLF &_
        "icon_index: " & rec.IconIndex & vbCRLF &_
        "def_inproc_handler: " & rec.DefInprocHandler & vbCRLF &_
        "argument: " & rec.argument & vbCRLF &_
        "feature: " & rec.feature & vbCRLF &_
        "attributes: " & rec.attributes & vbCRLF
end function

function progid_str(rec)
    progid_str = _
        "prog_id: " & rec.ProgId & vbCRLF &_
        "prog_id_parent: " & rec.Parent & vbCRLF &_
        "class: " & rec.Class & vbCRLF &_
        "description: " & rec.description & vbCRLF &_
        "icon: " & rec.icon & vbCRLF &_
        "icon_index: " & rec.IconIndex & vbCRLF
end function

function registry_str(rec)
    registry_str = _
        "registry: " & rec.registry & vbCRLF &_
        "root: " & rec.root & vbCRLF &_
        "key: " & rec.key & vbCRLF &_
        "name: " & rec.name & vbCRLF &_
        "value: " & rec.value & vbCRLF &_
        "component: " & rec.component & vbCRLF
end function

function typelib_str(rec)
    typelib_str = _
        "lib_id: " & rec.LibID & vbCRLF &_
        "language: " & rec.language & vbCRLF &_
        "component: " & rec.component & vbCRLF &_
        "version: " & rec.version & vbCRLF &_
        "description: " & rec.description & vbCRLF &_
        "directory: " & rec.directory & vbCRLF &_
        "feature: " & rec.feature & vbCRLF &_
        "cost: " & rec.cost & vbCRLF
end function

function service_control_str(rec)
    service_control_str = _
        "service_control: " & rec.ServiceControl & vbCRLF &_
        "name: " & rec.name & vbCRLF &_
        "event: " & rec.event & vbCRLF &_
        "arguments: " & rec.arguments & vbCRLF &_
        "wait: " & rec.wait & vbCRLF &_
        "component: " & rec.component & vbCRLF
end function

function service_install_str(rec)
    service_install_str = _
        "service_install: " & rec.ServiceInstall & vbCRLF &_
        "name: " & rec.name & vbCRLF &_
        "display_name: " & rec.DisplayName & vbCRLF &_
        "service_type: " & rec.ServiceType & vbCRLF &_
        "start_type: " & rec.StartType & vbCRLF &_
        "error_control: " & rec.ErrorControl& vbCRLF &_
        "load_order_group: " & rec.LoadOrderGroup & vbCRLF &_
        "dependencies: " & rec.dependencies & vbCRLF &_
        "start_name: " & rec.StartName & vbCRLF &_
        "password: " & rec.password & vbCRLF &_
        "arguments: " & rec.arguments & vbCRLF &_
        "component: " & rec.component & vbCRLF &_
        "description: " & rec.description & vbCRLF
end function

sub test_monitor(file, service, component, feature)
    dim mon : set mon = CreateObject("izfree.Monitor")
    mon.WatchKey "HKCR\AppID"
    mon.WatchKey "HKCR\CLSID"
    mon.WatchKey "HKCR\TypeLib"
    mon.WatchKey "HKCR\Component Categories"
    mon.WatchKey "HKCR"
    mon.WatchKey "HKCU\Software"
    mon.WatchKey "HKCU"
    mon.WatchKey "HKLM\Software"
    mon.WatchKey "HKLM"
    mon.WatchKey "HKU"
    mon.Process file, service, component, feature
    dim table : set table = mon.AppIdTable
    dim msg : msg = "AppId Count: " & table.Count & vbCRLF & vbCRLF
    dim rec : for each rec in table
        msg = msg & app_id_str(rec) & vbCRLF
    next
    wscript.echo msg

    set table = mon.ClassTable
    msg = "Class Count: " & table.Count & vbCRLF & vbCRLF
    for each rec in table
        msg = msg & class_str(rec) & vbCRLF
    next
    wscript.echo msg

    set table = mon.ProgIdTable
    msg = "ProgId Count: " & table.Count & vbCRLF & vbCRLF
    for each rec in table
        msg = msg & progid_str(rec) & vbCRLF
    next
    wscript.echo msg

    set table = mon.TypeLibTable
    msg = "TypeLib Count: " & table.Count & vbCRLF & vbCRLF
    for each rec in table
        msg = msg & typelib_str(rec) & vbCRLF
    next
    wscript.echo msg

    set table = mon.RegistryTable
    msg = "Registry Count: " & table.Count & vbCRLF & vbCRLF
    for each rec in table
        msg = msg & registry_str(rec) & vbCRLF
    next
    wscript.echo msg

    set table = mon.ServiceControlTable
    msg = "ServiceControl Count: " & table.Count & vbCRLF & vbCRLF
    for each rec in table
        msg = msg & service_control_str(rec)
    next
    wscript.echo msg

    set table = mon.ServiceInstallTable
    msg = "ServiceInstall Count: " & table.Count & vbCRLF & vbCRLF
    for each rec in table
        msg = msg & service_install_str(rec)
    next
    wscript.echo msg

    ' this should fail
    'mon.WatchKey "HKEY_CURRENT_CONFIG\Software\Pahvant"
end sub

'test_monitor "c:\tmp\service\debug\service.exe", true, "service.exe", "service.exe"
' this should fail:
' test_monitor "c:\data\projects\izfree\dll\guidgen.dll", true, "guidgen.dll", "guidgen.dll"
test_monitor "c:\data\projects\izfree\dll\guidgen.dll", false, "guidgen.dll", "guidgen.dll"
