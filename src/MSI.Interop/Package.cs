using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
	/// <summary>
	/// Summary description for Package.
	/// </summary>
	public class Package
	{
        public enum OpenFlags
        {
            Default                     = 0,
            IgnoreMachineState          = 1,
        }
        
        public Package(string packagePath)
		{
            m_path = packagePath;
		}

        public string Path
        {
            get { return m_path; }
        }

        #region AdvertiseProduct
        public void AdvertiseProduct(string scriptFilePath,
            string transforms, int language)
        {
            TR(MsiAdvertiseProduct(m_path, scriptFilePath, transforms,
                language));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiAdvertiseProduct(string packagePath,
            string scriptFilePath, string transforms, int language);

        public void AdvertiseProduct(string scriptFilePath,
            string transforms,
            int language,
            ArchitectureFlags platform,
            AdvertiseOptionFlags options)
        {
            TR(MsiAdvertiseProductEx(m_path, scriptFilePath, transforms,
                language, (int) platform, (int) options));
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiAdvertiseProductEx(string packagePath,
            string scriptFilePath, string transforms, int language,
            int platform, int options);

        public void AdvertiseProduct(AdvertiseFlags flags,
            string transforms, int language,
            ArchitectureFlags platform, AdvertiseOptionFlags options)
        {
            TR(MsiAdvertiseProductEx(m_path, (int) flags, transforms,
                language, (int) platform, (int) options));
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiAdvertiseProductEx(string packagePath,
            int flags, string transforms, int language,
            int platform, int options);
        #endregion

        #region Install
        public void Install()
        {
            Install("");
        }
        public void Install(string commandLine)
        {
            TR(MsiInstallProduct(m_path, commandLine));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiInstallProduct(string packagePath,
            string commandLine);
        #endregion

        #region Open
        public Database Open()
        {
            IntPtr databaseHandle;
            TR(MsiOpenPackage(m_path, out databaseHandle));
            return new Database(databaseHandle);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiOpenPackage(string package,
            out IntPtr product);

        public Database Open(OpenFlags options)
        {
            IntPtr databaseHandle;
            TR(MsiOpenPackageEx(m_path, (int) options, out databaseHandle));
            return new Database(databaseHandle);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiOpenPackageEx(string package,
            int options, out IntPtr databaseHandle);
        #endregion

        #region Verify
        public void Verify()
        {
            TR(MsiVerifyPackage(m_path));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiVerifyPackage(string package);
        #endregion

        private static void TR(UInt32 result)
        {
            Installer.TR(result);
        }

        private string m_path;
	}
}
