using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
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
        [Flags]
        public enum SourceType
        {
            ShortFileNames  = 0x00000001,
            Compressed      = 0x00000002,
            AdminImage      = 0x00000004
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
        public bool ShortFileNames
        {
            get { return 0 != (Words & (int) SourceType.ShortFileNames); }
        }
        public bool Compressed
        {
            get { return 0 != (Words & (int) SourceType.Compressed); }
        }
        public bool AdministrativeImage
        {
            get { return 0 != (Words & (int) SourceType.AdminImage); }
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
            Installer.TR(result);
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
}
