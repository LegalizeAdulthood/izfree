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
            URT,
            Win32
        }
        public enum ClassAttributes
        {
            RelativePath
        }
        public enum ControlAttributes
        {
            Visible,
            Enabled,
            Sunken,
            Indirect,
            Integer,
            RTLRO,
            RightAligned,
            LeftScroll,
            BiDi,
            Transparent,
            NoPrefix,
            NoWrap,
            FormatSize,
            UsersLanguage,
            Multiline,
            PasswordInput,
            Progress95,
            RemovableVolume,
            FixedVolume,
            RemoteVolume,
            CDROMVolume,
            RAMDiskVolume,
            FloppyVolume,
            ShowRollbackCost,
            Sorted,
            ComboList,
            ImageHandle,
            PushLike,
            Bitmap,
            Icon,
            FixedSize,
            IconSize16,
            IconSize32,
            IconSize48,
            HasBorder
        }
        public enum ComponentAttributes
        {
            LocalOnly,
            SourceOnly,
            Optional,
            RegistryKeyPath,
            SharedDllRefCount,
            Permanent,
            ODBCDataSource,
            Transitive,
            NeverOverwrite,
            SixtyFourBit
        }
        public enum CustomActionType
        {
            Dll,
            Exe,
            TextData,
            JScript,
            VBScript,
            Install,
            BinaryData,
            SourceFile,
            Directory,
            Property,
            Continue,
            Async,
            FirstSequnce,
            OncePerProcess,
            ClientRepeat,
            InScript,
            Rollback,
            Commit,
            NoImpersonate,
            TSAware,
            SixtyFourBitScript,
            HideTarget
        }
        public enum DialogAttributes
        {
            Visible,
            Modal,
            Minimize,
            SysModal,
            KeepModeless,
            TrackDiskSpace,
            UseCustomPalette,
            RTLRO,
            RightAligned,
            LeftScroll,
            BiDi,
            Error
        }
        public enum FeatureAttributes
        {
            FavorLocal,
            FavorSource,
            FollowParent,
            FavorAdvertise,
            DisallowAdvertise,
            UIDisallowAbsent,
            NoUnsupportedAdvertise
        }
        public enum FileAttributes
        {
            ReadOnly,
            Hidden,
            System,
            Reserved0,
            Reserved1,
            Reserved2,
            Reserved3,
            Vital,
            Checksum,
            PatchAdded,
            Noncompressed,
            Compressed,
            Reserved4
        }
        public enum FileInstallMode
        {
            OnInstall,
            OnRemove,
            OnBoth
        }
        public enum IniFileAction
        {
            AddLine,
            CreateLine,
            RemoveLine,
            AddTag,
            RemoveTag
        }
        public enum InstallErrorControl
        {
            Vital
        }
        public enum LocatorType
        {
            Directory,
            FileName,
            RawValue,
            SixtyFourBit
        }
        public enum MoveFileOptions
        {
            Move
        }
        public enum ODBCDataSourceRegistration
        {
            PerMachine,
            PerUser
        }
        public enum PatchAttributes
        {
            NonVital
        }
        public enum RegistryRoot
        {
            ClassesRoot,
            CurrentUser,
            LocalMachine,
            Users
        }
        public enum ServiceControlEvent
        {
            Start,
            Stop,
            Delete,
            UninstallStart,
            UninstallStop,
            UninstallDelete
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
        public enum TextStyleBits
        {
            Bold,
            Italic,
            Underline,
            Strike
        }
        public enum UpgradeAttributes
        {
            MigrateFeatures,
            OnlyDetect,
            IgnoreRemoveFailure,
            VersionMinInclusive,
            VersionMaxInclusive,
            LanguagesExclusive
        }
        [Flags]
        public enum OpenMode
        {
            ReadOnly = 0,
            Transact = 1,
            Direct = 2,
            Create = 3,
            CreateDirect = 4,
            // ListScript = 5,
            PatchFileW = 16,
            PatchFileA = 32
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
                MSI.Installer.TR(this, result);
            }
            else
            {
                MSI.Installer.TR(result);
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

    public class Record : IDisposable
    {
        #region Constructors/Destructors
        public Record(int count)
        {
            m_handle = new MSIHandle(MsiCreateRecord(count));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern IntPtr MsiCreateRecord(int count);

        public Record(IntPtr handle)
        {
            m_handle = new MSIHandle(handle);
        }
        #endregion 

        #region ClearData
        public void ClearData()
        {
            TR(MsiRecordClearData(m_handle.Handle));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiRecordClearData(IntPtr record);
        #endregion

        #region DataSize
        public int DataSize(int field)
        {
            return (int) MsiRecordDataSize(m_handle.Handle, (UInt32) field);
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordDataSize(
            IntPtr record, UInt32 field);
        #endregion

        #region SetString
        public void SetString(int index, string data)
        {
            TR(MsiRecordSetString(m_handle.Handle, (UInt32) index, data));
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordSetString(IntPtr record,
            UInt32 field, string data);
        #endregion

        #region GetString
        public string GetString(int field)
        {
            StringBuilder sb = new StringBuilder(DataSize(field)+1);
            UInt32 count = (UInt32) sb.Capacity;
            TR(MsiRecordGetString(m_handle.Handle, (UInt32) field,
                sb, ref count));
            return sb.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordGetString(
            IntPtr record, UInt32 field, StringBuilder data, ref UInt32 count);
        #endregion

        #region GetInteger
        public int GetInteger(int field)
        {
            return MsiRecordGetInteger(m_handle.Handle, (UInt32) field);
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern int MsiRecordGetInteger(
            IntPtr record, UInt32 field);
        #endregion

        #region SetInteger
        public void SetInteger(int field, int data)
        {
            TR(MsiRecordSetInteger(m_handle.Handle, (UInt32) field, data));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiRecordSetInteger(
            IntPtr record, UInt32 field, int data);
        #endregion

        #region IsNull
        public bool IsNull(int field)
        {
            return MsiRecordIsNull(m_handle.Handle, (UInt32) field) != 0;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern int MsiRecordIsNull(
            IntPtr record, UInt32 field);
        #endregion

        #region ReadStream
        public byte[] ReadStream(int field)
        {
            byte[] bytes = new byte[] { };
            int count = bytes.Length;
            TR(MsiRecordReadStream(m_handle.Handle, (UInt32) field,
                bytes, ref count));
            return bytes;            
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordReadStream(IntPtr record,
            UInt32 field, byte[] buffer, ref int bufferLength);
        #endregion

        #region SetStream
        public void SetStream(int field, string path)
        {
            TR(MsiRecordSetStream(m_handle.Handle, (UInt32) field, path));
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordSetStream(IntPtr record,
            UInt32 field, string path);
        #endregion

        #region FieldCount
        public int FieldCount
        {
            get { return (int) MsiRecordGetFieldCount(m_handle.Handle); }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiRecordGetFieldCount(IntPtr record);
        #endregion


        private static void TR(UInt32 result)
        {
            MSI.Installer.TR(result);
        }

        public IntPtr Handle
        {
            get { return m_handle.Handle; }
        }

        private MSIHandle m_handle;
        #region IDisposable Members
        public void Dispose()
        {
            Dispose(true);
        }
        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                GC.SuppressFinalize(this);
                m_handle.Dispose();
            }
        }
        ~Record()
        {
            Dispose(false);
        }
        #endregion
    }

    public class View : IDisposable
    {
        #region Enumerations
        public enum Modify
        {
            Seek = -1,
            Refresh = 0,
            Insert = 1,
            Update = 2,
            Assign = 3,
            Replace = 4,
            Merge = 5,
            Delete = 6,
            InsertTemporary = 7,
            Validate = 8,
            ValidateNew = 9,
            ValidateField = 10,
            ValidateDelete = 11
        }
        public enum ColumnInfo
        {
            Names = 0,
            Types = 1
        }
        #endregion

        public View(IntPtr handle)
        {
            m_handle = new MSIHandle(handle);
        }

        public View(Database db, string sql)
        {
            IntPtr handle;
            TR(db, MsiDatabaseOpenView(db.Handle, sql, out handle));
            m_handle = new MSIHandle(handle);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDatabaseOpenView(IntPtr database,
            string query, out IntPtr view);

        #region Execute
        public void Execute()
        {
            TR(MsiViewExecute(m_handle.Handle, IntPtr.Zero));
        }
        public void Execute(Record args)
        {
            TR(MsiViewExecute(m_handle.Handle, args.Handle));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiViewExecute(IntPtr view, IntPtr record);
        #endregion

        #region Close
        public void Close()
        {
            TR(MsiViewClose(m_handle.Handle));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiViewClose(IntPtr view);
        #endregion

        #region Fetch
        public Record Fetch()
        {
            IntPtr record;
            UInt32 res = MsiViewFetch(m_handle.Handle, out record);
            if (0 == res)
            {
                return new Record(record);
            }
            else if (259 != res)
            {
                TR(res);
            }
            return null;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiViewFetch(IntPtr view, out IntPtr record);
        #endregion

        private static void TR(UInt32 result)
        {
            MSI.Installer.TR(result);
        }

        private static void TR(Database db, UInt32 result)
        {
            MSI.Installer.TR(db, result);
        }

        private MSIHandle m_handle;
        #region IDisposable Members
        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                GC.SuppressFinalize(this);
                m_handle.Dispose();
            }
        }
        public void Dispose()
        {
            Dispose(true);
        }
        ~View()
        {
            Dispose(false);
        }
        #endregion
    }

    public class SummaryInformation : IDisposable
    {
        public enum Properties
        {
            CodePage    = 1,
            Title       = 2,
            Subject     = 3,
            Author      = 4,
            Keywords    = 5,
            Comments    = 6,
            Template    = 7,
            LastAuthor  = 8,
            Revision    = 9,
            Printed     = 11,
            Created     = 12,
            Saved       = 13,
            Pages       = 14,
            Words       = 15,
            Characters  = 16,
            Application = 18,
            Security    = 19
        }

        #region Construction/Destruction
        public SummaryInformation(Database db, int count)
        {
            IntPtr handle;
            TR(MsiGetSummaryInformation(db.Handle, null, count, out handle));
            m_handle = new MSIHandle(handle);
        }
        public SummaryInformation(string path, int count)
        {
            IntPtr handle;
            TR(MsiGetSummaryInformation(IntPtr.Zero, path, count, out handle));
            m_handle = new MSIHandle(handle);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetSummaryInformation(IntPtr database,
            string path, int count, out IntPtr handle);
        #endregion

        #region Methods
        public void Persist()
        {
            TR(MsiSummaryInfoPersist(m_handle.Handle));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSummaryInfoPersist(IntPtr handle);
        #endregion

        #region GetProperty
        public string GetProperty(Properties which)
        {
            int integerData;
            FILETIME dateTimeData;
            VarEnum dataType;
            int stringDataLength = 0;
            TR(MsiSummaryInfoGetProperty(m_handle.Handle, (int) which,
                out dataType, out integerData, out dateTimeData, null,
                ref stringDataLength));
            StringBuilder stringData = new StringBuilder(stringDataLength+1);
            stringDataLength = stringData.Capacity;
            TR(MsiSummaryInfoGetProperty(m_handle.Handle, (int) which,
                out dataType, out integerData, out dateTimeData, stringData,
                ref stringDataLength));

            return stringData.ToString();
        }

        public int GetIntegerProperty(Properties which)
        {
            int integerData;
            FILETIME dateTimeData;
            int stringDataLength = 0;
            VarEnum dataType;
            TR(MsiSummaryInfoGetProperty(m_handle.Handle, (int) which,
                out dataType, out integerData, out dateTimeData, null,
                ref stringDataLength));
            return integerData;
        }

        public DateTime GetDateTimeProperty(Properties which)
        {
            int integerData;
            FILETIME dateTimeData;
            int stringDataLength = 0;
            VarEnum dataType;
            TR(MsiSummaryInfoGetProperty(m_handle.Handle, (int) which,
                out dataType, out integerData, out dateTimeData, null,
                ref stringDataLength));
            return ToDateTime(dateTimeData);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSummaryInfoGetProperty(
            IntPtr handle, int which, out VarEnum dataType,
            out int integerData, out FILETIME dateTimeData,
            StringBuilder stringData, ref int stringDataLength);
        #endregion

        #region SetProperty
        public void SetProperty(Properties which, string data)
        {
            TR(MsiSummaryInfoSetProperty(m_handle.Handle, (int) which,
                (int) VarEnum.VT_LPSTR, 0, IntPtr.Zero, data));
        }

        public void SetIntegerProperty(Properties which, int data)
        {
            TR(MsiSummaryInfoSetProperty(m_handle.Handle, (int) which,
                (int) VarEnum.VT_I4, data, IntPtr.Zero, null));
        }

        public void SetDateTimeProperty(Properties which, DateTime data)
        {
            FILETIME ft = FromDateTime(data);
            TR(MsiSummaryInfoSetProperty(m_handle.Handle, (int) which,
                (int) VarEnum.VT_FILETIME, 0, ref ft, null));
        }

        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSummaryInfoSetProperty(
            IntPtr handle, int propertyId, int dataType,
            int integerData, IntPtr dateTimeData, string stringData);
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSummaryInfoSetProperty(
            IntPtr handle, int propertyId, int dataType,
            int integerData, ref FILETIME dateTimeData, string stringData);
        #endregion

        private static FILETIME FromDateTime(DateTime time)
        {
            FILETIME val = new FILETIME();
            long ticks = time.ToFileTime();
            val.dwLowDateTime = (int) (ticks & 0xFFFFFFFFL);
            val.dwHighDateTime = (int) (ticks >> 32);
            return val;
        }
        private static DateTime ToDateTime(FILETIME time)
        {
            return new DateTime(
                (((long) time.dwHighDateTime) << 32) + time.dwLowDateTime);
        }

        #region Synthesized Properties
        #region PropertyCount
        public int PropertyCount
        {
            get
            {
                int count;
                TR(MsiSummaryInfoGetPropertyCount(m_handle.Handle, out count));
                return count;
            }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSummaryInfoGetPropertyCount(IntPtr handle,
            out int count);
        #endregion

        public int CodePage
        {
            get { return GetIntegerProperty(Properties.CodePage); }
            set { SetIntegerProperty(Properties.CodePage, value); }
        }
        public string Title
        {
            get { return GetProperty(Properties.Title); }
            set { SetProperty(Properties.Title, value); }
        }
        public string Subject
        {
            get { return GetProperty(Properties.Subject); }
            set { SetProperty(Properties.Subject, value); }
        }
        public string Author
        {
            get { return GetProperty(Properties.Author); }
            set { SetProperty(Properties.Author, value); }
        }
        public string Keywords
        {
            get { return GetProperty(Properties.Keywords); }
            set { SetProperty(Properties.Keywords, value); }
        }
        public string Comments
        {
            get { return GetProperty(Properties.Comments); }
            set { SetProperty(Properties.Comments, value); }
        }
        public string Template
        {
            get { return GetProperty(Properties.Template); }
            set { SetProperty(Properties.Template, value); }
        }
        public string LastAuthor
        {
            get { return GetProperty(Properties.LastAuthor); }
            set { SetProperty(Properties.LastAuthor, value); }
        }
        public string Revision
        {
            get { return GetProperty(Properties.Revision); }
            set { SetProperty(Properties.Revision, value); }
        }
        public DateTime Printed
        {
            get { return GetDateTimeProperty(Properties.Printed); }
            set { SetDateTimeProperty(Properties.Printed, value); }
        }
        public DateTime Created
        {
            get { return GetDateTimeProperty(Properties.Created); }
            set { SetDateTimeProperty(Properties.Created, value); }
        }
        public DateTime Saved
        {
            get { return GetDateTimeProperty(Properties.Saved); }
            set { SetDateTimeProperty(Properties.Saved, value); }
        }
        public int Pages
        {
            get { return GetIntegerProperty(Properties.Pages); }
            set { SetIntegerProperty(Properties.Pages, value); }
        }
        public int Words
        {
            get { return GetIntegerProperty(Properties.Words); }
            set { SetIntegerProperty(Properties.Words, value); }
        }
        public int Characters
        {
            get { return GetIntegerProperty(Properties.Characters); }
            set { SetIntegerProperty(Properties.Characters, value); }
        }
        public string Application
        {
            get { return GetProperty(Properties.Application); }
            set { SetProperty(Properties.Application, value); }
        }
        public string Security
        {
            get { return GetProperty(Properties.Security); }
            set { SetProperty(Properties.Security, value); }
        }
        #endregion

        private static void TR(UInt32 result)
        {
            MSI.Installer.TR(result);
        }

        private MSIHandle m_handle;
        #region IDisposable Members
        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                GC.SuppressFinalize(this);
                m_handle.Dispose();
            }
        }
        public void Dispose()
        {
            Dispose(true);
        }
        ~SummaryInformation()
        {
            Dispose(false);
        }
        #endregion
    }

    public class UIPreview : IDisposable
    {
        public UIPreview(IntPtr handle)
        {
            m_handle = new MSIHandle(handle);
        }

        #region PreviewBillboard
        public void PreviewBillboard(string billboard, string control)
        {
            TR(MsiPreviewBillboard(m_handle.Handle, control, billboard));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private extern static UInt32 MsiPreviewBillboard(
            IntPtr preview, string control, string billboard);
        #endregion

        #region PreviewDialog
        public void PreviewDialog(string dialog)
        {
            TR(MsiPreviewDialog(m_handle.Handle, dialog));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private extern static UInt32 MsiPreviewDialog(
            IntPtr preview, string dialog);
        #endregion

        #region IDisposable Members
        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                GC.SuppressFinalize(this);
                m_handle.Dispose();
            }
        }
        public void Dispose()
        {
            Dispose(true);
        }
        ~UIPreview()
        {
            Dispose(false);
        }
        #endregion

        private static void TR(UInt32 result)
        {
            MSI.Installer.TR(result);
        }

        MSIHandle m_handle;
    }
}
