using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
    public class Record : IDisposable
    {
        #region Constructors/Destructors
        public Record(int count)
        {
            m_handle = new MSIHandle(MsiCreateRecord(count));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern IntPtr MsiCreateRecord(int count);

        public Record(IntPtr handle)
        {
            m_handle = new MSIHandle(handle);
        }
        #endregion 

        #region ClearData
        public void ClearData()
        {
            TR(MsiRecordClearData(m_handle.Handle));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiRecordClearData(IntPtr record);
        #endregion

        #region DataSize
        public int DataSize(int field)
        {
            return (int) MsiRecordDataSize(m_handle.Handle, (UInt32) field);
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordDataSize(
            IntPtr record, UInt32 field);
        #endregion

        #region SetString
        public void SetString(int index, string data)
        {
            TR(MsiRecordSetString(m_handle.Handle, (UInt32) index, data));
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordSetString(IntPtr record,
            UInt32 field, string data);
        #endregion

        #region GetString
        public string GetString(int field)
        {
            StringBuilder sb = new StringBuilder(DataSize(field)+1);
            UInt32 count = (UInt32) sb.Capacity;
            TR(MsiRecordGetString(m_handle.Handle, (UInt32) field,
                sb, ref count));
            return sb.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordGetString(
            IntPtr record, UInt32 field, StringBuilder data, ref UInt32 count);
        #endregion

        #region GetInteger
        public int GetInteger(int field)
        {
            return MsiRecordGetInteger(m_handle.Handle, (UInt32) field);
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern int MsiRecordGetInteger(
            IntPtr record, UInt32 field);
        #endregion

        #region SetInteger
        public void SetInteger(int field, int data)
        {
            TR(MsiRecordSetInteger(m_handle.Handle, (UInt32) field, data));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiRecordSetInteger(
            IntPtr record, UInt32 field, int data);
        #endregion

        #region IsNull
        public bool IsNull(int field)
        {
            return MsiRecordIsNull(m_handle.Handle, (UInt32) field) != 0;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern int MsiRecordIsNull(
            IntPtr record, UInt32 field);
        #endregion

        #region ReadStream
        public byte[] ReadStream(int field)
        {
            byte[] bytes = new byte[] { };
            int count = bytes.Length;
            TR(MsiRecordReadStream(m_handle.Handle, (UInt32) field,
                bytes, ref count));
            return bytes;            
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordReadStream(IntPtr record,
            UInt32 field, byte[] buffer, ref int bufferLength);
        #endregion

        #region SetStream
        public void SetStream(int field, string path)
        {
            TR(MsiRecordSetStream(m_handle.Handle, (UInt32) field, path));
        }
        [DllImport(Installer.MSI_DLL, CharSet=CharSet.Auto)]
        private static extern UInt32 MsiRecordSetStream(IntPtr record,
            UInt32 field, string path);
        #endregion

        #region FieldCount
        public int FieldCount
        {
            get { return (int) MsiRecordGetFieldCount(m_handle.Handle); }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiRecordGetFieldCount(IntPtr record);
        #endregion


        private static void TR(UInt32 result)
        {
            Installer.TR(result);
        }

        public IntPtr Handle
        {
            get { return m_handle.Handle; }
        }

        private MSIHandle m_handle;
        #region IDisposable Members
        public void Dispose()
        {
            Dispose(true);
        }
        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                GC.SuppressFinalize(this);
                m_handle.Dispose();
            }
        }
        ~Record()
        {
            Dispose(false);
        }
        #endregion
    }
}
