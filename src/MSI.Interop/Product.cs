using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
	/// <summary>
	/// Summary description for Product.
	/// </summary>
	public class Product
	{
        public Product(string productCode)
		{
            Guid guid = new Guid(productCode);
            m_code = productCode;
        }

        public Guid Code
        {
            get { return new Guid(m_code); }
        }

        #region CollectUserInformation
        public  void CollectUserInformation()
        {
            TR(MsiCollectUserInfo(m_code));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiCollectUserInfo(string product);
        #endregion

        #region ConfigureFeature
        public  void ConfigureFeature(string feature, MSI.InstallState state)
        {
            TR(MsiConfigureFeature(m_code, feature, (int) state));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiConfigureFeature(string product,
            string feature, int state);
        #endregion

        #region Configure
        public void Configure(int installLevel, MSI.InstallState state)
        {
            TR(MsiConfigureProduct(m_code, installLevel, (int) state));
        }
        public void Configure(int installLevel, MSI.InstallState state,
            string commandLine)
        {
            TR(MsiConfigureProductEx(m_code, installLevel, (int) state,
                commandLine));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiConfigureProduct(string product,
            int installLevel, int state);
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiConfigureProductEx(string product,
            int installLevel, int state, string commandLine);
        #endregion

        #region EnumFeatures
        public string EnumFeatures(int index)
        {
            string parent;
            return EnumFeatures(index, out parent);
        }
        public string EnumFeatures(int index, out string parentFeature)
        {
            StringBuilder parent =
                new StringBuilder(Installer.MaxFeatureLength+1);
            StringBuilder feature =
                new StringBuilder(Installer.MaxFeatureLength+1);
            TR(MsiEnumFeatures(m_code, index, feature, parent));
            parentFeature = parent.ToString();
            return feature.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnumFeatures(string product,
            int index, StringBuilder feature, StringBuilder parent);
        #endregion

        #region EnumPatches
        public string EnumPatches(int index, out Guid patch)
        {
            StringBuilder patchGuid =
                new StringBuilder(Installer.MaxGuidLength+1);
            int transformLength = Installer.MaxPathLength;
            StringBuilder transforms = new StringBuilder(transformLength);
            TR(MsiEnumPatches(m_code, index, patchGuid,
                transforms, ref transformLength));
            patch = new Guid(patchGuid.ToString());
            return transforms.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnumPatches(string product,
            int index, StringBuilder patch, StringBuilder transforms,
            ref int transformsLength);
        #endregion

        #region GetComponentPath
        public string GetComponentPath(string component)
        {
            int pathLength = Installer.MaxPathLength;
            StringBuilder path = new StringBuilder(pathLength);
            TR(MsiGetComponentPath(m_code, component, path, ref pathLength));
            return path.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetComponentPath(string product,
            string component, StringBuilder path, ref int pathLength);
        #endregion

        #region GetFeatureUsage
        public int GetFeatureUsage(string feature)
        {
            DateTime dateUsed;
            return GetFeatureUsage(feature, out dateUsed);
        }
        public int GetFeatureUsage(string feature, out DateTime dateUsed)
        {
            UInt16 date = 0;
            UInt32 count = 0;
            TR(MsiGetFeatureUsage(m_code, feature, out count, out date));
            dateUsed = new DateTime(1980 + ((date >> 9) & 0x7F),
                (date >> 5) & 0xF, date & 0x1F);
            return (int) count;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFeatureUsage(string product,
            string feature, out UInt32 usageCount, out UInt16 dateUsed);
        #endregion

        #region GetInfo
        public string GetInfo(string property)
        {
            int dataLength = Installer.MaxGuidLength+1;
            StringBuilder data = new StringBuilder(dataLength);
            TR(MsiGetProductInfo(m_code, property, data, ref dataLength));
            return data.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetProductInfo(string product,
            string property, StringBuilder data, ref int dataLength);
        #endregion

        #region GetUserInfo
        public void GetUserInfo(
            out string userNameResult, out string organizationNameResult,
            out string serialNumberResult)
        {
            int userNameLength = Installer.MaxPathLength;
            StringBuilder userName = new StringBuilder(userNameLength);
            int orgLength = Installer.MaxPathLength;
            StringBuilder organization = new StringBuilder(orgLength);
            int serialLength = Installer.MaxPathLength;
            StringBuilder serialNumber = new StringBuilder(serialLength);
            TR(MsiGetUserInfo(m_code, userName, ref userNameLength,
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
        public void InstallMissingComponent(string component, int installState)
        {
            TR(MsiInstallMissingComponent(m_code, component, installState));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiInstallMissingComponent(string product,
            string component, int installState);
        #endregion

        #region InstallMissingFile
        public void InstallMissingFile(string file)
        {
            TR(MsiInstallMissingFile(m_code, file));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiInstallMissingFile(string product,
            string file);
        #endregion

        #region Install
        public void Install(string commandLine)
        {
            TR(MsiInstallProduct(m_code, commandLine));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiInstallProduct(string product,
            string commandLine);
        #endregion

        #region Elevated
        public bool Elevated
        {
            get
            {
                int elevated;
                TR(MsiIsProductElevated(m_code, out elevated));
                return elevated != 0;
            }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiIsProductElevated(string product,
            out int elevated);
        #endregion

        #region Open
        public Database Open()
        {
            IntPtr handle;
            TR(MsiOpenProduct(m_code, out handle));
            return new MSI.Database(handle);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiOpenProduct(string product,
            out IntPtr handle);
        #endregion

        #region ProvideComponent
        public string ProvideComponent(string feature,
            string component, InstallMode installMode)
        {
            int pathLength = Installer.MaxPathLength;
            StringBuilder path = new StringBuilder(pathLength);
            TR(MsiProvideComponent(m_code, feature, component,
                (UInt32) installMode, path, ref pathLength));
            return path.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiProvideComponent(string product,
            string feature, string component, UInt32 installMode, 
            StringBuilder path, ref int pathLength);
        #endregion

        #region QueryFeatureState
        public MSI.InstallState QueryFeatureState(string product,
            string feature)
        {
            return (MSI.InstallState) MsiQueryFeatureState(m_code, feature);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiQueryFeatureState(string product,
            string feature);
        #endregion

        #region QueryState
        public MSI.InstallState InstallState
        {
            get
            {
                return (MSI.InstallState) MsiQueryProductState(m_code);
            }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiQueryProductState(string product);
        #endregion

        #region ReinstallFeature
        public void ReinstallFeature(string feature, int reinstallMode)
        {
            TR(MsiReinstallFeature(m_code, feature, reinstallMode));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiReinstallFeature(string product,
            string feature, int reinstallMode);
        #endregion

        #region Reinstall
        public void Reinstall(int reinstallMode)
        {
            TR(MsiReinstallProduct(m_code, reinstallMode));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiReinstallProduct(string product,
            int reinstallMode);
        #endregion

        #region SourceListAddSource
        public void SourceListAddSource(string userName, string source)
        {
            TR(MsiSourceListAddSource(m_code, userName, 0, source));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSourceListAddSource(string product,
            string userName, int reserved, string source);
        #endregion

        #region SourceListClearAll
        public void SourceListClearAll(string userName)
        {
            TR(MsiSourceListClearAll(m_code, userName, 0));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSourceListClearAll(string product,
            string userName, int reserved);
        #endregion

        #region SourceListForceResolution
        public void SourceListForceResolution(string userName)
        {
            TR(MsiSourceListForceResolution(m_code, userName, 0));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiSourceListForceResolution(
            string product, string userName, int reserved);
        #endregion

        #region UseFeature
        public void UseFeature(string feature)
        {
            TR(MsiUseFeature(m_code, feature));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiUseFeature(
            string product, string feature);

        public void UseFeature(string feature, int installMode)
        {
            TR(MsiUseFeatureEx(m_code, feature, installMode, 0));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiUseFeatureEx(string product,
            string feature, int installMode, int reserved);
        #endregion

        private static void TR(UInt32 result)
        {
            Installer.TR(result);
        }

        private string m_code;
    }
}
