using System;
using System.Windows.Forms;

namespace IzFree.Helpers
{
	/// <summary>
	/// Summary description for WaitCursor.
	/// </summary>
	public class WaitCursor : IDisposable
	{
		public WaitCursor()
		{
            Cursor.Current = Cursors.WaitCursor;
        }
        #region IDisposable Members

        ~WaitCursor()
        {
            Dispose(false);
        }

        #region IDisposable Members
        public void Dispose()
        {
            Dispose(true);
        }
        #endregion

        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                GC.SuppressFinalize(this);
                Cursor.Current = Cursors.Default;
            }
        }

        #endregion
    }
}
