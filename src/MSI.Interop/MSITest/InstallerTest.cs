using System;

namespace MSITest
{
	/// <summary>
	/// Summary description for InstallerTest.
	/// </summary>
	public class InstallerTest
	{
		public InstallerTest()
		{
		}

        public void Run()
        {
            AdvertiseProduct();
        }

        private void AdvertiseProduct()
        {
            string package = "test.msi";
            string scriptPath = @"c:\tmp";
            string transforms = null;
            int language = 0;
            MSI.ArchitectureFlags platform = MSI.ArchitectureFlags.Current;
            MSI.AdvertiseOptionFlags options = 0;
            MSI.Installer.AdvertiseProduct(package, scriptPath, transforms,
                language, platform, options);
        }
    }
}
