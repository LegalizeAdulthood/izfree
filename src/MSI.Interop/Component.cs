using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
	/// <summary>
	/// Summary description for Component.
	/// </summary>
	public class Component
	{
		public Component(string componentCode)
		{
            Guid guid = new Guid(componentCode);
            m_code = componentCode;
		}

        public string Code
        {
            get { return m_code; }
        }

        #region EnumClients
        public Guid EnumClients(int index)
        {
            StringBuilder product = new StringBuilder(Installer.MaxGuidLength+1);
            TR(MsiEnumClients(m_code, index, product));
            return new Guid(product.ToString());
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnumClients(string component,
            int index, StringBuilder product);
        #endregion

        #region EnumQualifiers
        public void EnumQualifiers(int index,
            out string qualifier, out string applicationData)
        {
            int qualifiersLength = 0;
            int appDataLength = 0;
            TR(MsiEnumComponentQualifiers(m_code, index,
                null, ref qualifiersLength,
                null, ref appDataLength));

            StringBuilder qualifiers = new StringBuilder(qualifiersLength+1);
            StringBuilder appData  = new StringBuilder(appDataLength+1);
            TR(MsiEnumComponentQualifiers(m_code, index,
                qualifiers, ref qualifiersLength,
                appData, ref appDataLength));

            qualifier = qualifiers.ToString();
            applicationData = appData.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnumComponentQualifiers(
            string component, int index,
            StringBuilder qualifiers, ref int qualifiersLength,
            StringBuilder applicationData, ref int applicationDataLength);
        #endregion

        #region ProductCode
        public System.Guid ProductCode
        {
            get
            {
                StringBuilder guid = new StringBuilder(Installer.MaxGuidLength+1);
                TR(MsiGetProductCode(m_code, guid));
                return new System.Guid(guid.ToString());
            }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetProductCode(string component,
            StringBuilder productCode);
        #endregion

        #region Path
        public string Path
        {
            get
            {
                int pathLength = Installer.MaxPathLength;
                StringBuilder path = new StringBuilder(pathLength);
                TR(MsiLocateComponent(m_code, path, ref pathLength));
                return path.ToString();
            }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiLocateComponent(string component,
            StringBuilder path, ref int pathLength);
        #endregion

        #region ProvideQualified
        public string ProvideQualified(string qualifier,
            InstallMode installMode)
        {
            int pathLength = Installer.MaxPathLength;
            StringBuilder path = new StringBuilder(pathLength);
            TR(MsiProvideQualifiedComponent(m_code, qualifier,
                (UInt32) installMode, path, ref pathLength));
            return path.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiProvideQualifiedComponent(
            string component, string qualifier, UInt32 installMode,
            StringBuilder path, ref int pathLength);

        public string ProvideQualified(
            string qualifier, InstallMode installMode, string product)
        {
            int pathLength = Installer.MaxPathLength;
            StringBuilder path = new StringBuilder(pathLength);
            TR(MsiProvideQualifiedComponentEx(m_code, qualifier,
                (UInt32) installMode, product, 0, 0, path, ref pathLength));
            return path.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiProvideQualifiedComponentEx(
            string component, string qualifier, UInt32 installMode,
            string product, int reserved1, int reserved2,
            StringBuilder path, ref int pathLength);
        #endregion

        private static void TR(UInt32 result)
        {
            Installer.TR(result);
        }

        private string m_code;
    }
}
