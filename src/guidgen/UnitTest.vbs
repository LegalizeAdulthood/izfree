' VBScript source code
sub TestGenerator()
    dim generator : set generator = CreateObject("izfree.GUIDGen")
    WScript.Echo "Testing GUID generation: " & generator.Generate()
    set generator = nothing
end sub

sub TestFileVersion(file)
    dim versionator : set versionator = CreateObject("izfree.FileVersion")
    WScript.Echo "File: " & file & vbCrLf &_
        "Version: " & versionator.Version(file) & vbCrLf
end sub

TestGenerator
TestFileVersion WScript.Arguments(0)
WScript.Quit 0
