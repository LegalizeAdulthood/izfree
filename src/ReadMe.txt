Building izfree
---------------

izfree is mostly HTML and VBScipt.  However, there are some things that
aren't conveniently exposed to scripting environments, such as
::CoGenerateGuid function and the VS_VERSION_INFO structure of VXD files
(VS_VERSION_INFO for PE files can be had from Scripting.FileSystemObject).
These two items are exposed to the scripting environment through COM
wrappers around their functionality.  The guidgen DLL project provides
these COM objects to the script.  Guidgen has a small C++ test program
that exercises the functionality.

The izMonitor project is a local server EXE project that extracts COM
registration information from a self-registering COM server.

Both the guidgen and izMonitor servers are written in C++.

izfree.hhp and izfree.hhc contain the definition of the HTML Help project
that creates izfree.chm.  You will need the HTML Help compiler in order
to build that project.  The compiler is available free of charge from
the MSDN web site.  Search for "HTML Help Start Page"; MS moves things
around too often for me to try and track the exact URL.
<http://msdn.microsoft.com>

The HTML portions of izfree are developed using Visual InterDev.  If
you wish to contribute to izfree, you will find some form of script
debugger very useful.  I use Visual InterDev -- see the project debug
options for how I run it.  You will need to edit the path to the source
on your machine for the debug configuration to work properly, as I could
not determine how to use relative paths in that instance.

Coding Style
------------
In general the code is appropriately commented and formatted for 75
or so columns.  Other than that I haven't followed any one convention
too closely.  My personal preference is for identifiers to be in lower
case with words separated by underscores, but the AppWizard generates
mixed-case identifiers with no separation between words.  So there is
a mix of identifier styles in the code.
