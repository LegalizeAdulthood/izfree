using Microsoft.Win32;
using System;
using System.IO;
using Pahvant.MSI;

namespace IzFree
{
	/// <summary>
	/// Summary description for Application.
	/// </summary>
	public class Application
	{
        #region Static Methods
        public static string ToolString(string tool, string name, string defaultValue)
        {
            string subkey = @"Software\Pahvant\izfree\2.0\" + tool;
            try
            {
                using (RegistryKey key = Registry.CurrentUser.OpenSubKey(subkey))
                {
                    return key.GetValue(name).ToString();
                }
            }
            catch
            {
                try
                {
                    using (RegistryKey key = Registry.LocalMachine.OpenSubKey(subkey))
                    {
                        return key.GetValue(name).ToString();
                    }
                }
                catch
                {
                    return defaultValue;
                }
            }
        }

        public static string NewGuid()
        {
            return "{" + Guid.NewGuid().ToString().ToUpper() + "}";
        }
        public static View ExecView(Database db, string sql)
        {
            View view = db.OpenView(sql);
            view.Execute();
            return view;
        }

        public static string WIFileName(string filename)
        {
            //System.Diagnostics.Debug.Assert(false);
            return filename;
        }

        public static string ShortName(string name)
        {
            return name;
        }
        #endregion

        #region Constructors and Destructors
		public Application()
		{
		}
        #endregion

        #region Public Properties
        public Project Project
        {
            get { return m_project; }
        }
        #endregion

        #region Public Operations
        public void OpenProject(string filename)
        {
            m_project = new Project(filename);
        }

        public void CloseProject()
        {
            m_project.Close();
            m_project = null;
        }

        public void NewProject(string filename)
        {
            m_project = new Project(filename);
        }

        public void SaveProject()
        {
            m_project.Save();
        }

        public void SaveProjectAs(string filename)
        {
            m_project.SaveAs(filename);
        }

        public void NewPackage(string templateDirectory,
            string databaseFileName, string manufacturer,
            string productName, string productVersion,
            string targetDirectoryRoot, string targetDirectory,
            string packageCode, string productCode, string upgradeCode)
        {
            m_project = new Project(templateDirectory, databaseFileName,
                manufacturer, productName, productVersion,
                targetDirectoryRoot, targetDirectory, packageCode,
                productCode, upgradeCode);
        }
        #endregion

        #region Private Instance Data Members
        private Project m_project = null;
        #endregion
	}
}
