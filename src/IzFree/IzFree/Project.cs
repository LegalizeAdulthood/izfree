using System;
using System.Collections;
using System.IO;
using MSI;

namespace IzFree
{
    public class PropertyNotFoundException : Exception
    {
        public PropertyNotFoundException(string propertyName) : base()
        {
            m_propertyName = propertyName;
        }
        private string m_propertyName = null;

        public string PropertyName
        {
            get { return m_propertyName; }
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

        public bool Modified
        {
            get { return m_modified; }
            set { m_modified = value; }
        }
        private bool m_modified = false;

        private object FindIzProperty(string name)
        {
            ReadIzProperties();
            if (!m_properties.ContainsKey(name))
            {
                throw new PropertyNotFoundException(name);
            }
            return m_properties[name];
        }
        public string GetIzProperty(string name)
        {
            return FindIzProperty(name) as string;
        }
        public int GetIntegerIzProperty(string name)
        {
            return System.Convert.ToInt32(FindIzProperty(name));
        }

        public void SetIzProperty(string name, string data)
        {
            ReadIzProperties();
            m_properties[name] = data;
            m_modified = true;
        }
        public void SetIntegerIzProperty(string name, int data)
        {
            SetIzProperty(name, data.ToString());
        }
        #endregion

        #region Public Methods
        public void Close()
        {
            m_db.Dispose();
            m_db = null;
            m_filename = null;
            m_modified = false;
            m_properties = null;
        }

        public void Save()
        {
            if (m_modified)
            {
                WriteIzProperties();
            }
            m_db.Commit();
            m_modified = false;
        }

        public void SaveAs(string filename)
        {
            throw new NotImplementedException();
#if false
            Save();
            m_filename = filename;
#endif
        }

        public bool TableExists(string name)
        {
            using (View view = Application.ExecView(m_db,
                       "SELECT `Name` FROM `_Tables` WHERE `Name`='" +
                       name + "'"))
            {
                using (Record rec = view.Fetch())
                {
                    return (rec != null);
                }
            }
        }
        #endregion

        #region Private Methods
        private void WriteIzProperties()
        {
            if (m_izPropertyTableExists)
            {
                // update records
                foreach (string key in m_properties.Keys)
                {
                    using (View view = Application.ExecView(m_db,
                               "UPDATE `IzProperty` SET `Value`='" +
                               (m_properties[key] as string) +
                               "' WHERE `Name`='" + key + "'"))
                    {
                        view.Close();
                    }
                }
            }
            else
            {
                // create table
                using (View view = Application.ExecView(m_db,
                           "CREATE TABLE `IzProperty`(`Name` CHAR(72) NOT NULL, " +
                           "`Value` CHAR NOT NULL PRIMARY KEY `Name`)"))
                {
                    view.Close();
                }

                // now add rows to the validation table for the new table
                using (View view = m_db.OpenView("INSERT INTO `_Validation`(" +
                           "`Column`,`Category`,`Description`," +
                           "`Table`,`Nullable`,`MinValue`,`MaxValue`,`KeyTable`,`KeyColumn`," +
                           "`Set`) VALUES (?,?,?,'IzProperty','N','','','','','')"))
                {
                    using (Record rec = new Record(3))
                    {
                        rec.SetString(1, "Name");
                        rec.SetString(2, "Identifier");
                        rec.SetString(3, "The name of the izfree property.");
                        view.Execute(rec);

                        rec.SetString(1, "Value");
                        rec.SetString(2, "Text");
                        rec.SetString(3, "The value of the izfree property.");
                        view.Execute(rec);
                    }
                    view.Close();
                }

                // insert records
                using (View view = Application.ExecView(m_db,
                           "INSERT INTO `IzProperty`(`Name`,`Value`) VALUES (?,?)"))
                {
                    using (Record rec = new Record(2))
                    {
                        foreach (string key in m_properties.Keys)
                        {
                            rec.SetString(1, key);
                            rec.SetString(2, m_properties[key] as string);
                            view.Execute(rec);
                        }
                    }
                    view.Close();
                }
            }
        }

        private void ReadIzProperties()
        {
            if (m_properties != null)
            {
                return;
            }

            m_properties = new Hashtable();
            m_izPropertyTableExists = TableExists("IzProperty");
            if (m_izPropertyTableExists)
            {
                using (View view = Application.ExecView(m_db,
                            "SELECT `Name`,`Value` FROM `IzProperty`"))
                {
                    for (Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                    {
                        m_properties[rec.GetString(1)] = rec.GetString(2);
                        rec.Dispose();
                    }
                }
            }
        }

        private void Merge(string sourcePath)
        {
            using (Database source =
                new Database(sourcePath, Database.OpenMode.ReadOnly))
            {
                m_db.Merge(source, "IzFreeMergeErrors");
            }
        }

        // get entry from Property table
        public string GetProperty(string name)
        {
            string text = "";
            using (View view = Application.ExecView(Database,
                       "SELECT `Value` FROM `Property` WHERE `Property`='" +
                       name + "'"))
            {
                Record rec = view.Fetch();
                view.Close();
                if (rec != null)
                {
                    text = rec.GetString(1);
                    rec.Dispose();
                }
            }
            return text;
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
        private bool m_izPropertyTableExists = false;
        private Hashtable m_properties = null;
        #endregion
	}
}
