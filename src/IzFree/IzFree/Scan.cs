using GUIDGENLib;
using IzFree;
using System;
using IO = System.IO;
using System.Collections;

namespace IzFree.Scan
{
    public class File
    {
        public File(Directory directory, string name,
            long size, string version, string shortName)
        {
            m_directory = directory;
            m_name = name;
            m_size = size;
            m_version = version;
            m_shortName = shortName;
            m_component = null;
        }

        #region Component
        public Component Component
        {
            get { return m_component; }
            set { m_component = value; }
        }
        private Component m_component;
        #endregion

        #region Directory
        public Directory Directory
        {
            get { return m_directory; }
            set { m_directory = value; }
        }
        private Directory m_directory;
        #endregion

        #region Name
        public string Name
        {
            get { return m_name; }
            set { m_name = value; }
        }
        private string m_name;
        #endregion

        #region Size
        public long Size
        {
            get { return m_size; }
            set { m_size = value; }
        }
        private long m_size;
        #endregion

        #region Version
        public string Version
        {
            get { return m_version; }
            set { m_version = value; }
        }
        private string m_version;
        #endregion

        #region ShortName
        public string ShortName
        {
            get { return m_shortName; }
            set { m_shortName = value; }
        }
        private string m_shortName;
        #endregion
    }

    public class Directory
    {
        public Directory()
        {
        }
        public Directory(string path, string name,
            string parent, string defaultDirectory)
        {
            m_path = path;
            m_name = name;
            m_parent = parent;
            m_defaultDirectory = defaultDirectory;
        }

        #region Path
        public string Path
        {
            get { return m_path; }
            set { m_path = value; }
        }
        private string m_path;
        #endregion

        #region Name
        public string Name
        {
            get { return m_name; }
            set { m_name = value; }
        }
        private string m_name;
        #endregion

        #region Parent
        public string Parent
        {
            get { return m_parent; }
            set { m_parent = value; }
        }
        private string m_parent;
        #endregion

        #region DefaultDirectory
        public string DefaultDirectory
        {
            get { return m_defaultDirectory; }
            set { m_defaultDirectory = value; }
        }
        private string m_defaultDirectory;
        #endregion
    }

	public class Component
	{
		public Component(string name, Directory directory, File[] files)
		{
            m_name = name;
            m_directory = directory;
            m_files = (null == files) ? new ArrayList() : new ArrayList(files);
		}

        private string m_name;
        public string Name
        {
            get { return m_name; }
            set { m_name = value; }
        }

        private Directory m_directory;
        public Directory Directory
        {
            get { return m_directory; }
            set { m_directory = value; }
        }

        public File[] Files
        {
            get 
            {
                return (File[]) m_files.ToArray(typeof(File));
            }
        }
        private ArrayList m_files;

        public void AddFile(File file)
        {
            m_files.Add(file);
        }
	}

    public class Scanner
    {
        public Scanner()
        {
            m_files = new ArrayList();
            m_directories = new ArrayList();
            m_components = new ArrayList();
        }


        #region Public Methods
        #region Scan
        //////////////////////////////////////////////////////////////////////
        // Scan
        //
        // Scan a directory and create components from its contents.
        //
        public void Scan(string scanPath)
        {
            using (new Helpers.WaitCursor())
            {
                m_files.Clear();
                m_directories.Clear();
                m_components.Clear();

                EnumerateFiles(scanPath, "", new IO.DirectoryInfo(scanPath));

                DetermineComponents(IO.Path.GetFileName(scanPath));
            }
        }
        #endregion

        public void Commit(IzFree.Project project, string rootDirectory,
            string rootFeature)
        {
            CommitFiles(project);
            MSI.Database db = project.Database;
            CommitDirectories(db, rootDirectory);
            CommitMedia(db);
            CommitComponents(db);
            CommitFeatures(db, rootFeature);
            CommitFeatureComponents(db);
        }

        public Component FindComponent(string componentName)
        {
            for (int i = 0; i < m_components.Count; i++)
            {
                Component component = m_components[i] as Component;
                if (component.Name == componentName)
                {
                    return component;
                }
            }

            return null;
        }
        #endregion

        #region Private Methods
        private void CommitComponents(MSI.Database db)
        {
            using (MSI.View view = db.OpenView("INSERT INTO `Component`(" +
                       "`Component`,`ComponentId`,`Directory_`,`Attributes`," +
                       "`Condition`,`KeyPath`) VALUES (?,?,?,0,'','')"))
            {
                for (int i = 0; i < m_components.Count; i++)
                {
                    Component component = m_components[i] as Component;
                    using (MSI.Record rec = new MSI.Record(3))
                    {
                        rec.SetString(1, component.Name);
                        rec.SetString(2, Application.NewGuid());
                        rec.SetString(3, component.Directory.Name);
                        view.Execute(rec);
                    }
                }
                view.Close();
            }
        }

        private int ScrapeFileCounter(MSI.Database db)
        {
            int count = 0;
            using (MSI.View view =
                       Application.ExecView(db, "SELECT `File` FROM `File`"))
            {
                for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                {
                    count++;
                    rec.Dispose();
                }
            }
            return count;
        }

