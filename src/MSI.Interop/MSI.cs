using System;
using System.Collections;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Pahvant.MSI
{
    #region MSIHandle
    internal class MSIHandle : IDisposable
    {
        public MSIHandle(IntPtr handle)
        {
            m_handle = handle;
        }
        ~MSIHandle()
        {
            Dispose(false);
        }

        public IntPtr Handle
        {
            get { return m_handle; }
            set { m_handle = value; }
        }

        #region IDisposable Members
        public void Dispose()
        {
            Dispose(true);
        }
        #endregion

        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                GC.SuppressFinalize(this);
                if (m_handle != IntPtr.Zero)
                {
                    Installer.TR(MsiCloseHandle(m_handle));
                }
                m_handle = IntPtr.Zero;
            }
            else
            {
            }
        }

        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiCloseHandle(IntPtr handle);

        private IntPtr m_handle = IntPtr.Zero;
    }
    #endregion MSIHandle

    #region Enumerations
    [Flags]
    public enum AdvertiseFlags
    {
        MachineAssign                   = 0,
        UserAssign                      = 1
    }
    [Flags]
    public enum AdvertiseOptionFlags
    {
        None                            = 0,
        Instance                        = 1
    }
    [Flags]
    public enum ArchitectureFlags
    {
        Current                         = 0,
        X86                             = 1,
        IA64                            = 2,
        AMD64                           = 4
    }
    public enum Condition
    {
        False                           = 0,
        True                            = 1,
        None                            = 2,
        Error                           = 3
    }
    public enum CostTree
    {
        SelfOnly                        = 0,
        Children                        = 1,
        Parents                         = 2,
        Reserved                        = 3
    }
    public enum DatabaseError
    {
        InvalidArg                      = -3,
        MoreData                        = -2,
        FunctionError                   = -1,
        NoError                         = 0,
        DuplicateKey                    = 1,
        Required                        = 2,
        BadLink                         = 3,
        Overflow                        = 4,
        Underflow                       = 5,
        NotInset                        = 6,
        BadVersion                      = 7,
        BadCase                         = 8,
        BadGuid                         = 9,
        BadWildcard                     = 10,
        BadIdentifier                   = 11,
        BadLanguage                     = 12,
        BadFilename                     = 13,
        BadPath                         = 14,
        BadCondition                    = 15,
        BadFormatted                    = 16,
        BadTemplate                     = 17,
        BadDefaultDir                   = 18,
        BadRegPath                      = 19,
        BadCustomSource                 = 20,
        BadProperty                     = 21,
        MissingData                     = 22,
        BadCategory                     = 23,
        BadKeyTable                     = 24,
        BadMaxMinValues                 = 25,
        BadCabinet                      = 26,
        BadShortcut                     = 27,
        StringOverflow                  = 28,
        BadLocalizeAttrib               = 29
    }
    [Flags]
    public enum InstallFeatureAttribute
    {
        FavorLocal                      = 0x1,
        FavorSource                     = 0x2,
        FollowParent                    = 0x4,
        FavorAdvertise                  = 0x8,
        DisallowAdvertise               = 0x10,
        NoUnsupportedAdvertise          = 0x20
    }
    public enum InstallLevel
    {
        Default                         = 0,
        Minimum                         = 1,
        Maximum                         = 0xFFFF
    }
    [Flags]
    public enum InstallLogAttributes
    {
        Append                          = 0x1,
        FlushEachLine                   = 0x2
    }
    public enum InstallLogMode
    {
        FatalExit                       = 0x1,
        Error                           = 0x2,
        Warning                         = 0x4,
        User                            = 0x8,
        Info                            = 0x10,
        ResolveSource                   = 0x20,
        OutOfDiskSpace                  = 0x40,
        ActionStart                     = 0x80,
        ActionData                      = 0x100,
        CommonData                      = 0x200,
        PropertyDump                    = 0x400,
        Verbose                         = 0x800,
        ExtraDebug                      = 0x1000,
        Progress                        = 0x2000,
        Initialize                      = 0x4000,
        Terminate                       = 0x8000,
        ShowDialog                      = 0x10000
    }
    public enum InstallMessage
    {
        FatalExit                       = 0x0000000,
        Error                           = 0x1000000,
        Warning                         = 0x2000000,
        User                            = 0x3000000,
        Info                            = 0x4000000,
        FilesInUse                      = 0x5000000,
        ResolveSource                   = 0x6000000,
        OutOfDiskSpace                  = 0x7000000,
        ActionStart                     = 0x8000000,
        ActionData                      = 0x9000000,
        Progress                        = 0XA000000,
        CommonData                      = 0xB000000,
        Initialize                      = 0xC000000,
        Terminate                       = 0xD000000,
        ShowDialog                      = 0xE000000
    }
    public enum InstallMode
    {
        NoSourceResolution              = -3,
        NoDetection                     = -2,
        Existing                        = -1,
        Default                         = 0
    }
    public enum InstallState
    {
        NotUsed                         = -7,
        BadConfig                       = -6,
        Incomplete                      = -5,
        SourceAbsent                    = -4,
        MoreData                        = -3,
        InvalidArg                      = -2,
        Unknown                         = -1,
        Broken                          = 0,
        Advertised                      = 1,
        Removed                         = 1,
        Absent                          = 2,
        Local                           = 3,
        Source                          = 4,
        Default                         = 5
    }
    public enum InstallType
    {
        Default                         = 0,
        NetworkImage                    = 1,
        SingleInstance                  = 2
    }
    [Flags]
    public enum InstallUILevel
    {
        NoChange                        = 0,
        Default                         = 1,
        None                            = 2,
        Basic                           = 3,
        Reduced                         = 4,
        Full                            = 5,
        EndDialog                       = 0x080,
        ProgressOnly                    = 0x040,
        HideCancel                      = 0x020,
        SourceResOnly                   = 0x100
    }
    public enum Modify
    {
        Seek                            = -1,
        Refresh                         = 0,
        Insert                          = 1,
        Update                          = 2,
        Assign                          = 3,
        Replace                         = 4,
        Merge                           = 5,
        Delete                          = 6,
        InsertTemporary                 = 7,
        Validate                        = 8,
        ValidateNew                     = 9,
        ValidateField                   = 10,
        ValidateDelete                  = 11
    }
    [Flags]
    public enum ReinstallMode
    {
        Repair                          = 0x001,
        FileMissing                     = 0x002,
        FileOlderVersion                = 0x004,
        FileEqualVersion                = 0x008,
        FileExact                       = 0x010,
        FileVerify                      = 0x020,
        FileReplace                     = 0x040,
        MachineData                     = 0x080,
        UserData                        = 0x100,
        Shortcut                        = 0x200,
        Package                         = 0x400
    }
    public enum RunMode
    {
        Admin                           = 0,
        Advertise                       = 1,
        Maintenance                     = 2,
        RollbackEnabled                 = 3,
        LogEnabled                      = 4,
        Operations                      = 5,
        RebootAtEnd                     = 6,
        RebootNow                       = 7,
        Cabinet                         = 8,
        SourceShortNames                = 9,
        TargetShortNames                = 10,
        Reserved11                      = 11,
        Windows9x                       = 12,
        ZAWEnabled                      = 13,
        Reserved14                      = 14,
        Reserved15                      = 15,
        Scheduled                       = 16,
        Rollback                        = 17,
        Commit                          = 18
    }
    [Flags]
    public enum ScriptFlags
    {
        CacheInfo                       = 0x1,
        Shortcuts                       = 0x4,
        MachineAssign                   = 0x8,
        RegDataConfigInfo               = 0x20,
        ValidateTransformsList          = 0x40,
        RegDataClassInfo                = 0x80,
        RegDataExtensionInfo            = 0x100,
        RegDataAppInfo                  = RegDataClassInfo | RegDataExtensionInfo,
        RegData                         = RegDataAppInfo | RegDataConfigInfo
    }
    public enum TransformError
    {
        AddExistingRow                  = 0x00000001,
        DelMissingRow                   = 0x00000002,
        AddExistingTable                = 0x00000004,
        DelMissingTable                 = 0x00000008,
        UpdateMissingRow                = 0x00000010,
        ChangeCodePage                  = 0x00000020,
        ViewTransform                   = 0x00000100,
    }
    public enum TransformValidate
    {
        Language                        = 0x00000001,
        Product                         = 0x00000002,
        Platform                        = 0x00000004,
        MajorVersion                    = 0x00000008,
        MinorVersion                    = 0x00000010,
        UpdateVersion                   = 0x00000020,
        NewLessBaseVersion              = 0x00000040,
        NewLessEqualBaseVersion         = 0x00000080,
        NewEqualBaseVersion             = 0x00000100,
        NewGreaterEqualBaseVersion      = 0x00000200,
        NewGreaterBaseVersion           = 0x00000400,
        UpgradeCode                     = 0x00000800
    }
    public enum UserInfoState
    {
        MoreData                        = -3,
        InvalidArg                      = -2,
        Unknown                         = -1,
        Absent                          = 0,
        Present                         = 1
    }
    #endregion
}
