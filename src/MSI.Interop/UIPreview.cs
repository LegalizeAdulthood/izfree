using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
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
            Installer.TR(result);
        }

        MSIHandle m_handle;
    }
}