using System;
using System.IO;
using MSI;

namespace IzFree
{
    public class PropertyNotFoundException : Exception
    {
        public PropertyNotFoundException() : base()
        {
        }
    }

	/// <summary>
	/// Summary description for Project.
	/// </summary>
	public class Project
	{
        #region Constructors and Destructors
        public Project()
        {}
		
        public Project(string filename)
		{
            m_filename = filename;
            m_db = new Database(m_filename,
                Database.OpenMode.Transact);
		}

        public Project(string filename, Database db)
        {
            m_filename = filename;
            m_db = db;
        }

        public Project(string templateDirectory,
            string databaseFileName, string manufacturer,
            string productName, string productVersion,
            string targetDirectoryRoot, string targetDirectory,
            string packageCode, string productCode, string upgradeCode)
        {
            string source = templateDirectory;
            if (!source.EndsWith(@"\"))
            {
                source += @"\";
            }

            File.Copy(source + "schema.msi", databaseFileName, true);
            m_db = new Database(databaseFileName, Database.OpenMode.Transact);
            Merge(source + "Sequence.msi");
            Merge(source + "UISample.msi");

            using (SummaryInformation si = m_db.SummaryInformation(9))
            {
                si.Title = "Installation Database";
                si.Subject = productName;
                si.Author = manufacturer;
                si.Comments =
                    "This installation database contains the " +
                    "logic and data needed to install " + productName;
                si.Revision = packageCode;
                DateTime timestamp = DateTime.Now;
                si.Printed = timestamp;
                si.Created = timestamp;
                si.Saved = timestamp;
                si.Application = "izfree Tools for Windows Installer 2.0";
                si.Persist();
            }

            using (View view = m_db.OpenView(
                    "INSERT INTO `Property`(`Property`,`Value`) VALUES (?,?)"))
            {
                SetProperty(view, "Manufacturer", manufacturer);
                SetProperty(view, "ProductCode", productCode);
                SetProperty(view, "ProductName", productName);
                SetProperty(view, "ProductVersion", productVersion);
                SetProperty(view, "UpgradeCode", upgradeCode);
                view.Close();
            }

            using (View view = m_db.OpenView("INSERT INTO `Directory`(" +
                    "`Directory`,`Directory_Parent`,`DefaultDir`) VALUES (?,?,?)"))
            {
                SetDirectory(view, "TARGETDIR", "", "SourceDir");
                SetDirectory(view, targetDirectoryRoot, "TARGETDIR", ".");
                SetDirectory(view, "APPDIR", targetDirectoryRoot,
                    IzFree.Application.WIFileName(targetDirectory) + ":.");
                view.Close();
            }

            using (View view = m_db.OpenView("INSERT INTO `Feature`(" +
                       "`Feature`,`Feature_Parent`,`Title`,`Description`," +
                       "`Display`,`Level`,`Directory_`,`Attributes`)" +
                       "VALUES " +
                       "('All', '', 'All Features'," +
                       "'All features in " + productName +
                       ".', 10, 1, 'APPDIR', 0)"))
            {
                view.Execute();
                view.Close();
            }
            m_db.Commit();
            m_filename = databaseFileName;
        }
        #endregion
        
        #region Public Properties
        public string Filename
        {
            get { return m_filename; }
        }
        public Database Database
        {
            get { return m_db; }
        }

        public string GetProperty(string name)
        {
            string data = null;
            using (View view = Application.ExecView(m_db,
                       "SELECT `Value` FROM `IzProperty` WHERE " +
                       "`IzProperty`.`Property` = '" + name + "'"))
            {
                using (Record rec = view.Fetch())
                {
                    if (rec != null)
                    {
                        data = rec.GetString(1);
                    }
                }
                view.Close();
            }
            return data;
        }

        public void SetProperty(string name, string data)
        {
        }

        public int GetIntegerProperty(string name)
        {
            using (View view = Application.ExecView(m_db,
                       "SELECT `Value` FROM `IzProperty` WHERE " +
                       "`IzProperty`.`Property` = '" + name + "'"))
            {
                using (Record rec = view.Fetch())
                {
                    if (rec != null)
                    {
                        return rec.GetInteger(1);
                    }
                }
            }
            throw new PropertyNotFoundException();
        }

        public void SetIntegerProperty(string name, int data)
        {
        }
        #endregion

        #region Private Methods
        private void Merge(string sourcePath)
        {
            using (Database source =
                new Database(sourcePath, Database.OpenMode.ReadOnly))
            {
                m_db.Merge(source, "IzFreeMergeErrors");
            }
        }

        private void SetProperty(View view, string name, string val)
        {
            using (Record rec = new Record(2))
            {
                rec.SetString(1, name);
                rec.SetString(2, val);
                view.Execute(rec);
            }
        }
        private void SetDirectory(View view,
            string directory, string parent, string defaultDirectory)
        {
            using (Record rec = new Record(3))
            {
                rec.SetString(1, directory);
                rec.SetString(2, parent);
                rec.SetString(3, defaultDirectory);
                view.Execute(rec);
            }
        }
        #endregion
        
        #region Private Instance Data
        private string m_filename = null;
        private Database m_db = null;
        #endregion
	}
}