        private int FileCounter(IzFree.Project project)
        {
            try
            {
                return project.GetIntegerIzProperty("FileCounter");
            }
            catch (PropertyNotFoundException)
            {
                return ScrapeFileCounter(project.Database);
            }
            catch
            {
                throw;
            }
        }

        private void CommitFiles(IzFree.Project project)
        {
            MSI.Database db = project.Database;
            int fileCounter = FileCounter(project);

            using (MSI.View view = db.OpenView("INSERT INTO `File`(" +
                       "`File`,`Component_`,`FileName`,`FileSize`,`Version`," +
                       "`Language`,`Attributes`,`Sequence`) " +
                       "VALUES (?,?,?,?,?,?,0,1)"))
            {
                for (int i = 0; i < m_files.Count; i++)
                {
                    File file = m_files[i] as File;
                    using (MSI.Record rec = new MSI.Record(6))
                    {
                        rec.SetString(1, DatabaseKey(file.Name) + "_f" +
                            (fileCounter + i).ToString());
                        rec.SetString(2, file.Component.Name);
                        rec.SetString(3, (file.ShortName.Length > 0) ?
                            file.ShortName + "|" + file.Name : file.Name);
                        rec.SetInteger(4, (int) file.Size);
                        rec.SetString(5, file.Version);
                        if (file.Version != "")
                        {
                            rec.SetInteger(6, 0);
                        }
                        else
                        {
                            rec.SetString(6, "");
                        }
                        view.Execute(rec);
                    }
                }
                view.Close();
            }

            project.SetIzProperty("FileCounter",
                (fileCounter + m_files.Count).ToString());
        }

        private void CommitDirectories(MSI.Database db, string root)
        {
            using (MSI.View view = db.OpenView("INSERT INTO `Directory`(" +
                       "`Directory`,`Directory_Parent`,`DefaultDir`) " +
                       " VALUES (?,?,?)"))
            {
                for (int i = 0; i < m_directories.Count; i++)
                {
                    Directory dir = m_directories[i] as Directory;
                    if (dir.Name != "APPDIR")
                    {
                        using (MSI.Record rec = new MSI.Record(3))
                        {
                            rec.SetString(1, dir.Name);
                            rec.SetString(2, dir.Parent);
                            rec.SetString(3, dir.DefaultDirectory);
                            view.Execute(rec);
                        }
                    }
                }
                view.Close();
            }
        }

        private void CommitMedia(MSI.Database db)
        {
            bool insert;
            using (MSI.View view = Application.ExecView(db,
                       "SELECT * FROM `Media`"))
            using (MSI.Record rec = view.Fetch())
            {
                insert = (null == rec);
                view.Close();
            }
            if (insert)
            {
                using (MSI.View view = Application.ExecView(db,
                           "INSERT INTO `Media`(`DiskId`,`LastSequence`," +
                           "`DiskPrompt`,`Cabinet`,`VolumeLabel`,`Source`) " +
                           "VALUES (1,1,'','','','')"))
                {
                    view.Close();
                }
            }
        }

        private void CommitFeatures(MSI.Database db, string root)
        {
            int display = 0;
            using (MSI.View view = Application.ExecView(db,
                       "SELECT `Display` FROM `Feature` ORDER BY `Display`"))
            {
                for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                {
                    if (!rec.IsNull(1))
                    {
                        display = Math.Max(rec.GetInteger(1)/2, display);
                    }
                    rec.Dispose();
                }
                view.Close();
            }
            display = (0 == display) ? 100 : display+1;

            using (MSI.View view = db.OpenView("INSERT INTO `Feature`(" +
                       "`Feature`,`Feature_Parent`,`Title`,`Description`," +
                       "`Display`,`Level`,`Directory_`,`Attributes`) " +
                       "VALUES (?,?,?,?,?,?,?,0)"))
            {
                for (int i = 0; i < m_components.Count; i++)
                {
                    Component component = m_components[i] as Component;
                    using (MSI.Record rec = new MSI.Record(7))
                    {
                        rec.SetString(1, component.Name);
                        rec.SetString(2, root);
                        rec.SetString(3, component.Name);
                        rec.SetString(4, component.Name);
                        rec.SetInteger(5, 2*(i+display));
                        rec.SetInteger(6, 1);
                        rec.SetString(7, "");
                        view.Execute(rec);
                    }
                }
                view.Close();
            }
        }

        private void CommitFeatureComponents(MSI.Database db)
        {
            using (MSI.View view = db.OpenView("INSERT INTO " +
                       "`FeatureComponents`(`Feature_`,`Component_`) " +
                       "VALUES (?,?)"))
            {
                for (int i = 0; i < m_components.Count; i++)
                {
                    string name = (m_components[i] as Component).Name;
                    using (MSI.Record rec = new MSI.Record(2))
                    {
                        rec.SetString(1, name);
                        rec.SetString(2, name);
                        view.Execute(rec);
                    }
                }
                view.Close();
            }
        }

