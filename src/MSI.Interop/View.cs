using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
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
            Installer.TR(result);
        }

        private static void TR(Database db, UInt32 result)
        {
            Installer.TR(db, result);
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
}
