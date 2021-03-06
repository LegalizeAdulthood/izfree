''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' izfree Tools for Windows Installer 1.1
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
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
option explicit
on error resume next

' const vbYesNo = 4

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Common Dialog Open File Name constants
'
const cdlOFNReadOnly           = 1
const cdlOFNOverwritePrompt    = 2
const cdlOFNHideReadOnly       = 4
const cdlOFNNoChangeDir        = 8
const cdlOFNHelpButton         = 16
const cdlOFNNoValidate         = 256
const cdlOFNAllowMultiselect   = 512
const cdlOFNExtensionDifferent = 1024
const cdlOFNPathMustExist      = 2048
const cdlOFNFileMustExist      = 4096
const cdlOFNCreatePrompt       = 8192
const cdlOFNShareAware         = 16384
const cdlOFNNoReadOnlyReturn   = 32768
const cdlOFNNoLongNames        = &h00040000
const cdlOFNExplorer           = &h00080000
const cdlOFNNoDereferenceLinks = &h00100000
const cdlOFNLongNames          = &h00200000

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Shell Browse For Folder constants
'
const BIF_RETURNONLYFSDIRS   = &h0001
const BIF_DONTGOBELOWDOMAIN  = &h0002
const BIF_STATUSTEXT         = &h0004
const BIF_RETURNFSANCESTORS  = &h0008
const BIF_EDITBOX            = &h0010
const BIF_VALIDATE           = &h0020
const BIF_NEWDIALOGSTYLE     = &h0040
const BIF_USENEWUI           = &h0050 'BIF_NEWDIALOGSTYLE | BIF_EDITBOX
const BIF_BROWSEINCLUDEURLS  = &h0080
const BIF_UAHINT             = &h0100
const BIF_NONEWFOLDERBUTTON  = &h0200
const BIF_NOTRANSLATETARGETS = &h0400
const BIF_BROWSEFORCOMPUTER  = &h1000
const BIF_BROWSEFORPRINTER   = &h2000
const BIF_BROWSEINCLUDEFILES = &h4000
const BIF_SHAREABLE          = &h8000

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' INSTALLER_FILE_FILTER
'
' Default file filter for all Windows Installer database types.
'
const INSTALLER_FILE_FILTER = _
"Installer Database (*.msi)|*.msi|Merge Module (*.msm)|*.msm|ICE Database (*.cub)|*.cub|Windows Installer Files (*.{msi,msm,cub})|*.msi;*.msm;*.cub|All Files (*.*)|*.*"

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' MSI Open Database constants
'
const msiOpenDatabaseModeReadOnly = 0
const msiOpenDatabaseModeTransact = 1
const msiOpenDatabaseModeCreate = 3

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' FileSystemObject constants
'
const ForReading = 1

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Summary Information Properties constants
'
const PID_CODEPAGE = 1
const PID_TITLE = 2
const PID_SUBJECT = 3
const PID_AUTHOR = 4
const PID_KEYWORDS = 5
const PID_COMMENTS = 6
const PID_TEMPLATE = 7
const PID_LASTAUTHOR = 8
const PID_REVNUMBER = 9
const PID_LASTPRINTED = 11
const PID_CREATE_DTM = 12
const PID_LASTSAVE_DTM = 13
const PID_PAGECOUNT = 14
const PID_WORDCOUNT = 15
const PID_CHARCOUNT = 16
const PID_APPNAME = 18
const PID_SECURITY = 19

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' TreeView Control constants
'
const tvwChild = 4

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' check -- error checking routine
'
sub check
    if (Err.number) then
        'check = err.number
        dim msg : msg = Err.Source & " " & Hex(Err) & ": " & Err.Description & " " & Err.Source
        if (not installer is nothing) then
            dim err_rec : set err_rec = installer().LastErrorRecord
            if (not err_rec is nothing) then
                msg = msg & vbNewLine & err_rec.FormatText
            end if
        end if
        MsgBox(msg)
        Err.Clear
    end if
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' check_object
'
' Call CreateObject and then check the results.
'
function check_object(progid)
    on error resume next
    set check_object = CreateObject(progid) : check
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' installer()
' wsh()
' fso()
' generator()
'
' Accessors to grabbed objects
' 
function installer()
    select case window.name
    case ""
        set installer = g_installer
    case "Dialog"
        set installer = window.dialogArguments.g_installer
    case else
        set installer = window.parent.g_installer
    end select
