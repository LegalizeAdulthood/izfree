using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
    public struct FileHash
    {
        public UInt32[] Data;
    }

	/// <summary>
	/// Summary description for Installer.
	/// </summary>
    public class Installer
    {
        [StructLayout(LayoutKind.Sequential)]
        private struct MSIFILEHASHINFO
        {
            public UInt32 dwFileHashInfoSize;
            public UInt32 dwData1;
            public UInt32 dwData2;
            public UInt32 dwData3;
            public UInt32 dwData4;
        }

        public const int MaxFeatureLength = 38;
        public const int MaxGuidLength = 38;
        public const int MaxPathLength = 1024;

        private Installer()
        {}

        public const string MSI_DLL = @"msi.dll";

        #region LastErrorRecord
        public static Record LastErrorRecord
        {
            get
            {
                return new Record(MsiGetLastErrorRecord());
            }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern IntPtr MsiGetLastErrorRecord();
        #endregion

        #region AdvertiseScript
        public static void AdvertiseScript(string scriptPath,
            MSI.ScriptFlags flags, Microsoft.Win32.RegistryKey data,
            bool removeItems)
        {
            int key = 0;
            TR(MsiAdvertiseScript(scriptPath, (int) flags, (IntPtr) key, removeItems ? 1 : 0));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiAdvertiseScript(string scriptPath,
            int flags, IntPtr key, int removeItems);
        #endregion

        #region ApplyPatch
        public static void ApplyPatch(string patchPackage,
            string installPackage, MSI.InstallType which, string commandLine)
        {
            TR(MsiApplyPatch(patchPackage, installPackage, (int) which,
                commandLine));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiApplyPatch(string patchPackage,
            string installPackage, int installType, string commandLine);
        #endregion

        #region CollectUserInformation
        public static void CollectUserInformation(string product)
        {
            TR(MsiCollectUserInfo(product));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiCollectUserInfo(string product);
        #endregion

        #region ConfigureFeature
        public static void ConfigureFeature(string product, string feature,
            MSI.InstallState state)
        {
            TR(MsiConfigureFeature(product, feature, (int) state));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiConfigureFeature(string product,
            string feature, int state);
        #endregion

        #region ConfigureProduct
        public static void ConfigureProduct(string product, int installLevel,
            MSI.InstallState state)
        {
            TR(MsiConfigureProduct(product, installLevel, (int) state));
        }
        public static void ConfigureProduct(string product, int installLevel,
            MSI.InstallState state, string commandLine)
        {
            TR(MsiConfigureProductEx(product, installLevel, (int) state,
                commandLine));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiConfigureProduct(string product,
            int installLevel, int state);
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiConfigureProductEx(string product,
            int installLevel, int state, string commandLine);
        #endregion

        #region EnableLog
        public static void EnableLog(MSI.InstallLogMode mode, string logFile,
            MSI.InstallLogAttributes attributes)
        {
            TR(MsiEnableLog((int) mode, logFile, (int) attributes));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnableLog(int logMode, string logFile,
            int attributes);
        #endregion

        #region EnumComponents
        public static string EnumComponents(int index)
        {
            string component;
            TR(MsiEnumComponents(index, out component));
            return component;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnumComponents(int index,
            out string component);
        #endregion

        #region EnumProducts
        public static string EnumProducts(int index)
        {
            string product;
            TR(MsiEnumProducts(index, out product));
            return product;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnumProducts(int index,
            out string product);
        #endregion

        #region EnumRelatedProduct
        public static string EnumRelatedProducts(string upgradeCode,
            int index)
        {
            string product;
            TR(MsiEnumRelatedProduct(upgradeCode, 0, index, out product));
            return product;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnumRelatedProduct(string upgradeCode,
            int reserved, int index, out string product);
        #endregion

        #region GetComponentPath
        public static string GetComponentPath(string product, string component)
        {
            int pathLength = Installer.MaxPathLength;
            StringBuilder path = new StringBuilder(pathLength);
            TR(MsiGetComponentPath(product, component, path, ref pathLength));
            return path.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetComponentPath(string product,
            string component, StringBuilder path, ref int pathLength);
        #endregion

        #region GetFeatureUsage
        public static int GetFeatureUsage(string product, string feature)
        {
            DateTime dateUsed;
            return GetFeatureUsage(product, feature, out dateUsed);
        }
        public static int GetFeatureUsage(string product, string feature,
            out DateTime dateUsed)
        {
            UInt16 date = 0;
            UInt32 count = 0;
            TR(MsiGetFeatureUsage(product, feature, out count, out date));
            dateUsed = new DateTime(1980 + ((date >> 9) & 0x7F),
                (date >> 5) & 0xF, date & 0x1F);
            return (int) count;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFeatureUsage(string product,
            string feature, out UInt32 usageCount, out UInt16 dateUsed);
        #endregion

        #region GetFileHash
        public static FileHash GetFileHash(string path)
        {
            MSIFILEHASHINFO hash = new MSIFILEHASHINFO();
            hash.dwFileHashInfoSize =
                (UInt32) Marshal.SizeOf(typeof(MSIFILEHASHINFO));
            TR(MsiGetFileHash(path, 0, ref hash));
            FileHash result = new FileHash();
            result.Data = new UInt32[4]
                { hash.dwData1, hash.dwData2, hash.dwData3, hash.dwData4 };
            return result;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFileHash(string path,
            int options, ref MSIFILEHASHINFO hash);
        #endregion

        #region GetFileSignatureInformation
#if false
        public static void GetFileSignatureInformation(
            string signedObjectPath, int flags, IntPtr certificateContext,
            out byte[] hash)
        {
            IntPtr hashData;
            IntPtr hashLength;
            TR(MsiGetFileSignatureInformation(signedObjectPath, flags,
                certificateContext, hashData, hashLength));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFileSignatureInformation(
            string signedObjectPath, UInt32 flags,
            out CCERT_CONTEXT certificateContext,
            IntPtr hash, IntPtr hashLength);
#endif
        #endregion

        #region GetFileVersion
        public static string GetFileVersion(string filePath)
        {
            int versionLength = "65535.65535.65535.65535".Length+1;
            StringBuilder version = new StringBuilder(versionLength);
            int languageLength = 0;
            TR(MsiGetFileVersion(filePath, version, ref versionLength,
                null, ref languageLength));
            return version.ToString();
        }
        public static string GetFileLanguage(string filePath)
        {
            int languageLength = Installer.MaxPathLength;
            StringBuilder language = new StringBuilder(languageLength);
            int versionLength = 0;
            TR(MsiGetFileVersion(filePath, null, ref versionLength,
                language, ref languageLength));
            return language.ToString();
        }
        public static string GetFileVersion(string filePath,
            out string fileLanguage)
        {
            int versionLength = "65535.65535.65535.65535".Length+1;
            StringBuilder version = new StringBuilder(versionLength);
            int languageLength = Installer.MaxPathLength;
            StringBuilder language = new StringBuilder(languageLength);
            TR(MsiGetFileVersion(filePath, version, ref versionLength,
                language, ref languageLength));
            fileLanguage = language.ToString();
            return version.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFileVersion(string filePath,
            StringBuilder version, ref int versionLength,
            StringBuilder language, ref int languageLength);
        #endregion

        #region GetPatchInfo
        public static string GetPatchInfo(string patch, string attribute)
        {
            int length = Installer.MaxPathLength;
            StringBuilder data = new StringBuilder(length);
            TR(MsiGetPatchInfo(patch, attribute, data, ref length));
            return data.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetPatchInfo(string patch,
            string attribute, StringBuilder val, ref int valueLength);
        #endregion

        #region GetProductInfo
        public static string GetProductInfo(string product, string property)
        {
            int dataLength = Installer.MaxGuidLength+1;
            StringBuilder data = new StringBuilder(dataLength);
            TR(MsiGetProductInfo(product, property, data, ref dataLength));
            return data.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetProductInfo(string product,
            string property, StringBuilder data, ref int dataLength);
        #endregion

        #region GetProductInfoFromScript
        public static void GetProductInfoFromScript(string scriptFile,
            out Guid productCodeResult, out int languageResult,
            out int versionResult, out string nameResult,
            out string packageResult)
        {
            StringBuilder productCode =
                new StringBuilder(Installer.MaxGuidLength+1);
            int language = 0;
            UInt32 version = 0;
            int nameLength = Installer.MaxPathLength;
            StringBuilder name = new StringBuilder(nameLength);
            int packageLength = Installer.MaxPathLength;
            StringBuilder package = new StringBuilder(packageLength);
            TR(MsiGetProductInfoFromScript(scriptFile, productCode,
                out language, out version,
                name, ref nameLength, package, ref packageLength));

            productCodeResult = new Guid(productCode.ToString());
            languageResult = language;
            versionResult = (int) version;
            nameResult = name.ToString();
            packageResult = package.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetProductInfoFromScript(
            string scriptFile, StringBuilder productCode,
            out int language, out UInt32 version,
            StringBuilder name, ref int nameLength,
            StringBuilder package, ref int packageLength);
        #endregion

        #region GetProductProperty
        public static string GetProductProperty(IntPtr product, string property)
        {
            int dataLength = Installer.MaxPathLength;
            StringBuilder data = new StringBuilder(dataLength);
            TR(MsiGetProductProperty(product, property, data, ref dataLength));
            return data.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetProductProperty(IntPtr product,
            string property, StringBuilder val, ref int valueLength);
        #endregion

        #region GetShortcutTarget
        public static void GetShortcutTarget(string shortcutTarget,
            out Guid productCode, out string featureId, out Guid componentCode)
        {
            StringBuilder product =
                new StringBuilder(Installer.MaxGuidLength+1);
            StringBuilder feature =
                new StringBuilder(Installer.MaxFeatureLength+1);
            StringBuilder component =
                new StringBuilder(Installer.MaxGuidLength+1);
            TR(MsiGetShortcutTarget(shortcutTarget, product,
                feature, component));
            productCode = new Guid(product.ToString());
            featureId = feature.ToString();
            componentCode = new Guid(component.ToString());
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetShortcutTarget(
            string shortcutTarget, StringBuilder productCode,
            StringBuilder featureID, StringBuilder componentCode);
        #endregion

        #region GetUserInfo
        public static void GetUserInfo(string product,
            out string userNameResult, out string organizationNameResult,
            out string serialNumberResult)
        {
            int userNameLength = Installer.MaxPathLength;
            StringBuilder userName = new StringBuilder(userNameLength);
            int orgLength = Installer.MaxPathLength;
            StringBuilder organization = new StringBuilder(orgLength);
            int serialLength = Installer.MaxPathLength;
            StringBuilder serialNumber = new StringBuilder(serialLength);
            TR(MsiGetUserInfo(product, userName, ref userNameLength,
                organization, ref orgLength, serialNumber, ref serialLength));
            userNameResult = userName.ToString();
            organizationNameResult = organization.ToString();
            serialNumberResult = serialNumber.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetUserInfo(string product,
            StringBuilder userName, ref int userNameLength,
            StringBuilder organizationName, ref int organizationNameLength,
            StringBuilder serialNumber, ref int serialNumberLength);
        #endregion

        #region InstallMissingComponent
        public static void InstallMissingComponent(string product,
            string component, int installState)
        {
            TR(MsiInstallMissingComponent(product, component, installState));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiInstallMissingComponent(string product,
            string component, int installState);
        #endregion

        #region InstallMissingFile
        public static void InstallMissingFile(string product, string file)
        {
            TR(MsiInstallMissingFile(product, file));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiInstallMissingFile(string product,
            string file);
        #endregion

        #region InstallProduct
        public static void InstallProduct(string product, string commandLine)
        {
            TR(MsiInstallProduct(product, commandLine));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiInstallProduct(string product,
            string commandLine);
        #endregion

        #region IsProductElevated
        public static bool IsProductElevated(string product)
        {
            int elevated;
            TR(MsiIsProductElevated(product, out elevated));
            return elevated != 0;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiIsProductElevated(string product,
            out int elevated);
        #endregion

        #region OpenPackage
        public static Database OpenPackage(string package)
        {
            IntPtr product;
            TR(MsiOpenPackage(package, out product));
            return new Database(product);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiOpenPackage(string package,
            out IntPtr product);

        public static Database OpenPackage(string package, int options)
        {
            IntPtr product;
            TR(MsiOpenPackageEx(package, options, out product));
            return new Database(product);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiOpenPackageEx(string package,
            int options, out IntPtr product);
        #endregion

        #region OpenProduct
        public static Database OpenProduct(string product)
        {
            IntPtr handle;
            TR(MsiOpenProduct(product, out handle));
            return new MSI.Database(handle);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiOpenProduct(string product,
            out IntPtr handle);
        #endregion

        #region ProcessAdvertiseScript
        public static void ProcessAdvertiseScript(
            string scriptFile, string iconFolder, IntPtr key,
            int shortcuts, int removeItems)
        {
            TR(MsiProcessAdvertiseScript(scriptFile, iconFolder, key,
                shortcuts, removeItems));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiProcessAdvertiseScript(
            string scriptFile, string iconFolder, IntPtr key,
            int shortcuts, int removeItems);
        #endregion

        public enum AssemblyInfo
        {
            NetAssembly = 0,
            Win32Assembly = 1
        }

        #region ProvideAssembly
        public static string ProvideAssembly(string assemblyName,
            string appContext, InstallMode installMode, AssemblyInfo info)
        {
            int pathLength = Installer.MaxPathLength;
            StringBuilder path = new StringBuilder(pathLength);
            TR(MsiProvideAssembly(assemblyName, appContext,
                (UInt32) installMode, (UInt32) info,
                path, ref pathLength));
            return path.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiProvideAssembly(string assemblyName,
            string appContext, UInt32 installMode, UInt32 assemblyInfo,
            StringBuilder path, ref int pathLength);
        #endregion

        #region ProvideComponent
        public static string ProvideComponent(string product, string feature,
            string component, InstallMode installMode)
        {
            int pathLength = Installer.MaxPathLength;
            StringBuilder path = new StringBuilder(pathLength);
            TR(MsiProvideComponent(product, feature, component,
                (UInt32) installMode, path, ref pathLength));
            return path.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiProvideComponent(string product,
            string feature, string component, UInt32 installMode, 
            StringBuilder path, ref int pathLength);
        #endregion

        #region QueryFeatureState
        public static MSI.InstallState QueryFeatureState(string product,
            string feature)
        {
            return (MSI.InstallState) MsiQueryFeatureState(product, feature);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiQueryFeatureState(string product,
            string feature);
        #endregion

        #region QueryProductState
        public static MSI.InstallState QueryProductState(string product)
        {
            return (MSI.InstallState) MsiQueryProductState(product);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiQueryProductState(string product);
        #endregion

        #region ReinstallFeature
        public static void ReinstallFeature(string product, string feature,
            int reinstallMode)
        {
            TR(MsiReinstallFeature(product, feature, reinstallMode));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiReinstallFeature(string product,
            string feature, int reinstallMode);
        #endregion

        #region ReinstallProduct
        public static void ReinstallProduct(string product, int reinstallMode)
        {
            TR(MsiReinstallProduct(product, reinstallMode));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiReinstallProduct(string product,
            int reinstallMode);
        #endregion

        public enum ControlIds
        {
            IDOK = 1,
            IDCANCEL = 2,
            IDABORT = 3,
            IDRETRY = 4,
            IDIGNORE = 5,
            IDYES = 6,
            IDNO = 7,
            IDCLOSE = 8,
            IDHELP = 9,
            IDTRYAGAIN = 10,
            IDCONTINUE = 11
        }

        #region SetExternalUI
        // need a delegate to handle function pointer here
        public delegate int UIHandlerDelegate(IntPtr context, 
            int messageType, string message);
        public static void SetExternalUI(UIHandlerDelegate handler,
            int messageFilter, IntPtr context)
        {
            TR(MsiSetExternalUI(handler, messageFilter, context));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSetExternalUI(UIHandlerDelegate handler,
            int messageFilter, IntPtr context);
        #endregion

        #region SetInternalUI
        public static void SetInternalUI(int uiLevel, IntPtr window)
        {
            TR(MsiSetInternalUI(uiLevel, window));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSetInternalUI(int uiLevel,
            IntPtr window);
        #endregion

        #region SourceListAddSource
        public static void SourceListAddSource(string product,
            string userName, string source)
        {
            TR(MsiSourceListAddSource(product, userName, 0, source));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSourceListAddSource(string product,
            string userName, int reserved, string source);
        #endregion

        #region SourceListClearAll
        public static void SourceListClearAll(string product, string userName)
        {
            TR(MsiSourceListClearAll(product, userName, 0));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSourceListClearAll(string product,
            string userName, int reserved);
        #endregion

        #region SourceListForceResolution
        public static void SourceListForceResolution(string product,
            string userName)
        {
            TR(MsiSourceListForceResolution(product, userName, 0));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSourceListForceResolution(
            string product, string userName, int reserved);
        #endregion

        #region UseFeature
        public static void UseFeature(string product, string feature)
        {
            TR(MsiUseFeature(product, feature));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiUseFeature(string product,
            string feature);

        public static void UseFeature(string product, string feature,
            int installMode)
        {
            TR(MsiUseFeatureEx(product, feature, installMode, 0));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiUseFeatureEx(string product,
            string feature, int installMode, int reserved);
        #endregion

        #region VerifyPackage
        public static void VerifyPackage(string package)
        {
            TR(MsiVerifyPackage(package));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiVerifyPackage(string package);
        #endregion

        public static string FormatRecord(Record record)
        {
            int size = Installer.MaxPathLength;
            StringBuilder text = new StringBuilder(size);
            TR(MsiFormatRecord(IntPtr.Zero, record.Handle, text, ref size));
            return text.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiFormatRecord(IntPtr session,
            IntPtr record, StringBuilder text, ref int size);

        private static string ErrorText(Database db, Record error)
        {
            string format = "";
            if (null != db)
            {
                using (View view = db.OpenView("SELECT `Message` FROM `Error` " +
                           "WHERE `Error`=" + error.GetString(1)))
                {
                    view.Execute();
                    using (Record rec = view.Fetch())
                    {
                        if (null != rec)
                        {
                            format = rec.GetString(1);
                        }
                    }
                }
            }
            if ("" == format)
            {
                format = "1: [1]";
                for (int i = 2; i <= error.FieldCount; i++)
                {
                    format += String.Format("{{, {0}: [{0}]}}", i);
                }
            }
            error.SetString(0, format);
            return FormatRecord(error);
        }

        public static void TR(Database db, UInt32 result)
        {
            if (result != 0)
            {
                Record error = LastErrorRecord;
                if ((error != null) && (error.FieldCount > 0))
                {
                    System.Diagnostics.Debug.WriteLine(
                        String.Format("Windows Installer Error {0}:\n{1}",
                        error.GetInteger(1), ErrorText(db, error)));
                    System.Diagnostics.Debug.WriteLine(
                        (new System.Diagnostics.StackTrace()).ToString());
                }
                throw new Win32Exception((int) result);
            }
        }

        public static void TR(UInt32 result)
        {
            TR(null, result);
        }
    }
}