        private string DatabaseKey(string text)
        {
            string key = text;
            for (int i = 0; i < key.Length; i++)
            {
                if (!(((key[i] >= 'A') && (key[i] <= 'Z')) ||
                    ((key[i] >= '0') && (key[i] <= '9')) ||
                    (key[i] == '.') || (key[i] == '_')))
                {
                    if (i != 0)
                    {
                        key = key.Substring(0, i-1) + "_" + key.Substring(i+1);
                    }
                    else
                    {
                        key = "_" + key.Substring(i+1);
                    }
                }
            }

            if ((key[0] >= '0') && (key[0] <= '9'))
            {
                key = "_" + key;
            }
            return key;
        }


        //////////////////////////////////////////////////////////////////////
        // determine_components
        //
        // Scan file list and create a collection of components according to
        // Windows Installer component rules:
        //   Create a component for anything with a version resource
        //   Create components for any .hlp, .dll, .ocx, .exe
        //   Remaining files grouped into components by directory.
        //   First file selected as key file.
        //
        private void DetermineComponents(string baseName)
        {
            int[] assignedFiles = new int[m_files.Count];
            for (int i = 0; i < m_files.Count; i++)
            {
                File file = m_files[i] as File;
                string ext =
                    file.Name.ToLower().Substring(file.Name.Length-4);
                if ((file.Version != "") || (".exe" == ext) ||
                    (".dll" == ext) || (".ocx" == ext) || (".hlp" == ext))
                {
                    CreateComponent(file.Name, file);
                    assignedFiles[i] = m_components.Count;
                }
                else
                {
                    assignedFiles[i] = -1;
                }
            }

            for (int i = 0; i < m_files.Count; i++)
            {
                if (-1 == assignedFiles[i])
                {
                    AddToComponent(baseName, i);
                }
            }
        }

        //////////////////////////////////////////////////////////////////////
        // CreateComponent
        //
        // Create a unique component just for this file -- used for .exe, etc.
        //
        private void CreateComponent(string name, File file)
        {
            Component component = new Component(
                name, file.Directory, new Scan.File[] { file });
            file.Component = component;
            m_components.Add(component);
        }

        //////////////////////////////////////////////////////////////////////
        // AddToComponent
        //
        // Look for a directory component with which to associate this file
        //
        private void AddToComponent(string baseName, int fileIndex)
        {
            // scan list to see if we have a directory component already
            File file = m_files[fileIndex] as File;
            for (int i = m_components.Count - m_numDirectoryComponents;
                 i < m_components.Count; i++)
            {
                Component component = m_components[i] as Component;
                if (component.Directory.Equals(file.Directory))
                {
                    component.AddFile(file);
                    file.Component = component;
                    return;
                }
            }

            // didn't find it, so create new directory component
            string componentName = file.Directory.Path.Replace(@"\", "_");
            if ("." == componentName)
            {
                componentName = baseName + "_Top";
            }
            CreateComponent(componentName, file);
            m_numDirectoryComponents++;
        }

        //////////////////////////////////////////////////////////////////////
        // EnumerateFiles
        //
        // Enumerate the directories and files in a directory hierarchy.  Use
        // the given base to construct directory component names.
        //
        private void EnumerateFiles(string root, string parent,
            IO.DirectoryInfo dinfo)
        {
            // record the folder
            string name = dinfo.FullName;
            if (name.ToLower().StartsWith(root.ToLower()))
            {
                name = name.Remove(0, root.Length);
            }
            Directory dir = new Directory();
            if (name == "")
            {
                name = "APPDIR";
                dir.Path = ".";
                dir.Name = name;
                dir.Parent = "";
                dir.DefaultDirectory = "SourceDir";
            }
            else
            {
                dir.Path = name;
                dir.Name = name.Replace('\\', '_');
                dir.Parent = parent;
                dir.DefaultDirectory =
                    (dinfo.Name != Application.ShortName(dinfo.Name)) ?
                    Application.ShortName(dinfo.Name) + "|" + dinfo.Name :
                    dinfo.Name;
            }
            m_directories.Add(dir);

            // record the files in this folder
            foreach (IO.FileInfo file in dinfo.GetFiles())
            {
                m_files.Add(new File(dir,
                    file.Name, file.Length,
                    m_version.get_Version(file.FullName),
                    Application.ShortName(file.Name)));
            }

            // record subfolders of the folder
            foreach (IO.DirectoryInfo subdir in dinfo.GetDirectories())
            {
                EnumerateFiles(root, name, subdir);
            }
        }
        #endregion

        #region Private Data
        private FileVersionClass m_version = new FileVersionClass();
        private int m_numDirectoryComponents = 0;
        #endregion

        #region Files
        public File[] Files
        {
            get { return (File[]) m_files.ToArray(typeof(File)); }
        }
        private ArrayList m_files;
        #endregion

        #region Directories
        public Directory[] Directories
        {
            get { return (Directory[]) m_directories.ToArray(typeof(Directory)); }
        }
        private ArrayList m_directories;
        #endregion

        #region Components
        public Component[] Components
        {
            get { return (Component[]) m_components.ToArray(typeof(Component)); }
        }
        private ArrayList m_components;
        #endregion
    }
}