end function
function wsh()
    select case window.name
    case ""
        set wsh = g_wsh
    case "Dialog"
        set wsh = window.dialogArguments.g_wsh
    case else
        set wsh = window.parent.g_wsh
    end select
end function
function fso()
    select case window.name
    case ""
        set fso = g_fso
    case "Dialog"
        set fso = window.dialogArguments.g_fso
    case else
        set fso = window.parent.g_fso
    end select
end function
function generator()
    select case window.name
    case ""
        set generator = g_generator
    case "Dialog"
        set generator = window.dialogArguments.g_generator
    case else
        set generator = window.parent.g_generator
    end select
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' new_guid
'
' Generate a new Windows Installer compatible GUID (no lower case) and
' return it as a string in {xxx-xx-xxx} form.
'
function new_guid()
    new_guid = ucase(generator().Generate())
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' set_guid_button
'
' Set the value of a text field to a new GUID string in response to
' a button click
'
sub set_guid_button(form, button)
    document.forms(form).all(button).value = new_guid()
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' wit_filename -- windows installer type: Filename
'
' Given a wild and hairy long name, return the long name if its a
' valid short name, otherwise return short|long form.
'
function wit_filename(wildname)
    ' split into basename and extension
    dim short : short = wildname
    dim ext : ext = ""
    dim dot : dot = instrrev(short, ".")
    if (dot) then
        ext = mid(short, dot+1)
        if (dot > 1) then
            short = left(short, dot-1)
        else
            short = ""
        end if
    end if

    ' check some length constraints on the pieces
    dim bad_short : bad_short = (len(short) > 8) or (len(ext) > 3)
    
    ' replace characters that can be in long names, but not in short
    const bad_short_chars = " +,;=[]."
    dim i : for i = 1 to len(bad_short_chars)
        dim suspect : suspect = mid(bad_short_chars, i, 1)
        if (instr(short, suspect)) then
            bad_short = true
            short = replace(short, suspect, "_")
        end if
    next

    ' need to produce short|long form
    if (bad_short) then
        if (len(short) > 8) then short = left(short, 8)
        if (len(ext) > 3) then ext = left(ext, 3)
        if (dot <> 0) then ext = "." & ext
        wit_filename = short & ext & "|" & wildname
    else
        wit_filename = wildname
    end if
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' sig_digits
'
' Return the number of significant digits in value.  This is used to
' construct the File table keys to ensure that every key is unique.
'
function sig_digits(value)
    sig_digits = 1
    dim tmp : tmp = value
    do while (tmp > 10)
        sig_digits = sig_digits + 1
        tmp = tmp / 10
    loop
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' sort
'
' Simple bubble sort on an array
'
sub sort(byref ary)
    on error resume next : err.clear
    dim len : len = ubound(ary)
    if (not err) then
        dim i : for i = 0 to len-1
            dim j : for j = i+1 to len
                if (ary(j) < ary(i)) then
                    dim tmp : tmp = ary(j) : ary(j) = ary(i) : ary(i) = tmp
                end if
            next
        next
    end if
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' quote
'
' Encapsulate a string in single quotes.
'
function quote(item)
    quote = "'" & item & "'"
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' show_help
'
' Display the help information for the given label.
'
sub show_help(label)
    g_main_frame.window_OnHelp()
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' browse_for_existing_file
'
' Use common open file dialog to browse for an existing file.
'
function browse_for_existing_file(filter)
    on error resume next
    dim ofd : set ofd = check_object("MSComDlg.CommonDialog")
    ofd.MaxFileSize = 1024
    ofd.Flags = cdlOFNFileMustExist
    ofd.Filter = filter
    err.Clear : ofd.ShowOpen : if (err.Number) then err.Raise
    browse_for_existing_file = ofd.FileName
    set ofd = nothing
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' browse_for_existing_dir
'
' Use windows shell browse for folder dialog to browse for an existing
' directory.
'
function browse_for_existing_dir(title)
    on error resume next
    dim shell : set shell = check_object("Shell.Application")
    dim folder : set folder = shell.BrowseForFolder(0, title, _
        BIF_RETURNONLYFSDIRS or BIF_USENEWUI).Self
    if (Err) then
        Err.Clear
        browse_for_existing_dir = ""
    elseif (folder.IsFileSystem) then
        browse_for_existing_dir = folder.Path
    else
        browse_for_existing_dir = ""
    end if
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' dbgout
'
' Send a line of debug output to the "debug" element in the current
' document.
'
sub dbgout(str)
    dim par : set par = document.All("debug")
    if (isobject(par) and ucase(par.tagName) = "P") then
        if (par.children.length > 10) then
            par.removeChild par.children(0)
            par.removeChild par.children(0)
        end if
        dim el : set el = document.CreateElement("SPAN")
        el.innerHTML = str
        par.AppendChild el
        par.AppendChild document.createElement("BR")
    end if
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' read_setting
'
' Read a setting for a tool out of the registry.
'
function read_setting(tool, name)
    if (tool <> "") then tool = tool & "\"
    read_setting = wsh().RegRead("HKCU\Software\Pahvant\izfree\" & tool & name)
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' write_setting
'
' Write a setting for a tool into the registry.
'
sub write_setting(tool, name, value)
    if (tool <> "") then tool = tool & "\"
    wsh().RegWrite "HKCU\Software\Pahvant\izfree\" & tool & name, value
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' write_input
'
' Write the contents of an input value into the registry.
'
sub write_input(tool, all, field)
    dim value : value = all(field).value
    if (value <> "") then
        write_setting tool, field, value
    end if
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' read_input
'
' Read the contents of an input value from the registry.
'
sub read_input(tool, all, field, fallback)
    on error resume next
    dim value : value = read_setting(tool, field)
    if (value = "") then
        value = fallback
    end if
    all(field).value = value
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
sub set_database(file, db, modified)
    g_main_frame.document.forms("dbForm").all("database").innerText = file
    set g_main_frame.g_database = db
    set_db_modified(modified)
end sub

sub set_db_modified(modified)
    g_main_frame.g_db_modified = modified
    g_main_frame.update_db_buttons
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
sub db_modified
    g_main_frame.g_db_modified = true
    g_main_frame.update_db_buttons
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' push
'
' push a value onto the end of a dynamic array
'
sub push(byref ary, val)
    on error resume next
    Err.clear : redim preserve ary(ubound(ary)+1)
    if (err) then
        Err.Clear
        redim preserve ary(0)
    end if
    if (isobject(val)) then
        set ary(ubound(ary)) = val
    else
        ary(ubound(ary)) = val
    end if
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' db_dic
'
' Return a dictionary populated with keys from the column of a database
' table
'
function db_dic(db, table, column)
    dim dic : set dic = check_object("Scripting.Dictionary")
    
    dim view : set view = exec_view(db, _
        "select `" & column & "` from `" & table & "`")
    dim rec : set rec = view.fetch
    do while (not rec is nothing)
        dic.add rec.stringdata(1), 1
        set rec = view.fetch
    loop
    set db_dic = dic
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' exec_view
'
' Create a view on a database and execute it, returning the view object.
'
function exec_view(db, query)
    on error resume next
    dim view : set view = db.openview(query) : check
    view.execute : check
    set exec_view = view
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' new_option_val
'
' Create a new OPTION element with text and associated value
'
function new_option_val(item, value)
    dim o : set o = document.createElement("OPTION")
    o.text = item : o.value = value
    set new_option_val = o
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' new_option
'
' Create a new OPTION element with the corresponding text and value
'
function new_option(item)
    set new_option = new_option_val(item, item)
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' get_property
'
' Return the value of a database property, or empty string.
'
function get_property(db, name)
    on error resume next
    dim view : set view = db.OpenView("select `Value` from `Property` " &_
        "where `Property`.`Property` = '" & name & "'") : check
    view.execute : check
    dim rec : set rec = view.fetch
    if (not rec is nothing) then
        get_property = rec.stringdata(1)
    else
        get_property = ""
    end if
    view.close : check
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' selected_option
'
' Return the OPTION element selected in the SELECT object, or nothing.
'
function selected_option(sel)
    if (sel.selectedIndex >= 0) then
        selected_option = sel.options(sel.selectedIndex).value
    else
        selected_option = ""
    end if
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' null_int
'
' Return the integerdata in the field of the given record, or the empty
' string if the field is null.
'
function null_int(rec, field)
    if (rec.IsNull(field)) then
        null_int = ""
    else
        null_int = rec.integerdata(field)
    end if
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' null_str
'
' Return the stringdata in the field of the given record, or the empty
' string if the field is null
'
function null_str(rec, field)
    if (rec.IsNull(field)) then
        null_str = ""
    else
        null_str = rec.stringdata(field)
    end if
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' clear_opts
'
' Clear out all the <OPTION>s in a <SELECT>
'
sub clear_opts(opts)
    do while (opts.length > 0)
        opts.remove 0
    loop
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' load_opts
'
' Load a <SELECT> container full of <OPTION> elements based on the
' values in an array.
'
sub load_opts(opts, ary)
    clear_opts opts
    dim len : len = -1
    on error resume next : err.clear : len = ubound(ary)
    if (len >= 0) then
        dim i : for i = 0 to len
            opts.add new_option(ary(i))
        next
    elseif (err) then
        err.clear
    end if
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
sub init_izfree_props(db)
    on error resume next
    dim props : set props  = check_object("Scripting.Dictionary")
    set g_main_frame.g_izfree_props = props
    dim view : set view = exec_view(db, "SELECT * FROM `izProperty`")
    dim rec : set rec = view.fetch
    do while not rec is nothing
        props(rec.stringdata(1)) = rec.stringdata(2)
        set rec = view.fetch
    loop
    view.close : check
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
function izfree_property(db, name)
    izfree_property = ""
    on error resume next
    err.clear
    dim keys : set keys = db.PrimaryKeys("izProperty")
    if (err.number = 0) then
        dim view : set view = exec_view(db, "SELECT `Value` FROM " &_
            "`izProperty` WHERE `Name` = '" & name & "'")
        dim rec : set rec = view.fetch
        if (not rec is nothing) then
            izfree_property = rec.stringdata(1)
        end if
    else
        err.clear
    end if
end function
        
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
sub add_izfree_property_table(db)
    on error resume next
    ' add table
    dim view : set view = exec_view(db, "CREATE TABLE `izProperty`(" &_
        "`Name` CHAR(72) NOT NULL, `Value` CHAR NOT NULL " &_
        "PRIMARY KEY `Name`)") : check
    view.close : check
        
    ' now add rows to the validation table for the new table
    set view = db.OpenView("INSERT INTO `_Validation`(" &_
        "`Column`,`Category`,`Description`," &_
        "`Table`,`Nullable`,`MinValue`,`MaxValue`,`KeyTable`,`KeyColumn`," &_
        "`Set`) VALUES (?,?,?,'izProperty','N','','','','','')") : check
    dim rec : set rec = installer().CreateRecord(3) : check
    rec.stringdata(1) = "Name"
    rec.stringdata(2) = "Identifier"
    rec.stringdata(3) = "The name of the izfree property."
    view.execute rec : check
    rec.stringdata(1) = "Value"
    rec.stringdata(2) = "Text"
    rec.stringdata(3) = "The value of the izfree property."
    view.execute rec : check
    view.close : check
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
sub update_izfree_property(db, name, value)
    err.clear
    dim view : set view = db.OpenView("UPDATE `izProperty` SET `Value` = '" &_
        value & "' WHERE `Name` = '" & name & "'")
    view.execute
    view.close
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
sub insert_izfree_property(db, name, value)
    err.clear
    dim view : set view = db.OpenView("INSERT INTO `izProperty`(`Name`,`Value`) " &_
        " VALUES ('" & name & "','" & value & "')")
    view.execute
    view.close
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
sub set_izfree_property(db, name, value)
    on error resume next
    dim props : set props = g_main_frame.g_izfree_props
    dim keys : set keys = db.PrimaryKeys("izProperty")
    if (err.number <> 0) then
        err.clear
        add_izfree_property_table db
        insert_izfree_property db, name, value
        init_izfree_props db
    else
        if (props is nothing) then
            init_izfree_props db
        end if
        if (not props.exists(name)) then
            insert_izfree_property db, name, value
        else
            update_izfree_property db, name, value
        end if
        props(name) = value
    end if
end sub

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
function max(a, b)
    if (a > b) then max = a else max = b
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
function scrape_file_counter(db)
    dim view : set view = exec_view(db, "SELECT `File` FROM `File`")
    dim rec : set rec = view.fetch
    dim counter : counter = 0
    dim num_recs : num_recs = 0
    do while not rec is nothing
        dim key : key = rec.stringdata(1)
        if (left(key, 1) = "f") then
            dim i : i = 2
            do while (IsNumeric(mid(key, i, 1)))
                i = i + 1
            loop
            if (mid(key, i, 1) = "_") then
                counter = max(counter, cint(mid(key, 2, i-2)))
            end if
        end if
        num_recs = num_recs + 1
        set rec = view.fetch
    loop
    view.close
    scrape_file_counter = max(counter, num_recs)
end function
