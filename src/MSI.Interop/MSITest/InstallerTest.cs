using MSI = Pahvant.MSI;
using System;
using System.Diagnostics;

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

        public void AdvertiseProduct()
        {
            string package = "test.msi";
            string scriptPath = @"c:\tmp";
            string transforms = null;
            int language = 0;
            MSI.ArchitectureFlags platform = MSI.ArchitectureFlags.Current;
            MSI.AdvertiseOptionFlags options = 0;
            new MSI.Package(package).AdvertiseProduct(scriptPath, transforms,
                language, platform, options);
        }

        public void Run()
        {
            MSI.Installer.SetExternalUI(
                new MSI.Installer.UIHandlerDelegate(UIHandler), ~0, IntPtr.Zero); //this);
            new MSI.Package("test.msi").Install();
        }

        int UIHandler(IntPtr context, int messageType, string message)
        {
            MSI.InstallMessage kind =
                (MSI.InstallMessage) (0xFF000000 & messageType);
            int result = -1;
            switch (kind)
            {
                case MSI.InstallMessage.ActionData:
                    result = (int) MSI.Installer.ControlIds.IDOK;
                    break;
                case MSI.InstallMessage.ActionStart:
                    result = (int) MSI.Installer.ControlIds.IDOK;
                    break;
                case MSI.InstallMessage.Progress:
                    result = (int) MSI.Installer.ControlIds.IDOK;
                    break;

                case MSI.InstallMessage.CommonData:
                    break;
                case MSI.InstallMessage.Error:
                    break;
                case MSI.InstallMessage.FatalExit:
                    break;
                case MSI.InstallMessage.FilesInUse:
                    break;
                case MSI.InstallMessage.Info:
                    break;
                case MSI.InstallMessage.Initialize:
                    break;
                case MSI.InstallMessage.OutOfDiskSpace:
                    break;
                case MSI.InstallMessage.ResolveSource:
                    break;
                case MSI.InstallMessage.ShowDialog:
                    break;
                case MSI.InstallMessage.Terminate:
                    break;
                case MSI.InstallMessage.User:
                    break;
                case MSI.InstallMessage.Warning:
                    break;

                default:
                    break;
            }

            Trace.WriteLine(String.Format("Type: {0}, '{1}'", kind.ToString(), message));
            return result;
        }
    }
}
