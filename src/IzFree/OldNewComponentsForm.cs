using GUIDGENLib;
using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace IzFree
{
	/// <summary>
	/// Summary description for OldNewComponentsForm.
	/// </summary>
    public class OldNewComponentsForm : System.Windows.Forms.Form
    {
        private System.Windows.Forms.Button browseButton;
        private System.Windows.Forms.Label scanDirectoryLabel;
        private System.Windows.Forms.TextBox scanDirectory;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TreeView componentTree;
        private System.Windows.Forms.Label sourceDirectoryLabel;
        private System.Windows.Forms.Label targetDirectoryLabel;
        private System.Windows.Forms.TextBox sourceDirectory;
        private System.Windows.Forms.TextBox targetDirectory;
        private System.Windows.Forms.Button acceptButton;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label featureLabel;
        private System.Windows.Forms.TreeView featureTreeView;
        private System.Windows.Forms.Button scanButton;
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.Container components = null;

        public OldNewComponentsForm(MSI.Database db)
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            m_db = db;
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose( bool disposing )
        {
            if( disposing )
            {
                if(components != null)
                {
                    components.Dispose();
                }
            }
            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.scanDirectoryLabel = new System.Windows.Forms.Label();
            this.scanDirectory = new System.Windows.Forms.TextBox();
            this.browseButton = new System.Windows.Forms.Button();
            this.componentTree = new System.Windows.Forms.TreeView();
            this.label1 = new System.Windows.Forms.Label();
            this.sourceDirectoryLabel = new System.Windows.Forms.Label();
            this.targetDirectoryLabel = new System.Windows.Forms.Label();
            this.sourceDirectory = new System.Windows.Forms.TextBox();
            this.targetDirectory = new System.Windows.Forms.TextBox();
            this.acceptButton = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.featureLabel = new System.Windows.Forms.Label();
            this.featureTreeView = new System.Windows.Forms.TreeView();
            this.scanButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // scanDirectoryLabel
            // 
            this.scanDirectoryLabel.Location = new System.Drawing.Point(16, 8);
            this.scanDirectoryLabel.Name = "scanDirectoryLabel";
            this.scanDirectoryLabel.Size = new System.Drawing.Size(88, 16);
            this.scanDirectoryLabel.TabIndex = 0;
            this.scanDirectoryLabel.Text = "Scan Directory:";
            this.scanDirectoryLabel.TextAlign = System.Drawing.ContentAlignment.BottomRight;
            // 
            // scanDirectory
            // 
            this.scanDirectory.Location = new System.Drawing.Point(112, 8);
            this.scanDirectory.Name = "scanDirectory";
            this.scanDirectory.Size = new System.Drawing.Size(272, 20);
            this.scanDirectory.TabIndex = 1;
            this.scanDirectory.Text = "";
            // 
            // browseButton
            // 
            this.browseButton.Location = new System.Drawing.Point(392, 8);
            this.browseButton.Name = "browseButton";
            this.browseButton.Size = new System.Drawing.Size(56, 23);
            this.browseButton.TabIndex = 2;
            this.browseButton.Text = "Browse...";
            this.browseButton.Click += new System.EventHandler(this.browseButton_Click);
            // 
            // componentTree
            // 
            this.componentTree.ImageIndex = -1;
            this.componentTree.Location = new System.Drawing.Point(8, 64);
            this.componentTree.Name = "componentTree";
            this.componentTree.SelectedImageIndex = -1;
            this.componentTree.Size = new System.Drawing.Size(240, 320);
            this.componentTree.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(16, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 16);
            this.label1.TabIndex = 4;
            this.label1.Text = "New Components:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // sourceDirectoryLabel
            // 
            this.sourceDirectoryLabel.Location = new System.Drawing.Point(8, 400);
            this.sourceDirectoryLabel.Name = "sourceDirectoryLabel";
            this.sourceDirectoryLabel.Size = new System.Drawing.Size(48, 23);
            this.sourceDirectoryLabel.TabIndex = 6;
            this.sourceDirectoryLabel.Text = "Source:";
            this.sourceDirectoryLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // targetDirectoryLabel
            // 
            this.targetDirectoryLabel.Location = new System.Drawing.Point(8, 432);
            this.targetDirectoryLabel.Name = "targetDirectoryLabel";
            this.targetDirectoryLabel.Size = new System.Drawing.Size(48, 23);
            this.targetDirectoryLabel.TabIndex = 7;
            this.targetDirectoryLabel.Text = "Target:";
            this.targetDirectoryLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // sourceDirectory
            // 
            this.sourceDirectory.Location = new System.Drawing.Point(64, 400);
            this.sourceDirectory.Name = "sourceDirectory";
            this.sourceDirectory.ReadOnly = true;
            this.sourceDirectory.Size = new System.Drawing.Size(184, 20);
            this.sourceDirectory.TabIndex = 8;
            this.sourceDirectory.Text = "";
            // 
            // targetDirectory
            // 
            this.targetDirectory.Location = new System.Drawing.Point(64, 432);
            this.targetDirectory.Name = "targetDirectory";
            this.targetDirectory.ReadOnly = true;
            this.targetDirectory.Size = new System.Drawing.Size(184, 20);
            this.targetDirectory.TabIndex = 9;
            this.targetDirectory.Text = "";
            // 
            // acceptButton
            // 
            this.acceptButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.acceptButton.Enabled = false;
            this.acceptButton.Location = new System.Drawing.Point(296, 408);
            this.acceptButton.Name = "acceptButton";
            this.acceptButton.Size = new System.Drawing.Size(75, 32);
            this.acceptButton.TabIndex = 10;
            this.acceptButton.Text = "OK";
            // 
            // button1
            // 
            this.button1.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.button1.Location = new System.Drawing.Point(400, 408);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 32);
            this.button1.TabIndex = 11;
            this.button1.Text = "Cancel";
            // 
            // featureLabel
            // 
            this.featureLabel.Location = new System.Drawing.Point(272, 40);
            this.featureLabel.Name = "featureLabel";
            this.featureLabel.Size = new System.Drawing.Size(96, 16);
            this.featureLabel.TabIndex = 12;
            this.featureLabel.Text = "Features:";
            this.featureLabel.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // featureTreeView
            // 
            this.featureTreeView.ImageIndex = -1;
            this.featureTreeView.Location = new System.Drawing.Point(264, 64);
            this.featureTreeView.Name = "featureTreeView";
            this.featureTreeView.SelectedImageIndex = -1;
            this.featureTreeView.Size = new System.Drawing.Size(240, 320);
            this.featureTreeView.TabIndex = 14;
            // 
            // scanButton
            // 
            this.scanButton.Location = new System.Drawing.Point(456, 8);
            this.scanButton.Name = "scanButton";
            this.scanButton.Size = new System.Drawing.Size(56, 23);
            this.scanButton.TabIndex = 15;
            this.scanButton.Text = "Scan";
            this.scanButton.Click += new System.EventHandler(this.scanButton_Click);
            // 
            // OldNewComponentsForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(520, 470);
            this.Controls.Add(this.scanButton);
            this.Controls.Add(this.featureTreeView);
            this.Controls.Add(this.featureLabel);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.acceptButton);
            this.Controls.Add(this.targetDirectory);
            this.Controls.Add(this.sourceDirectory);
            this.Controls.Add(this.scanDirectory);
            this.Controls.Add(this.targetDirectoryLabel);
            this.Controls.Add(this.sourceDirectoryLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.componentTree);
            this.Controls.Add(this.browseButton);
            this.Controls.Add(this.scanDirectoryLabel);
            this.Name = "OldNewComponentsForm";
            this.Text = "Create New Components";
            this.ResumeLayout(false);

        }
        #endregion

        private void browseButton_Click(object sender, System.EventArgs e)
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            if (DialogResult.OK == dlg.ShowDialog())
            {
                scanDirectory.Text = dlg.SelectedPath;
            }
        }

        private void DisplayFeatures()
        {
            ArrayList roots = new ArrayList();
            Hashtable tree = new Hashtable();

            using (MSI.View view = m_db.OpenView(
                       "SELECT `Feature`,`Feature_Parent` FROM `Feature`" +
                       " ORDER BY `Feature_Parent`"))
            {
                for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                {
                    if (rec.IsNull(2))
                    {
                        roots.Add(rec.GetString(1));
                    }
                    else
                    {
                        string parent = rec.GetString(2);
                        if (!tree.ContainsKey(parent))
                        {
                            tree[parent] = new ArrayList();
                        }
                        (tree[parent] as ArrayList).Add(rec.GetString(1));
                    }
                    rec.Dispose();
                }
                view.Close();
            }

            roots.Sort();

            TreeView tv = new TreeView();
            for (int i = 0; i < roots.Count; i++)
            {
                string feature = roots[i] as string;
                TreeNode root = new TreeNode(feature);
                string label = "R" + i.ToString();
                root.Tag = label;
                tv.Nodes.Add(root);
                AddFeatures(tree, tv, label, feature);
            }
        }

        private void AddFeatures(Hashtable tree, TreeView tv, string parentLabel, string parent)
        {
            ArrayList kids = tree[parent] as ArrayList;
            kids.Sort();
            for (int i = 0; i < kids.Count; i++)
            {
                string kid = kids[i] as string;
                TreeNode child = new TreeNode(kid);
                string label = parentLabel + ".F" + i.ToString();
                child.Tag = label;
                tv.Nodes.Add(child);
                AddFeatures(tree, tv, label, kid);
            }
        }

        private struct FileBundle
        {
            public string directory;
            public string name;
            public long size;
            public string version;
        }

        private struct DirectoryBundle
        {
            public string directory;
            public string name;
            public string parent;
            public string defaultDir;
        }

        public struct ComponentBundle
        {
            string name;
            string directory;
            ArrayList fileList;
        }

        ArrayList m_files;
        ArrayList m_directories;
        ArrayList m_components;

        private void EnumFiles(string root, string parent, DirectoryInfo dir)
        {
            // record the files in this folder
            foreach (FileInfo file in dir.GetFiles())
            {
                FileBundle fi = new FileBundle();
                fi.directory = dir.FullName;
                fi.name = file.Name;
                fi.size = file.Length;
                fi.version = m_version.get_Version(file.FullName);
                m_files.Add(fi);
            }

            // record the folder
            string name = dir.FullName;
            {
                if (name.ToLower().StartsWith(root.ToLower()))
                {
                    name = name.Remove(0, root.Length);
                }
                DirectoryBundle di = new DirectoryBundle();
                if (name == "")
                {
                    name = "APPDIR";
                    di.directory = ".";
                    di.name = name;
                    di.parent = "";
                    di.defaultDir = "SourceDir";
                }
                else
                {
                    di.directory = name;
                    di.name = name.Replace('\\', '_');
                    di.parent = parent;
                    di.defaultDir = (dir.Name != ShortName(dir.Name)) ?
                        ShortName(dir.Name) + "|" + dir.Name : dir.Name;
                }
                m_directories.Add(di);
            }

            // record subfolders of the folder
            foreach (DirectoryInfo subdir in dir.GetDirectories())
            {
                EnumFiles(root, name, subdir);
            }
        }

        private string ShortName(string name)
        {
            return name;
        }

        private void scanButton_Click(object sender, System.EventArgs e)
        {
            m_files = new ArrayList();
            m_directories = new ArrayList();
            EnumFiles(scanDirectory.Text, "",
                new DirectoryInfo(scanDirectory.Text));
        }

        private MSI.Database m_db;
        private FileVersionClass m_version = new FileVersionClass();
    }
}
