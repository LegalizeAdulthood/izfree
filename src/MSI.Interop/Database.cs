using System;
using System.Collections;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
	/// <summary>
	/// Summary description for Database.
	/// </summary>
    public class Database : IDisposable
    {
        #region Enumerations
        public enum AssemblyAttributes
        {
            URT     = 0,
            Win32   = 1
        }
        [Flags]
        public enum ClassAttributes
        {
            Default         = 0,
            RelativePath    = 1
        }
        [Flags]
        public enum ControlAttributes
        {
            Visible           = 0x00000001,
            Enabled           = 0x00000002,
            Sunken            = 0x00000004,
            Indirect          = 0x00000008,
            Integer           = 0x00000010,
            RTLRO             = 0x00000020,
            RightAligned      = 0x00000040,
            LeftScroll        = 0x00000080,
            BiDi              = RTLRO | RightAligned | LeftScroll,
            Transparent       = 0x00010000,
            NoPrefix          = 0x00020000,
            NoWrap            = 0x00040000,
            FormatSize        = 0x00080000,
            UsersLanguage     = 0x00100000,
            Multiline         = 0x00010000,
            PasswordInput     = 0x00200000,
            Progress95        = 0x00010000,
            RemovableVolume   = 0x00010000,
            FixedVolume       = 0x00020000,
            RemoteVolume      = 0x00040000,
            CDROMVolume       = 0x00080000,
            RAMDiskVolume     = 0x00100000,
            FloppyVolume      = 0x00200000,
            ShowRollbackCost  = 0x00400000,
            Sorted            = 0x00010000,
            ComboList         = 0x00020000,
            ImageHandle       = 0x00010000,
            PushLike          = 0x00020000,
            Bitmap            = 0x00040000,
            Icon              = 0x00080000,
            FixedSize         = 0x00100000,
            IconSize16        = 0x00200000,
            IconSize32        = 0x00400000,
            IconSize48        = 0x00600000,
            HasBorder         = 0x01000000
        }
        [Flags]
        public enum ComponentAttributes
        {
            LocalOnly           = 0x00000000,
            SourceOnly          = 0x00000001,
            Optional            = 0x00000002,
            RegistryKeyPath     = 0x00000004,
            SharedDllRefCount   = 0x00000008,
            Permanent           = 0x00000010,
            ODBCDataSource      = 0x00000020,
            Transitive          = 0x00000040,
            NeverOverwrite      = 0x00000080,
            SixtyFourBit        = 0x00000100
        }
        [Flags]
        public enum CustomActionType
        {
            Dll              = 0x00000001,
            Exe              = 0x00000002,
            TextData         = 0x00000003,
            JScript          = 0x00000005,
            VBScript         = 0x00000006,
            Install          = 0x00000007,
            BinaryData       = 0x00000000,
            SourceFile       = 0x00000010,
            Directory        = 0x00000020,
            Property         = 0x00000030,
            Continue         = 0x00000040,
            Async            = 0x00000080,
            FirstSequence    = 0x00000100,
            OncePerProcess   = 0x00000200,
            ClientRepeat     = 0x00000300,
            InScript         = 0x00000400,
            Rollback         = 0x00000100,
            Commit           = 0x00000200,
            NoImpersonate    = 0x00000800,
            TSAware          = 0x00004000,
            SixtyFourBitScript = 0x00001000,
            HideTarget       = 0x00002000
        }
        [Flags]
        public enum DialogAttributes
        {
            Visible          = 0x00000001,
            Modal            = 0x00000002,
            Minimize         = 0x00000004,
            SysModal         = 0x00000008,
            KeepModeless     = 0x00000010,
            TrackDiskSpace   = 0x00000020,
            UseCustomPalette = 0x00000040,
            RTLRO            = 0x00000080,
            RightAligned     = 0x00000100,
            LeftScroll       = 0x00000200,
            BiDi             = RTLRO | RightAligned | LeftScroll,
            Error            = 0x00010000
        }
        [Flags]
        public enum FeatureAttributes
        {
            FavorLocal              = 0x00000000,
            FavorSource             = 0x00000001,
            FollowParent            = 0x00000002,
            FavorAdvertise          = 0x00000004,
            DisallowAdvertise       = 0x00000008,
            UIDisallowAbsent        = 0x00000010,
            NoUnsupportedAdvertise  = 0x00000020
        }
        [Flags]
        public enum FileAttributes
        {
            ReadOnly       = 0x00000001,
            Hidden         = 0x00000002,
            System         = 0x00000004,
            Reserved0      = 0x00000008,
            Reserved1      = 0x00000040,
            Reserved2      = 0x00000080,
            Reserved3      = 0x00000100,
            Vital          = 0x00000200,
            Checksum       = 0x00000400,
            PatchAdded     = 0x00001000,
            Noncompressed  = 0x00002000,
            Compressed     = 0x00004000,
            Reserved4      = 0x00008000
        }
        public enum FileInstallMode
        {
            OnInstall,
            OnRemove,
            OnBoth
        }
        public enum IniFileAction
        {
            AddLine    = 0x00000000,
            CreateLine = 0x00000001,
            RemoveLine = 0x00000002,
            AddTag     = 0x00000003,
            RemoveTag  = 0x00000004,
        }
        public enum InstallErrorControl
        {
            Vital
        }
        [Flags]
        public enum LocatorType
        {
            Directory       = 0x00000000,
            FileName        = 0x00000001,
            RawValue        = 0x00000002,
            SixtyFourBit    = 0x00000010
        }
        public enum MoveFileOptions
        {
            Copy            = 0,
            Move            = 1
        }
        public enum ODBCDataSourceRegistration
        {
            PerMachine      = 0,
            PerUser         = 1
        }
        [Flags]
        public enum OpenMode
        {
            ReadOnly        = 0,
            Transact        = 1,
            Direct          = 2,
            Create          = 3,
            CreateDirect    = 4,
            ListScript      = 5,
            PatchFileW      = 16,
            PatchFileA      = 32
        }
        [Flags]
        public enum PatchAttributes
        {
            Vital           = 0,
            NonVital        = 1
        }
        public enum RegistryRoot
        {
            ClassesRoot     = 0,
            CurrentUser     = 1,
            LocalMachine    = 2,
            Users           = 3
        }
        public enum RemoveFileInstallMode
        {
            OnInstall       = 1,
            OnRemove        = 2,
            OnBoth          = 3,
        }
        public enum ServiceControlEvent
        {
            Start           = 0x01,
            Stop            = 0x02,
            Delete          = 0x08,
            UninstallStart  = 0x10,
            UninstallStop   = 0x20,
            UninstallDelete = 0x80
        }
        [Flags]
        public enum ServiceInstallErrorControl
        {
            Ignore          = 0,
            Normal          = 1,
            Critical        = 3,
            Vital           = 0x00008000
        }
        public enum State
        {
            Error = -1,
            Read = 0,
            Write = 1
        };
        public enum SumInfoSourceType
        {
            SFN,
            Compressed,
            AdminImage
        }
        [Flags]
        public enum TextStyleBits
        {
            Bold            = 0x1,
            Italic          = 0x2,
            Underline       = 0x4,
            Strike          = 0x8
        }
        [Flags]
        public enum UpgradeAttributes
        {
            MigrateFeatures     = 0x1,
            OnlyDetect          = 0x2,
            IgnoreRemoveFailure = 0x4,
            VersionMinInclusive = 0x100,
            VersionMaxInclusive = 0x200,
            LanguagesExclusive  = 0x400
        }
        #endregion

        #region Construction
        public Database(IntPtr handle)
        {
            m_handle = new MSIHandle(handle);
        }

        public Database(string filename, OpenMode mode)
        {
            IntPtr handle;
            TR(MsiOpenDatabase(filename, (IntPtr) mode, out handle));
            m_handle = new MSIHandle(handle);
        }
        public Database(string filename, string persist)
        {
            IntPtr handle;
            TR(MsiOpenDatabase(filename, persist, out handle));
            m_handle = new MSIHandle(handle);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiOpenDatabase(string path,
            string persist, out IntPtr database);

        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiOpenDatabase(string path,
            IntPtr openMode, out IntPtr database);
        #endregion

        ~Database()
        {
            Dispose(false);
        }

        #region Properties
        public IntPtr Handle
        {
            get { return m_handle.Handle; }
        }

        public SummaryInformation SummaryInformation(int count)
        {
            return new SummaryInformation(this, count);
        }

        #region PrimaryKeys
        public string[] PrimaryKeys(string tableName)
        {
            IntPtr marshal;
            TR(MsiDatabaseGetPrimaryKeys(m_handle.Handle, tableName,
                out marshal));
            using (Record record = new Record(marshal))
            {
                string[] keys = new string[record.FieldCount];
                for (int i = 0; i < record.FieldCount; i++)
                {
                    keys[i] = record.GetString(i);
                }
                return keys;
            }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDatabaseGetPrimaryKeys(
            IntPtr database, string tableName, out IntPtr record);
        #endregion

        #region IsTablePersistent
        public bool IsTablePersistent(string table)
        {
            return MsiDatabaseIsTablePersistent(m_handle.Handle, table) == 0;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDatabaseIsTablePersistent(
            IntPtr database, string table);
        #endregion

        #region DatabaseState
        public State DatabaseState
        {
            get { return (State) MsiGetDatabaseState(m_handle.Handle); }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetDatabaseState(IntPtr database);
        #endregion

        #endregion

        #region Methods

        #region ApplyTransform
        public void ApplyTransform(string transformFile, int errorConditions)
        {
            TR(MsiDatabaseApplyTransform(m_handle.Handle, transformFile,
                errorConditions));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDatabaseApplyTransform(
            IntPtr database, string transformFile, int errorConditions);
        #endregion

        #region Commit
        public void Commit()
        {
            TR(MsiDatabaseCommit(m_handle.Handle));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDatabaseCommit(IntPtr handle);
        #endregion

        #region CreateTransformSummaryInfo
        public void CreateTransformSummaryInfo(Database reference,
            string transformFile, int errorConditions, int validation)
        {
            TR(MsiCreateTransformSummaryInfo(m_handle.Handle, reference.Handle,
                transformFile, errorConditions, validation));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiCreateTransformSummaryInfo(
            IntPtr database, IntPtr databaseReference,
            string transformFile, int errorConditions, int validation);
        #endregion

        #region EnableUIPreview
        public UIPreview EnableUIPreview()
        {
            IntPtr handle;
            TR(MsiEnableUIPreview(m_handle.Handle, out handle));
            return new UIPreview(handle);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnableUIPreview(IntPtr database,
            out IntPtr preview);
        #endregion

        #region Export
        public void Export(string tableName, string folderPath, string fileName)
        {
            TR(MsiDatabaseExport(m_handle.Handle, tableName,
                folderPath, fileName));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDatabaseExport(IntPtr database,
            string tableName, string folderPath, string fileName);
        #endregion

        #region GenerateTransform
        public void GenerateTransform(Database reference, string transformFile)
        {
            TR(MsiDatabaseGenerateTransform(m_handle.Handle, reference.Handle,
                transformFile, 0, 0));
        }            
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDatabaseGenerateTransform(
            IntPtr database, IntPtr databaseReference,
            string transformFile, int reserved1, int reserved2);
        #endregion

        #region GetFeatureInfo
        public void GetFeatureInfo(string feature,
            InstallFeatureAttribute attributes,
            out string title, out string help)
        {
            int titleLength = Installer.MaxPathLength;
            StringBuilder titleBuff = new StringBuilder(titleLength);
            int helpLength = Installer.MaxPathLength;
            StringBuilder helpBuff = new StringBuilder(helpLength);
            UInt32 attributeBuffer = (UInt32) attributes;
            TR(MsiGetFeatureInfo(Handle, feature, ref attributeBuffer,
                titleBuff, ref titleLength, helpBuff, ref helpLength));
            title = titleBuff.ToString();
            help = helpBuff.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFeatureInfo(
            IntPtr product, string feature, ref UInt32 attributes,
            StringBuilder title, ref int titleLength,
            StringBuilder help, ref int helpLength);
        #endregion

        #region Import
        public void Import(string folderPath, string fileName)
        {
            TR(MsiDatabaseImport(m_handle.Handle, folderPath, fileName));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDatabaseImport(IntPtr database,
            string folderPath, string fileName);
        #endregion

        #region Merge
        public void Merge(Database source, string tableName)
        {
            TR(MsiDatabaseMerge(m_handle.Handle, source.Handle, tableName));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDatabaseMerge(IntPtr database,
            IntPtr databaseMerge, string tableName);
        #endregion

        #region OpenView
        public View OpenView(string sql)
        {
            return new View(this, sql);
        }
        #endregion
        #endregion

        private void TR(UInt32 result)
        {
            if (m_handle != null)
            {
                Installer.TR(this, result);
            }
            else
            {
                Installer.TR(result);
            }
        }

        private MSIHandle m_handle;
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
                m_handle.Dispose();
            }
        }
    }
}
