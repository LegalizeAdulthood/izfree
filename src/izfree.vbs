''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
option explicit
on error resume next

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
function check
    check = 0
    if (Err.number) then
        check = err.number
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
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' check_object
'
' Call CreateObject and then check the results.
'
function check_object(progid)
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
    if (window.name = "") then
        set installer = g_installer
    else
        set installer = window.parent.g_installer
    end if
end function
function wsh()
    if (window.name = "") then
        set wsh = g_wsh
    else
        set wsh = window.parent.g_wsh
    end if
end function
function fso()
    if (window.name = "") then
        set fso = g_fso
    else
        set fso = window.parent.g_fso
    end if
end function
function generator()
    if (window.name = "") then
        set generator = g_generator
    else
        set generator = window.parent.g_generator
    end if
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
    ' look for characters that can be in long names, but not in short
    dim tmp : tmp = wildname
    const bad_short_chars = " +,;=[]"
    dim bad_short_name : bad_short_name = len(wildname) > 12
    if (not bad_short_name) then
        dim i : for i = 1 to len(bad_short_chars)
            if (instr(wildname, mid(bad_short_chars, i, 1))) then
                dim bad : bad = instr(tmp, mid(bad_short_chars, i, 1))
                do while (bad)
                    tmp = left(tmp, bad-1) & "_" & mid(tmp, bad+1)
                    bad = instr(tmp, mid(bad_short_chars, i, 1))
                loop
                bad_short_name = true
            end if
        next
    end if

    ' check some length constraints    
    dim dot : dot = instrrev(wildname, ".")
    if (dot > 9) or (dot and len(wildname)-dot > 3) or _
            (dot = 0 and len(wildname) > 8) then
        bad_short_name = true
    end if
    
    ' need to produce short|long form
    if (bad_short_name) then
        dot = instrrev(tmp, ".")
        if (dot) then
            if (dot > 9) then
                wit_filename = left(tmp, 8) & mid(tmp, dot, 4)
            else
                wit_filename = left(tmp, dot+3)
            end if
        else
            wit_filename = left(tmp, 8)
        end if
        wit_filename = wit_filename & "|" & wildname
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
sub sort(ary)
    dim i : for i = 0 to ubound(ary)-2
        dim j : for j = i+1 to ubound(ary)-1
            if (ary(j) < ary(i)) then
                dim tmp : tmp = ary(j) : ary(j) = ary(i) : ary(i) = tmp
            end if
        next
    next
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
    window.showModalDialog "help.html", label, _
        "resizable: yes; dialogHeight: 300px; dialogWidth: 500px;"
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
    if (folder.IsFileSystem) then
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
    read_setting = wsh.RegRead("HKCU\Software\Pahvant\izfree\" & tool & name)
end function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' write_setting
'
' Write a setting for a tool into the registry.
'
sub write_setting(tool, name, value)
    if (tool <> "") then tool = tool & "\"
    wsh.RegWrite "HKCU\Software\Pahvant\izfree\" & tool & name, value
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
