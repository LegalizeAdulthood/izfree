using System;
using System.Windows.Forms;

namespace IzFree
{
	/// <summary>
	/// Summary description for UpdateHelper.
	/// </summary>
    public class UpdateHelper : IDisposable
    {
        public UpdateHelper(Control control)
        {
            if (control is ListBox)
            {
                m_control = control;
                (m_control as ListBox).BeginUpdate();
            }
            else if (control is ListView)
            {
                m_control = control;
                (m_control as ListView).BeginUpdate();
            }
            else
            {
                throw new InvalidCastException();
            }
        }
        ~UpdateHelper()
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
                if (m_control is ListBox)
                {
                    (m_control as ListBox).EndUpdate();
                }
                else
                {
                    (m_control as ListView).EndUpdate();
                }
                m_control = null;
            }
        }

        private Control m_control = null;
    }
}
