Building izfree 2.0
-------------------

izfree originated as an HTML application written mostly in HTML and
VBScript.  A few C++ components to accomplish things not easily done
from script, such as the ::CoGenerateGuid function and the
VS_VERSION_INFO structure of VXD files (VS_VERSION_INFO for PE files
can be had from Scripting.FileSystemObject).  These two items are
implemented as COM objects.  The guidgen DLL project provides the COM
objects for GUID generation and file version support.  Guidgen has a
small C++ test program that exercises the functionality as well as a
small test script.

The izMonitor project is a local server EXE project that extracts COM
registration information from a self-registering COM server.

Both the guidgen and izMonitor objects are written in C++.

izfree 2.0 is a complete rewrite of the script and HTML portion as a C#
.NET Windows application.  This allows for a real UI with menu bars and
the normal behavior expected from a GUI application instead of the
approximations available in HTML.  It also eliminates a dependency on
ActiveX controls for tree views and list views, which can cause some
problems when moving from one OS environment to another.  In particular
Windows XP seems to have some difficulty with the tree view control.

izfree.hhp and izfree.hhc contain the definition of the HTML Help project
that creates izfree.chm.  You will need the HTML Help compiler in order
to build that project.  The compiler is available free of charge from
the MSDN web site.  Search for "HTML Help Start Page"; MS moves things
around too often for me to try and track the exact URL.
<http://msdn.microsoft.com>

The C# portions of izfree are developed using Visual Studio .NET 2003
and the .NET Framework v1.1.  If you wish to contribute to izfree, you
will most likely need Visual Studio .NET 2003 in order to do any work
on the GUI.  The C++ components can be compiled with VC6, although the
code base has now been migrated to Visual Studio .NET 2003 project files.

Coding Style
------------
In general the code is appropriately commented and formatted for 75
or so columns.  Other than that I haven't followed any one convention
too closely.  For the C# code, I have tried to follow the .NET coding
guidelines recommended by Microsoft.

"Hungarian" notation is an abomination!  It is not used anywhere in the
code.
