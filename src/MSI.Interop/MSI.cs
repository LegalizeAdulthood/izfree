using System;
using System.Collections;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
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
                    TR(MsiCloseHandle(m_handle));
                }
                m_handle = IntPtr.Zero;
            }
            else
            {
            }
        }

        private void TR(UInt32 result)
        {
            if (result != 0)
            {
                throw new Win32Exception((int) result);
            }
        }

        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiCloseHandle(IntPtr handle);

        private IntPtr m_handle = IntPtr.Zero;
    }

#if true
    #region Enumerations
    [Flags]
    public enum AdvertiseFlags
    {
        MachineAssign = 0,
        UserAssign = 1
    }
    [Flags]
    public enum AdvertiseOptionFlags
    {
        None = 0,
        Instance = 1
    }
    [Flags]
    public enum ArchitectureFlags
    {
        Current = 0,
        X86 = 1,
        IA64 = 2,
        AMD64 = 4
    }
    public enum Condition
    {
        False               = 0,
        True                = 1,
        None                = 2,
        Error               = 3
    }
    public enum CostTree
    {
        SelfOnly            = 0,
        Children            = 1,
        Parents             = 2,
        Reserved            = 3
    }
    public enum DatabaseError
    {
        InvalidArg          = -3,
        MoreData            = -2,
        FunctionError       = -1,
        NoError             = 0,
        DuplicateKey        = 1,
        Required            = 2,
        BadLink             = 3,
        Overflow            = 4,
        Underflow           = 5,
        NotInset            = 6,
        BadVersion          = 7,
        BadCase             = 8,
        BadGuid             = 9,
        BadWildcard         = 10,
        BadIdentifier       = 11,
        BadLanguage         = 12,
        BadFilename         = 13,
        BadPath             = 14,
        BadCondition        = 15,
        BadFormatted        = 16,
        BadTemplate         = 17,
        BadDefaultDir       = 18,
        BadRegPath          = 19,
        BadCustomSource     = 20,
        BadProperty         = 21,
        MissingData         = 22,
        BadCategory         = 23,
        BadKeyTable         = 24,
        BadMaxMinValues     = 25,
        BadCabinet          = 26,
        BadShortcut         = 27,
        StringOverflow      = 28,
        BadLocalizeAttrib   = 29
    }
    public enum InstallFeatureAttribute
    {
        FavorLocal,
        FavorSource,
        FollowParent,
        FavorAdvertise,
        DisallowAdvertise,
        NoUnsupportedAdvertise
    }
    public enum InstallLevel
    {
        Default             = 0,
        Minimum             = 1,
        Maximum             = 0xFFFF
    }
    [Flags]
    public enum InstallLogAttributes
    {
        Append,
        FlushEachLine
    }
    public enum InstallLogMode
    {
        FatalExit,
        Error,
        Warning,
        User,
        Info,
        ResolveSource,
        OutOfDiskSpace,
        ActionStart,
        ActionData,
        CommonData,
        PropertyDump,
        Verbose,
        ExtraDebug,
        Progress,
        Initialize,
        Terminate,
        ShowDialog
    }
    public enum InstallMessage
    {
        FatalExit           = 0x00000000,
        Error               = 0x10000000,
        Warning             = 0x20000000,
        User                = 0x30000000,
        Info                = 0x40000000,
        FilesInUse          = 0x50000000,
        ResolveSource       = 0x60000000,
        OutOfDiskSpace      = 0x70000000,
        ActionStart         = (0x8 << 28),
        ActionData          = (0x9 << 28),
        Progress            = (0xA << 28),
        CommonData          = (0xB << 28),
        Initialize          = (0xC << 28),
        Terminate           = (0xD << 28),
        ShowDialog          = (0xE << 28)
    }
    public enum InstallMode
    {
        NoSourceResolution,
        NoDetection,
        Existing,
        Default
    }
    public enum InstallState
    {
        NotUsed             = -7,
        BadConfig           = -6,
        Incomplete          = -5,
        SourceAbsent        = -4,
        MoreData            = -3,
        InvalidArg          = -2,
        Unknown             = -1,
        Broken              = 0,
        Advertised          = 1,
        Removed             = 1,
        Absent              = 2,
        Local               = 3,
        Source              = 4,
        Default             = 5
    }
    public enum InstallType
    {
        Default,
        NetworkImage,
        SingleInstance
    }
    public enum InstallUILevel
    {
        NoChange            = 0,
        Default             = 1,
        None                = 2,
        Basic               = 3,
        Reduced             = 4,
        Full                = 5,
        EndDialog           = 0x080,
        ProgressOnly        = 0x040,
        HideCancel          = 0x020,
        SourceResOnly       = 0x100
    }
    public enum Modify
    {
        Seek                = -1,
        Refresh             = 0,
        Insert              = 1,
        Update              = 2,
        Assign              = 3,
        Replace             = 4,
        Merge               = 5,
        Delete              = 6,
        InsertTemporary     = 7,
        Validate            = 8,
        ValidateNew         = 9,
        ValidateField       = 10,
        ValidateDelete      = 11
    }
    public enum OpenPackageFlags
    {
        IgnoreMachineState
    }
    [Flags]
    public enum ReinstallMode
    {
        Repair              = 0x001,
        FileMissing         = 0x002,
        FileOlderVersion    = 0x004,
        FileEqualVersion    = 0x008,
        FileExact           = 0x010,
        FileVerify          = 0x020,
        FileReplace         = 0x040,
        MachineData         = 0x080,
        UserData            = 0x100,
        Shortcut            = 0x200,
        Package             = 0x400
    }
    public enum RunMode
    {
        Admin               = 0,
        Advertise           = 1,
        Maintenance         = 2,
        RollbackEnabled     = 3,
        LogEnabled          = 4,
        Operations          = 5,
        RebootAtEnd         = 6,
        RebootNow           = 7,
        Cabinet             = 8,
        SourceShortNames    = 9,
        TargetShortNames    = 10,
        Reserved11          = 11,
        Windows9x           = 12,
        ZAWEnabled          = 13,
        Reserved14          = 14,
        Reserved15          = 15,
        Scheduled           = 16,
        Rollback            = 17,
        Commit              = 18
    }
    public enum ScriptFlags
    {
        CacheInfo,
        Shortcuts,
        MachineAssign,
        RegDataCnfgInfo,
        ValidateTransformsList,
        RegDataClassInfo,
        RegDataExtensionInfo,
        RegDataAppInfo,
        RegData
    }
    public enum TransformError
    {
        AddExistingRow      = 0x00000001,
        DelMissingRow       = 0x00000002,
        AddExistingTable    = 0x00000004,
        DelMissingTable     = 0x00000008,
        UpdateMissingRow    = 0x00000010,
        ChangeCodePage      = 0x00000020,
        ViewTransform       = 0x00000100,
    }
    public enum TransformValidate
    {
        Language                    = 0x00000001,
        Product                     = 0x00000002,
        Platform                    = 0x00000004,
        MajorVersion                = 0x00000008,
        MinorVersion                = 0x00000010,
        UpdateVersion               = 0x00000020,
        NewLessBaseVersion          = 0x00000040,
        NewLessEqualBaseVersion     = 0x00000080,
        NewEqualBaseVersion         = 0x00000100,
        NewGreaterEqualBaseVersion  = 0x00000200,
        NewGreaterBaseVersion       = 0x00000400,
        UpgradeCode                 = 0x00000800
    }
    public enum UserInfoState
    {
        MoreData            = -3,
        InvalidArg          = -2,
        Unknown             = -1,
        Absent              = 0,
        Present             = 1
    }
    #endregion

    public class Package
    {
        public Package(string path)
        {
            m_path = path;
        }

        #region Properties
        #region Features
        public string[] Features
        {
            get
            {
                if (m_features == null)
                {
                    ArrayList features = new ArrayList();
                    //MsiEnumFeatures
                    m_features = (string[]) features.ToArray(typeof(string));
                }
                return m_features;
            }
        }
        private string[] m_features = null;
        #endregion

        #region Patches
        public string[] Patches
        {
            get
            {
                if (m_patches == null)
                {
                    ArrayList patches = new ArrayList();
                    //MsiEnumPatches
                    m_patches = (string[]) patches.ToArray(typeof(string));
                }
                return m_patches;
            }
        }
        private string[] m_patches = null;
        #endregion

        #region Path
        public string Path
        {
            get { return m_path; }
            set { m_path = value; }
        }
        private string m_path = null;
        #endregion

        public string ComponentPath(string component)
        {
            //MsiGetComponentPath
            return null;
        }
        //MsiGetFeatureUsage
        //MsiGetProductCode
        //MsiGetProductInfo
        //MsiGetUserInfo
        //MsiIsProductElevated
        //MsiQueryFeatureState
        //MsiQueryProductState
        #endregion

        #region Methods
        public void Advertise(
            string scriptFilePath, string transforms, int language)
        {
            Installer.AdvertiseProduct(m_path, scriptFilePath, transforms,
                language);
        }
        public void Advertise(
            string scriptFilePath, string transforms, int language,
            ArchitectureFlags platform, AdvertiseOptionFlags options)
        {
            Installer.AdvertiseProduct(m_path, scriptFilePath, transforms,
                language, platform, options);
        }
        public void CollectUserInformation()
        {
            Installer.CollectUserInformation(m_path);
        }
        public void ConfigureFeature(
            string feature, MSI.InstallState state)
        {
            Installer.ConfigureFeature(m_path, feature, state);
        }
        public void ConfigureProduct(
            int installLevel, MSI.InstallState state)
        {
            Installer.ConfigureProduct(m_path, installLevel, state);
        }
        public void ConfigureProduct(
            int installLevel, MSI.InstallState state, string commandLine)
        {
            Installer.ConfigureProduct(m_path, installLevel, state, commandLine);
        }
        //MsiInstallMissingComponent
        //MsiInstallMissingFile
        //MsiInstallProduct
        //MsiOpenProduct
        //MsiProvideComponent
        //MsiReinstallFeature
        //MsiReinstallProduct
        //MsiSourceListAddSource
        //MsiSourceListClearAll
        //MsiSourceListForceResolution
        //MsiUseFeature
        //MsiUseFeatureEx
        //MsiVerifyPackage
        #endregion
    }

    class Session
    {
        private MSIHandle m_handle;

        public Session(IntPtr handle)
        {
            m_handle = new MSIHandle(handle);
        }

        private void TR(UInt32 result)
        {
            if (result != 0)
            {
                throw new Win32Exception((int) result);
            }
        }

        #region Handle
        public IntPtr Handle
        {
            get { return m_handle.Handle; }
        }
        #endregion

        #region DoAction
        public void DoAction(string action)
        {
            TR(MsiDoAction(m_handle.Handle, action));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDoAction(IntPtr session, string action);
        #endregion

        #region EnumComponentCosts
        public void EnumComponentCosts(string component, int index,
            InstallState installState,
            out string driveResult, out int cost, out int tempCost)
        {
            int driveLength = Installer.MaxPathLength;
            StringBuilder drive = new StringBuilder(driveLength);
            TR(MsiEnumComponentCosts(m_handle.Handle, component, index,
                (UInt32) installState, drive, ref driveLength,
                out cost, out tempCost));
            driveResult = drive.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnumComponentCosts(IntPtr session,
            string component, int index, UInt32 installState,
            StringBuilder drive, ref int driveLength,
            out int cost, out int tempCost);
        #endregion

        #region EvaluateCondition
        public MSI.Condition EvaluateCondition(string condition)
        {
            return (MSI.Condition)
                MsiEvaluateCondition(m_handle.Handle, condition);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEvaluateCondition(IntPtr session,
            string condition);
        #endregion

        #region FormatRecord
        public string FormatRecord(MSI.Record record)
        {
            int resultLength = Installer.MaxPathLength;
            StringBuilder result = new StringBuilder(resultLength);
            TR(MsiFormatRecord(m_handle.Handle, record.Handle,
                result, ref resultLength));
            return result.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiFormatRecord(IntPtr session,
            IntPtr record, StringBuilder result, ref int resultLength);
        #endregion

        #region ActiveDatabase
        Database ActiveDatabase
        {
            get
            {
                return new Database(MsiGetActiveDatabase(m_handle.Handle));
            }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern IntPtr MsiGetActiveDatabase(IntPtr session);
        #endregion

        #region ComponentState
        public MSI.InstallState ComponentState(string component,
            out InstallState installedReturn, out InstallState actionReturn)
        {
            UInt32 installed;
            UInt32 action;
            MSI.InstallState result = (MSI.InstallState)
                MsiGetComponentState(m_handle.Handle, component,
                    out installed, out action);
            installedReturn = (InstallState) installed;
            actionReturn = (InstallState) action;
            return result;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetComponentState(IntPtr session,
            string component, out UInt32 installed, out UInt32 action);
        #endregion

        #region FeatureCost
        public int FeatureCost(string feature, CostTree costTree,
            InstallState state)
        {
            int cost = 0;
            TR(MsiGetFeatureCost(m_handle.Handle, feature,
                (UInt32) costTree, (UInt32) state, out cost));
            return cost;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFeatureCost(IntPtr session,
            string feature, UInt32 costTree, UInt32 state, out int cost);
        #endregion

        #region FeatureState
        public MSI.InstallState FeatureState(string feature,
            out InstallState installedReturn, out InstallState actionReturn)
        {
            UInt32 installed;
            UInt32 action;
            MSI.InstallState result = (MSI.InstallState)
                MsiGetFeatureState(m_handle.Handle, feature,
                    out installed, out action);
            installedReturn = (InstallState) installed;
            actionReturn = (InstallState) action;
            return result;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFeatureState(IntPtr session,
            string feature, out UInt32 installed, out UInt32 action);
        #endregion

        #region GetFeatureValidStates
        public InstallState GetFeatureValidStates(string feature)
        {
            UInt32 states;
            TR(MsiGetFeatureValidStates(m_handle.Handle, feature, out states));
            return (InstallState) states;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFeatureValidStates(IntPtr session,
            string feature, out UInt32 installState);
        #endregion

        #region Language
        int Language
        {
            get { return (int) MsiGetLanguage(m_handle.Handle); }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetLanguage(IntPtr session);
        #endregion

        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetMode(IntPtr session, int runMode);

        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 Msi(IntPtr session);

    }


#else
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	public class MSI
	{
        #region Shortened WindowsInstaller constants
        public static Constants DatabaseNullInteger
        {
            get
            {
                return Constants.msiDatabaseNullInteger;
            }
        }
        public enum ColumnInfo
        {
            Names = MsiColumnInfo.msiColumnInfoNames,
            Types = MsiColumnInfo.msiColumnInfoTypes
        }
        public enum CostTree
        {
            Children = MsiCostTree.msiCostTreeChildren,
            Parents = MsiCostTree.msiCostTreeParents,
            SelfOnly = MsiCostTree.msiCostTreeSelfOnly
        }
        public enum DatabaseState
        {
            Read = MsiDatabaseState.msiDatabaseStateRead,
            Write = MsiDatabaseState.msiDatabaseStateWrite
        }
        public enum DoActionStatus
        {
            BadActionData = MsiDoActionStatus.msiDoActionStatusBadActionData,
            Failure = MsiDoActionStatus.msiDoActionStatusFailure,
            Finished = MsiDoActionStatus.msiDoActionStatusFinished,
            NoAction = MsiDoActionStatus.msiDoActionStatusNoAction,
            Success = MsiDoActionStatus.msiDoActionStatusSuccess,
            Suspend = MsiDoActionStatus.msiDoActionStatusSuspend,
            UserExt = MsiDoActionStatus.msiDoActionStatusUserExit,
            WrongState = MsiDoActionStatus.msiDoActionStatusWrongState
        }
        public enum EvaluateCondition
        {
            Error = MsiEvaluateCondition.msiEvaluateConditionError,
            False = MsiEvaluateCondition.msiEvaluateConditionFalse,
            None = MsiEvaluateCondition.msiEvaluateConditionNone,
            True = MsiEvaluateCondition.msiEvaluateConditionTrue
        }
        public enum InstallMode
        {
            Default = MsiInstallMode.msiInstallModeDefault,
            Existing = MsiInstallMode.msiInstallModeExisting,
            Detection = MsiInstallMode.msiInstallModeNoDetection,
            NoSourceResolution = MsiInstallMode.msiInstallModeNoSourceResolution
        }
        public enum InstallState
        {
            Absent = MsiInstallState.msiInstallStateAbsent,
            Advertised = MsiInstallState.msiInstallStateAdvertised,
            BadConfig = MsiInstallState.msiInstallStateBadConfig,
            Broken = MsiInstallState.msiInstallStateBroken,
            Default = MsiInstallState.msiInstallStateDefault,
            Incomplete = MsiInstallState.msiInstallStateIncomplete,
            InvalidArg = MsiInstallState.msiInstallStateInvalidArg,
            Local = MsiInstallState.msiInstallStateLocal,
            NotUsed = MsiInstallState.msiInstallStateNotUsed,
            Removed = MsiInstallState.msiInstallStateRemoved,
            Source = MsiInstallState.msiInstallStateSource,
            SourceAbsent = MsiInstallState.msiInstallStateSourceAbsent,
            Unknown = MsiInstallState.msiInstallStateUnknown
        }
        public enum InstallType
        {
            Default = MsiInstallType.msiInstallTypeDefault,
            NetworkImage = MsiInstallType.msiInstallTypeNetworkImage
        }
        public enum MessageStatus
        {
            Abort = MsiMessageStatus.msiMessageStatusAbort,
            Cancel = MsiMessageStatus.msiMessageStatusCancel,
            Error = MsiMessageStatus.msiMessageStatusError,
            Ignore = MsiMessageStatus.msiMessageStatusIgnore,
            No = MsiMessageStatus.msiMessageStatusNo,
            None = MsiMessageStatus.msiMessageStatusNone,
            Ok = MsiMessageStatus.msiMessageStatusOk,
            Retry = MsiMessageStatus.msiMessageStatusRetry,
            Yes = MsiMessageStatus.msiMessageStatusYes
        }
        public enum MessageType
        {
            AbortRetryIgnore = MsiMessageType.msiMessageTypeAbortRetryIgnore,
            ActionData = MsiMessageType.msiMessageTypeActionData,
            ActionStart = MsiMessageType.msiMessageTypeActionStart,
            CommonData = MsiMessageType.msiMessageTypeCommonData,
            Default1 = MsiMessageType.msiMessageTypeDefault1,
            Default2 = MsiMessageType.msiMessageTypeDefault2,
            Default3 = MsiMessageType.msiMessageTypeDefault3,
            Error = MsiMessageType.msiMessageTypeError,
            FatalExit = MsiMessageType.msiMessageTypeFatalExit,
            FilesInUse = MsiMessageType.msiMessageTypeFilesInUse,
            Info = MsiMessageType.msiMessageTypeInfo,
            Ok = MsiMessageType.msiMessageTypeOk,
            OkCancel = MsiMessageType.msiMessageTypeOkCancel,
            OutOfDiskSpace = MsiMessageType.msiMessageTypeOutOfDiskSpace,
            Progress = MsiMessageType.msiMessageTypeProgress,
            ResolveSource = MsiMessageType.msiMessageTypeResolveSource,
            RetryCancel = MsiMessageType.msiMessageTypeRetryCancel,
            User = MsiMessageType.msiMessageTypeUser,
            Warning = MsiMessageType.msiMessageTypeWarning,
            YesNo = MsiMessageType.msiMessageTypeYesNo,
            YesNoCancel = MsiMessageType.msiMessageTypeYesNoCancel
        }
        public enum OpenDatabaseMode
        {
            Create = MsiOpenDatabaseMode.msiOpenDatabaseModeCreate,
            CreateDirect = MsiOpenDatabaseMode.msiOpenDatabaseModeCreateDirect,
            Direct = MsiOpenDatabaseMode.msiOpenDatabaseModeDirect,
            PatchFile = MsiOpenDatabaseMode.msiOpenDatabaseModePatchFile,
            ReadOnly = MsiOpenDatabaseMode.msiOpenDatabaseModeReadOnly,
            Transact = MsiOpenDatabaseMode.msiOpenDatabaseModeTransact
        }
        public enum ReadStream
        {
            Ansi = MsiReadStream.msiReadStreamAnsi,
            Bytes = MsiReadStream.msiReadStreamBytes,
            Direct = MsiReadStream.msiReadStreamDirect,
            Integer = MsiReadStream.msiReadStreamInteger
        }
        public enum ReinstallMode
        {
            FileEqualVersion = MsiReinstallMode.msiReinstallModeFileEqualVersion,
            FileExact = MsiReinstallMode.msiReinstallModeFileExact,
            FileMissing = MsiReinstallMode.msiReinstallModeFileMissing,
            FileOlderVersion = MsiReinstallMode.msiReinstallModeFileOlderVersion,
            FileReplace = MsiReinstallMode.msiReinstallModeFileReplace,
            FileVerify = MsiReinstallMode.msiReinstallModeFileVerify,
            MachineData = MsiReinstallMode.msiReinstallModeMachineData,
            Package = MsiReinstallMode.msiReinstallModePackage,
            Shortcut = MsiReinstallMode.msiReinstallModeShortcut,
            UserData = MsiReinstallMode.msiReinstallModeUserData
        }
        public enum RunMode
        {
            Admin = MsiRunMode.msiRunModeAdmin,
            Advertise = MsiRunMode.msiRunModeAdvertise,
            Cabinet = MsiRunMode.msiRunModeCabinet,
            Commit = MsiRunMode.msiRunModeCommit,
            LogEnabled = MsiRunMode.msiRunModeLogEnabled,
            Maintenance = MsiRunMode.msiRunModeMaintenance,
            Operations = MsiRunMode.msiRunModeOperations,
            RebootAtEnd = MsiRunMode.msiRunModeRebootAtEnd,
            RebootNow = MsiRunMode.msiRunModeRebootNow,
            Rollback = MsiRunMode.msiRunModeRollback,
            RollbackEnabled = MsiRunMode.msiRunModeRollbackEnabled,
            Scheduled = MsiRunMode.msiRunModeScheduled,
            SourceShortNames = MsiRunMode.msiRunModeSourceShortNames,
            TargetShortNames = MsiRunMode.msiRunModeTargetShortNames,
            Windows9x = MsiRunMode.msiRunModeWindows9x,
            ZawEnabled = MsiRunMode.msiRunModeZawEnabled
        }
        public enum SignatureInfo
        {
            Certificate = MsiSignatureInfo.msiSignatureInfoCertificate,
            Hash = MsiSignatureInfo.msiSignatureInfoHash
        }
        public enum SignatureOption
        {
            InvalidHashFatal = MsiSignatureOption.msiSignatureOptionInvalidHashFatal
        }
        public enum TransformError
        {
            AddExistingRow = MsiTransformError.msiTransformErrorAddExistingRow,
            AddExistingTable = MsiTransformError.msiTransformErrorAddExistingTable,
            ChangeCodePage = MsiTransformError.msiTransformErrorChangeCodePage,
            DeleteNonExistingRow = MsiTransformError.msiTransformErrorDeleteNonExistingRow,
            DeleteNonExistingTable = MsiTransformError.msiTransformErrorDeleteNonExistingTable,
            None = MsiTransformError.msiTransformErrorNone,
            UpdateNonExistingRow = MsiTransformError.msiTransformErrorUpdateNonExistingRow,
            ViewTransform = MsiTransformError.msiTransformErrorViewTransform
        }
        public enum TransformValidation
        {
            Equal = MsiTransformValidation.msiTransformValidationEqual,
            Greater = MsiTransformValidation.msiTransformValidationGreater,
            GreaterOrEqual = MsiTransformValidation.msiTransformValidationGreaterOrEqual,
            Language = MsiTransformValidation.msiTransformValidationLanguage,
            Less = MsiTransformValidation.msiTransformValidationLess,
            LessOrEqual = MsiTransformValidation.msiTransformValidationLessOrEqual,
            MajorVer = MsiTransformValidation.msiTransformValidationMajorVer,
            MinorVer = MsiTransformValidation.msiTransformValidationMinorVer,
            None = MsiTransformValidation.msiTransformValidationNone,
            Platform = MsiTransformValidation.msiTransformValidationPlatform,
            Product = MsiTransformValidation.msiTransformValidationProduct,
            UpdateVer = MsiTransformValidation.msiTransformValidationUpdateVer,
            UpgradeCode = MsiTransformValidation.msiTransformValidationUpgradeCode
        }
        public enum UILevel
        {
            Basic = MsiUILevel.msiUILevelBasic,
            Default = MsiUILevel.msiUILevelDefault,
            EndDialog = MsiUILevel.msiUILevelEndDialog,
            Full = MsiUILevel.msiUILevelFull,
            HideCancel = MsiUILevel.msiUILevelHideCancel,
            NoChange = MsiUILevel.msiUILevelNoChange,
            None = MsiUILevel.msiUILevelNone,
            ProgressOnly = MsiUILevel.msiUILevelProgressOnly,
            Reduced = MsiUILevel.msiUILevelReduced
        }
        public enum ViewModify
        {
            Assign = MsiViewModify.msiViewModifyAssign,
            Delete = MsiViewModify.msiViewModifyDelete,
            Insert = MsiViewModify.msiViewModifyInsert,
            InsertTemporary = MsiViewModify.msiViewModifyInsertTemporary,
            Merge = MsiViewModify.msiViewModifyMerge,
            Refresh = MsiViewModify.msiViewModifyRefresh,
            Replace = MsiViewModify.msiViewModifyReplace,
            Seek = MsiViewModify.msiViewModifySeek,
            Update = MsiViewModify.msiViewModifyUpdate,
            Validate = MsiViewModify.msiViewModifyValidate,
            ValidateDelete = MsiViewModify.msiViewModifyValidateDelete,
            ValidateField = MsiViewModify.msiViewModifyValidateField,
            ValidateNew = MsiViewModify.msiViewModifyValidateNew
        }
        #endregion

        public enum SummaryInfoProperties
        {
            Dictionary   =  0,
            CodePage     =  1,
            Title        =  2,
            Subject      =  3,
            Author       =  4,
            Keywords     =  5,
            Comments     =  6,
            Template     =  7,
            LastAuthor   =  8,
            RevNumber    =  9,
            EditTime     = 10,
            LastPrinted  = 11,
            CreateDTM    = 12,
            LastSaveDTM  = 13,
            PageCount    = 14,
            WordCount    = 15,
            CharCount    = 16,
            ThumbNail    = 17,
            AppName      = 18,
            Security     = 19,
            MSIVersion   = PageCount,
            MSISource    = WordCount,
            MSIRestrict  = CharCount
        };

        public static Installer Installer
        {
            get
            {
                return (Installer) new MSIInstaller();
            }
        }

        [ComImport, Guid("000C1090-0000-0000-C000-000000000046")]
        private class MSIInstaller {}
    }
#endif
}
