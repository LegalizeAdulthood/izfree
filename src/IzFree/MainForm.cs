using System;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace IzFree
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
    public class MainForm : System.Windows.Forms.Form
    {
        private System.Windows.Forms.TabPage componentsTab;
        private System.Windows.Forms.TabPage fileSystemTab;
        private System.Windows.Forms.TabPage registryTab;
        private System.Windows.Forms.MainMenu mainMenu;
        private System.Windows.Forms.MenuItem fileMenu;
        private System.Windows.Forms.MenuItem fileNewItem;
        private System.Windows.Forms.MenuItem fileOpenItem;
        private System.Windows.Forms.MenuItem fileSaveItem;
        private System.Windows.Forms.MenuItem fileSaveAsItem;
        private System.Windows.Forms.MenuItem editMenu;
        private System.Windows.Forms.MenuItem editCopyItem;
        private System.Windows.Forms.MenuItem editPasteItem;
        private System.Windows.Forms.MenuItem editSelectAllItem;
        private System.Windows.Forms.TabControl projectTabControl;
        private System.Windows.Forms.TabPage featuresTab;
        private System.Windows.Forms.TreeView featureTreeView;
        private System.Windows.Forms.TabPage tablesTab;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.MenuItem editPasteNewGuidItem;
        private System.Windows.Forms.MenuItem editCopyNewGuidItem;
        private System.Windows.Forms.PropertyGrid tableRowPropertyGrid;
        private System.Windows.Forms.ListView primaryKeyListView;
        private System.Windows.Forms.ListBox tablesListBox;
        private System.Windows.Forms.MenuItem tasksMenu;
        private System.Windows.Forms.MenuItem taskScanDirectoryItem;
        private System.Windows.Forms.MenuItem windowsMenu;
        private System.Windows.Forms.MenuItem windowTablesItem;
        private System.Windows.Forms.MenuItem windowFeaturesItem;
        private System.Windows.Forms.MenuItem windowComponentsItem;
        private System.Windows.Forms.MenuItem windowDialogsItem;
        private System.Windows.Forms.MenuItem windowSequencesItem;
        private System.Windows.Forms.MenuItem windowRegistryItem;
        private System.Windows.Forms.MenuItem windowIniFilesItem;
        private System.Windows.Forms.MenuItem windowCOMRegistrationItem;
        private System.Windows.Forms.MenuItem windowAssembliesItem;
        private System.Windows.Forms.MenuItem taskExtractCOMItem;
        private System.Windows.Forms.MenuItem fileCloseItem;
        private System.Windows.Forms.MenuItem fileSeparatorItem;
        private System.Windows.Forms.MenuItem fileSummaryInformationItem;
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.Container components = null;

        public MainForm()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            //
            // TODO: Add any constructor code after InitializeComponent call
            //
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose( bool disposing )
        {
            if( disposing )
            {
                if (components != null) 
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
            System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem("primaryKeyListView");
            this.mainMenu = new System.Windows.Forms.MainMenu();
            this.fileMenu = new System.Windows.Forms.MenuItem();
            this.fileNewItem = new System.Windows.Forms.MenuItem();
            this.fileOpenItem = new System.Windows.Forms.MenuItem();
            this.fileSaveItem = new System.Windows.Forms.MenuItem();
            this.fileSaveAsItem = new System.Windows.Forms.MenuItem();
            this.fileCloseItem = new System.Windows.Forms.MenuItem();
            this.fileSeparatorItem = new System.Windows.Forms.MenuItem();
            this.fileSummaryInformationItem = new System.Windows.Forms.MenuItem();
            this.editMenu = new System.Windows.Forms.MenuItem();
            this.editCopyItem = new System.Windows.Forms.MenuItem();
            this.editCopyNewGuidItem = new System.Windows.Forms.MenuItem();
            this.editPasteItem = new System.Windows.Forms.MenuItem();
            this.editPasteNewGuidItem = new System.Windows.Forms.MenuItem();
            this.editSelectAllItem = new System.Windows.Forms.MenuItem();
            this.tasksMenu = new System.Windows.Forms.MenuItem();
            this.taskScanDirectoryItem = new System.Windows.Forms.MenuItem();
            this.taskExtractCOMItem = new System.Windows.Forms.MenuItem();
            this.windowsMenu = new System.Windows.Forms.MenuItem();
            this.windowTablesItem = new System.Windows.Forms.MenuItem();
            this.windowFeaturesItem = new System.Windows.Forms.MenuItem();
            this.windowComponentsItem = new System.Windows.Forms.MenuItem();
            this.windowDialogsItem = new System.Windows.Forms.MenuItem();
            this.windowSequencesItem = new System.Windows.Forms.MenuItem();
            this.windowRegistryItem = new System.Windows.Forms.MenuItem();
            this.windowIniFilesItem = new System.Windows.Forms.MenuItem();
            this.windowCOMRegistrationItem = new System.Windows.Forms.MenuItem();
            this.windowAssembliesItem = new System.Windows.Forms.MenuItem();
            this.projectTabControl = new System.Windows.Forms.TabControl();
            this.tablesTab = new System.Windows.Forms.TabPage();
            this.tablesListBox = new System.Windows.Forms.ListBox();
            this.tableRowPropertyGrid = new System.Windows.Forms.PropertyGrid();
            this.primaryKeyListView = new System.Windows.Forms.ListView();
            this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader3 = new System.Windows.Forms.ColumnHeader();
            this.featuresTab = new System.Windows.Forms.TabPage();
            this.featureTreeView = new System.Windows.Forms.TreeView();
            this.componentsTab = new System.Windows.Forms.TabPage();
            this.fileSystemTab = new System.Windows.Forms.TabPage();
            this.registryTab = new System.Windows.Forms.TabPage();
            this.projectTabControl.SuspendLayout();
            this.tablesTab.SuspendLayout();
            this.featuresTab.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainMenu
            // 
            this.mainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                     this.fileMenu,
                                                                                     this.editMenu,
                                                                                     this.tasksMenu,
                                                                                     this.windowsMenu});
            // 
            // fileMenu
            // 
            this.fileMenu.Index = 0;
            this.fileMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                     this.fileNewItem,
                                                                                     this.fileOpenItem,
                                                                                     this.fileSaveItem,
                                                                                     this.fileSaveAsItem,
                                                                                     this.fileCloseItem,
                                                                                     this.fileSeparatorItem,
                                                                                     this.fileSummaryInformationItem});
            this.fileMenu.Text = "File";
            // 
            // fileNewItem
            // 
            this.fileNewItem.Index = 0;
            this.fileNewItem.Text = "&New Package...";
            this.fileNewItem.Click += new System.EventHandler(this.fileNewItem_Click);
            // 
            // fileOpenItem
            // 
            this.fileOpenItem.Index = 1;
            this.fileOpenItem.Text = "&Open Package...";
            this.fileOpenItem.Click += new System.EventHandler(this.fileOpenItem_Click);
            // 
            // fileSaveItem
            // 
            this.fileSaveItem.Enabled = false;
            this.fileSaveItem.Index = 2;
            this.fileSaveItem.Text = "&Save Package";
            this.fileSaveItem.Click += new System.EventHandler(this.fileSaveItem_Click);
            // 
            // fileSaveAsItem
            // 
            this.fileSaveAsItem.Enabled = false;
            this.fileSaveAsItem.Index = 3;
            this.fileSaveAsItem.Text = "Save Package &As...";
            this.fileSaveAsItem.Click += new System.EventHandler(this.fileSaveAsItem_Click);
            // 
            // fileCloseItem
            // 
            this.fileCloseItem.Enabled = false;
            this.fileCloseItem.Index = 4;
            this.fileCloseItem.Text = "Close";
            this.fileCloseItem.Click += new System.EventHandler(this.fileCloseItem_Click);
            // 
            // fileSeparatorItem
            // 
            this.fileSeparatorItem.Index = 5;
            this.fileSeparatorItem.Text = "-";
            // 
            // fileSummaryInformationItem
            // 
            this.fileSummaryInformationItem.Enabled = false;
            this.fileSummaryInformationItem.Index = 6;
            this.fileSummaryInformationItem.Text = "Summary Information...";
            // 
            // editMenu
            // 
            this.editMenu.Index = 1;
            this.editMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                     this.editCopyItem,
                                                                                     this.editCopyNewGuidItem,
                                                                                     this.editPasteItem,
                                                                                     this.editPasteNewGuidItem,
                                                                                     this.editSelectAllItem});
            this.editMenu.Text = "Edit";
            // 
            // editCopyItem
            // 
            this.editCopyItem.Enabled = false;
            this.editCopyItem.Index = 0;
            this.editCopyItem.Text = "&Copy";
            // 
            // editCopyNewGuidItem
            // 
            this.editCopyNewGuidItem.Index = 1;
            this.editCopyNewGuidItem.Text = "Copy &New GUID";
            this.editCopyNewGuidItem.Click += new System.EventHandler(this.editCopyNewGuidItem_Click);
            // 
            // editPasteItem
            // 
            this.editPasteItem.Enabled = false;
            this.editPasteItem.Index = 2;
            this.editPasteItem.Text = "&Paste";
            // 
            // editPasteNewGuidItem
            // 
            this.editPasteNewGuidItem.Index = 3;
            this.editPasteNewGuidItem.Text = "Paste Ne&w GUID";
            this.editPasteNewGuidItem.Click += new System.EventHandler(this.editPasteNewGuidItem_Click);
            // 
            // editSelectAllItem
            // 
            this.editSelectAllItem.Enabled = false;
            this.editSelectAllItem.Index = 4;
            this.editSelectAllItem.Text = "Select &All";
            // 
            // tasksMenu
            // 
            this.tasksMenu.Index = 2;
            this.tasksMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                      this.taskScanDirectoryItem,
                                                                                      this.taskExtractCOMItem});
            this.tasksMenu.Text = "Tasks";
            // 
            // taskScanDirectoryItem
            // 
            this.taskScanDirectoryItem.Enabled = false;
            this.taskScanDirectoryItem.Index = 0;
            this.taskScanDirectoryItem.Text = "Scan &Directory for Components...";
            this.taskScanDirectoryItem.Click += new System.EventHandler(this.taskScanDirectoryItem_Click);
            // 
            // taskExtractCOMItem
            // 
            this.taskExtractCOMItem.Enabled = false;
            this.taskExtractCOMItem.Index = 1;
            this.taskExtractCOMItem.Text = "Extract COM Registration...";
            // 
            // windowsMenu
            // 
            this.windowsMenu.Index = 3;
            this.windowsMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                        this.windowTablesItem,
                                                                                        this.windowFeaturesItem,
                                                                                        this.windowComponentsItem,
                                                                                        this.windowDialogsItem,
                                                                                        this.windowSequencesItem,
                                                                                        this.windowRegistryItem,
                                                                                        this.windowIniFilesItem,
                                                                                        this.windowCOMRegistrationItem,
                                                                                        this.windowAssembliesItem});
            this.windowsMenu.Text = "Windows";
            // 
            // windowTablesItem
            // 
            this.windowTablesItem.Enabled = false;
            this.windowTablesItem.Index = 0;
            this.windowTablesItem.Text = "Tables";
            // 
            // windowFeaturesItem
            // 
            this.windowFeaturesItem.Enabled = false;
            this.windowFeaturesItem.Index = 1;
            this.windowFeaturesItem.Text = "Features";
            // 
            // windowComponentsItem
            // 
            this.windowComponentsItem.Enabled = false;
            this.windowComponentsItem.Index = 2;
            this.windowComponentsItem.Text = "Components";
            // 
            // windowDialogsItem
            // 
            this.windowDialogsItem.Enabled = false;
            this.windowDialogsItem.Index = 3;
            this.windowDialogsItem.Text = "Dialogs";
            // 
            // windowSequencesItem
            // 
            this.windowSequencesItem.Enabled = false;
            this.windowSequencesItem.Index = 4;
            this.windowSequencesItem.Text = "Sequences";
            // 
            // windowRegistryItem
            // 
            this.windowRegistryItem.Enabled = false;
            this.windowRegistryItem.Index = 5;
            this.windowRegistryItem.Text = "Registry";
            // 
            // windowIniFilesItem
            // 
            this.windowIniFilesItem.Enabled = false;
            this.windowIniFilesItem.Index = 6;
            this.windowIniFilesItem.Text = "INI Files";
            // 
            // windowCOMRegistrationItem
            // 
            this.windowCOMRegistrationItem.Enabled = false;
            this.windowCOMRegistrationItem.Index = 7;
            this.windowCOMRegistrationItem.Text = "COM Registration";
            // 
            // windowAssembliesItem
            // 
            this.windowAssembliesItem.Enabled = false;
            this.windowAssembliesItem.Index = 8;
            this.windowAssembliesItem.Text = ".NET Assemblies";
            // 
            // projectTabControl
            // 
            this.projectTabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                | System.Windows.Forms.AnchorStyles.Left) 
                | System.Windows.Forms.AnchorStyles.Right)));
            this.projectTabControl.Controls.Add(this.tablesTab);
            this.projectTabControl.Controls.Add(this.featuresTab);
            this.projectTabControl.Controls.Add(this.componentsTab);
            this.projectTabControl.Controls.Add(this.fileSystemTab);
            this.projectTabControl.Controls.Add(this.registryTab);
            this.projectTabControl.Location = new System.Drawing.Point(0, 0);
            this.projectTabControl.Multiline = true;
            this.projectTabControl.Name = "projectTabControl";
            this.projectTabControl.SelectedIndex = 0;
            this.projectTabControl.Size = new System.Drawing.Size(604, 494);
            this.projectTabControl.TabIndex = 0;
            // 
            // tablesTab
            // 
            this.tablesTab.Controls.Add(this.tablesListBox);
            this.tablesTab.Controls.Add(this.tableRowPropertyGrid);
            this.tablesTab.Controls.Add(this.primaryKeyListView);
            this.tablesTab.Location = new System.Drawing.Point(4, 22);
            this.tablesTab.Name = "tablesTab";
            this.tablesTab.Size = new System.Drawing.Size(596, 468);
            this.tablesTab.TabIndex = 5;
            this.tablesTab.Text = "Tables";
            // 
            // tablesListBox
            // 
            this.tablesListBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                | System.Windows.Forms.AnchorStyles.Left) 
                | System.Windows.Forms.AnchorStyles.Right)));
            this.tablesListBox.Location = new System.Drawing.Point(8, 8);
            this.tablesListBox.Name = "tablesListBox";
            this.tablesListBox.Size = new System.Drawing.Size(121, 446);
            this.tablesListBox.TabIndex = 3;
            this.tablesListBox.SelectedIndexChanged += new System.EventHandler(this.tablesListBox_SelectedIndexChanged);
            // 
            // tableRowPropertyGrid
            // 
            this.tableRowPropertyGrid.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                | System.Windows.Forms.AnchorStyles.Left) 
                | System.Windows.Forms.AnchorStyles.Right)));
            this.tableRowPropertyGrid.CommandsVisibleIfAvailable = true;
            this.tableRowPropertyGrid.LargeButtons = false;
            this.tableRowPropertyGrid.LineColor = System.Drawing.SystemColors.ScrollBar;
            this.tableRowPropertyGrid.Location = new System.Drawing.Point(288, 8);
            this.tableRowPropertyGrid.Name = "tableRowPropertyGrid";
            this.tableRowPropertyGrid.Size = new System.Drawing.Size(296, 446);
            this.tableRowPropertyGrid.TabIndex = 2;
            this.tableRowPropertyGrid.Text = "PropertyGrid";
            this.tableRowPropertyGrid.ViewBackColor = System.Drawing.SystemColors.Window;
            this.tableRowPropertyGrid.ViewForeColor = System.Drawing.SystemColors.WindowText;
            // 
            // primaryKeyListView
            // 
            this.primaryKeyListView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                | System.Windows.Forms.AnchorStyles.Left) 
                | System.Windows.Forms.AnchorStyles.Right)));
            this.primaryKeyListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
                                                                                                 this.columnHeader1,
                                                                                                 this.columnHeader2,
                                                                                                 this.columnHeader3});
            this.primaryKeyListView.FullRowSelect = true;
            this.primaryKeyListView.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
                                                                                               listViewItem1});
            this.primaryKeyListView.LabelEdit = true;
            this.primaryKeyListView.Location = new System.Drawing.Point(136, 8);
            this.primaryKeyListView.MultiSelect = false;
            this.primaryKeyListView.Name = "primaryKeyListView";
            this.primaryKeyListView.Size = new System.Drawing.Size(144, 446);
            this.primaryKeyListView.TabIndex = 1;
            this.primaryKeyListView.View = System.Windows.Forms.View.List;
            this.primaryKeyListView.SelectedIndexChanged += new System.EventHandler(this.primaryKeyListView_SelectedIndexChanged);
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "File_";
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Directory_";
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "FileName";
            // 
            // featuresTab
            // 
            this.featuresTab.Controls.Add(this.featureTreeView);
            this.featuresTab.Location = new System.Drawing.Point(4, 22);
            this.featuresTab.Name = "featuresTab";
            this.featuresTab.Size = new System.Drawing.Size(596, 468);
            this.featuresTab.TabIndex = 4;
            this.featuresTab.Text = "Features";
            // 
            // featureTreeView
            // 
            this.featureTreeView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                | System.Windows.Forms.AnchorStyles.Left) 
                | System.Windows.Forms.AnchorStyles.Right)));
            this.featureTreeView.ImageIndex = -1;
            this.featureTreeView.Location = new System.Drawing.Point(8, 8);
            this.featureTreeView.Name = "featureTreeView";
            this.featureTreeView.SelectedImageIndex = -1;
            this.featureTreeView.Size = new System.Drawing.Size(576, 446);
            this.featureTreeView.TabIndex = 0;
            // 
            // componentsTab
            // 
            this.componentsTab.Location = new System.Drawing.Point(4, 22);
            this.componentsTab.Name = "componentsTab";
            this.componentsTab.Size = new System.Drawing.Size(596, 468);
            this.componentsTab.TabIndex = 1;
            this.componentsTab.Text = "Components";
            // 
            // fileSystemTab
            // 
            this.fileSystemTab.Location = new System.Drawing.Point(4, 22);
            this.fileSystemTab.Name = "fileSystemTab";
            this.fileSystemTab.Size = new System.Drawing.Size(596, 468);
            this.fileSystemTab.TabIndex = 2;
            this.fileSystemTab.Text = "File System";
            // 
            // registryTab
            // 
            this.registryTab.Location = new System.Drawing.Point(4, 22);
            this.registryTab.Name = "registryTab";
            this.registryTab.Size = new System.Drawing.Size(596, 468);
            this.registryTab.TabIndex = 3;
            this.registryTab.Text = "Registry";
            // 
            // MainForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(600, 487);
            this.Controls.Add(this.projectTabControl);
            this.Menu = this.mainMenu;
            this.Name = "MainForm";
            this.Text = "izfree 2.0";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.projectTabControl.ResumeLayout(false);
            this.tablesTab.ResumeLayout(false);
            this.featuresTab.ResumeLayout(false);
            this.ResumeLayout(false);

        }
        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main() 
        {
            System.Windows.Forms.Application.Run(new MainForm());
        }

        private void PopulateFeaturesTab(MSI.Database db)
        {
            MSI.View view = IzFree.Application.ExecView(db,
                "SELECT `Feature`,`Feature_Parent` FROM `Feature`" +
                    " ORDER BY `Feature_Parent`");
            ArrayList roots = new ArrayList();
            Hashtable tree = new Hashtable();
            for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
            {
                if (rec.IsNull(2))
                {
                    roots.Add(rec.GetString(1));
                }
                else
                {
                    string child = rec.GetString(1);
                    string parent = rec.GetString(2);;
                    if (tree.ContainsKey(parent))
                    {
                        (tree[parent] as ArrayList).Add(child);
                    }
                    else
                    {
                        ArrayList tmp = new ArrayList();
                        tmp.Add(child);
                        tree[parent] = tmp;
                    }
                }
            }
            view.Close();

            roots.Sort();
            foreach (ArrayList children in tree.Values)
            {
                children.Sort();
            }

            featureTreeView.Nodes.Clear();
            for (int i = 0; i < roots.Count; i++)
            {
                string label = "R" + i.ToString();
                TreeNode node = new TreeNode(label);
                node.Text = roots[i] as string;
                featureTreeView.Nodes.Add(node);
                AddFeatures(tree, node, label, node.Text);
            }
        }

        private void AddFeatures(Hashtable tree, TreeNode parentNode,
            string parentLabel, string parent)
        {
            if (tree.ContainsKey(parent))
            {
                ArrayList kids = tree[parent] as ArrayList;
                for (int i = 0; i < kids.Count; i++)
                {
                    string label = parentLabel + ".F" + i.ToString();
                    TreeNode node = new TreeNode(label);
                    node.Text = kids[i] as string;
                    parentNode.Nodes.Add(node);
                    AddFeatures(tree, node, label, kids[i] as string);
                }
            }
        }
        private void PopulateComponentsTab(MSI.Database db)
        {
            Debug.WriteLine("\nComponents:");
            MSI.View view = IzFree.Application.ExecView(db,
                "SELECT `Component`,`ComponentId`,`Directory_`," +
                    "`Attributes`,`Condition`,`KeyPath` FROM `Component`" +
                " ORDER BY `Component`");
            for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
            {
                Debug.WriteLine(String.Format("Component={0}, " +
                    "ComponentId={1}, Directory_={2}, Attributes={3}, " +
                    "Condition={4}, KeyPath={5}", rec.GetString(1),
                    rec.GetString(2), rec.GetString(3), rec.GetInteger(4),
                    rec.GetString(5), rec.GetString(6)));
                rec.Dispose();
            }
            view.Close();
        }

        private void PopulateFileSystemTab(MSI.Database db)
        {
            Debug.WriteLine("\nFiles:");
            MSI.View view = IzFree.Application.ExecView(db,
                "SELECT `File`,`Component_`,`FileName`,`FileSize`," +
                    "`Version`,`Language`,`Attributes`,`Sequence` " +
                "FROM `File` ORDER BY `File`");
            for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
            {
                Debug.WriteLine(String.Format("File={0}, Component_={1}, " +
                    "FileName={2}, FileSize={3}, Version={4}, " +
                    "Language={5}, Attributes={6}, Sequence={7}",
                    rec.GetString(1), rec.GetString(2),
                    rec.GetString(3), rec.GetInteger(4), rec.GetString(5),
                    rec.GetString(6), rec.GetInteger(7), rec.GetInteger(8)));
                rec.Dispose();
            }
            view.Close();
        }

        private void PopulateRegistryTab(MSI.Database db)
        {
            Debug.WriteLine("\nRegistry:");
            MSI.View view = IzFree.Application.ExecView(db,
                "SELECT `Registry`,`Root`,`Key`,`Name`,`Value`,`Component_`" +
                " FROM `Registry` ORDER BY `Registry`");
            for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
            {
                Debug.WriteLine(String.Format("Registry={0}, Root={1}, " +
                    "Key={2}, Name={3}, Value={4}, Component_={5}",
                    rec.GetString(1), rec.GetInteger(2),
                    rec.GetString(3), rec.GetString(4), rec.GetString(5),
                    rec.GetString(6)));
                rec.Dispose();
            }
            view.Close();
        }

        private void PopulateTablesTab(MSI.Database db)
        {
            using (new UpdateHelper(tablesListBox))
            {
                tablesListBox.Items.Clear();
                MSI.View view = IzFree.Application.ExecView(db,
                    "SELECT * FROM `_Tables` ORDER BY `Name`");
                for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                {
                    tablesListBox.Items.Add(rec.GetString(1));
                    rec.Dispose();
                }
                view.Close();
            }
        }

        private void PopulateTabs(MSI.Database db)
        {
            PopulateTablesTab(db);
            PopulateFeaturesTab(db);
            PopulateComponentsTab(db);
            PopulateFileSystemTab(db);
            PopulateRegistryTab(db);
        }

        private void fileOpenItem_Click(object sender, System.EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Setup Databases (*.msi)|*.msi|" +
                "Merge Modules (*.msm)|*.msm|" +
                "Patch Creation Parameters (*.pcp)|*.pcp|" +
                "ICE Databases (*.cub)|*.cub";
            dlg.FilterIndex = 0;
            dlg.CheckFileExists = true;
            dlg.CheckPathExists = true;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                using (new Helpers.WaitCursor())
                {
                    m_application.OpenProject(dlg.FileName);
                    NewDatabase();
                }
            }
        }

        IzFree.Application m_application = new IzFree.Application();

        private void NewDatabase()
        {
            PopulateTabs(m_application.Project.Database);
            DatabaseOpen(true);
        }

        private void DatabaseOpen(bool openNotClosed)
        {
            fileCloseItem.Enabled = openNotClosed;
            fileSummaryInformationItem.Enabled = openNotClosed;
            taskScanDirectoryItem.Enabled = openNotClosed;
            taskExtractCOMItem.Enabled = openNotClosed;
            windowTablesItem.Enabled = openNotClosed;
            windowFeaturesItem.Enabled = openNotClosed;
            windowComponentsItem.Enabled = openNotClosed;
            windowDialogsItem.Enabled = openNotClosed;
            windowSequencesItem.Enabled = openNotClosed;
            windowRegistryItem.Enabled = openNotClosed;
            windowIniFilesItem.Enabled = openNotClosed;
            windowCOMRegistrationItem.Enabled = openNotClosed;
            windowAssembliesItem.Enabled = openNotClosed;
            Modified = false;
            ShowProjectTabs(openNotClosed);
        }

        private void fileNewItem_Click(object sender, System.EventArgs e)
        {
            using (NewPackageForm package = new NewPackageForm())
            {
                if (DialogResult.OK == package.ShowDialog())
                {
                    if (File.Exists(package.DatabaseFileName))
                    {
                        if (DialogResult.No == MessageBox.Show(this,
                            package.DatabaseFileName +
                            " already exists.  Do you want to overwrite it?",
                            "Overwrite Existing Database?",
                            MessageBoxButtons.YesNo))
                        {
                            return;
                        }
                        File.Delete(package.DatabaseFileName);
                    }
                    using (new Helpers.WaitCursor())
                    {
                        m_application.NewPackage(package.TemplateDirectory,
                            package.DatabaseFileName, package.Manufacturer,
                            package.ProductName, package.ProductVersion,
                            package.TargetDirectoryRoot, package.TargetDirectory,
                            package.ProductCode, package.PackageCode,
                            package.UpgradeCode);
                        NewDatabase();
                    }
                }
            }
        }

        private void MainForm_Load(object sender, System.EventArgs e)
        {
            ShowProjectTabs(false);
        }

        private void ShowProjectTabs(bool openNotClosed)
        {
            if (openNotClosed)
            {
                projectTabControl.TabPages.Add(tablesTab);
                projectTabControl.TabPages.Add(featuresTab);
                projectTabControl.TabPages.Add(componentsTab);
                projectTabControl.TabPages.Add(fileSystemTab);
                projectTabControl.TabPages.Add(registryTab);
            }
            else
            {
                projectTabControl.TabPages.Remove(tablesTab);
                projectTabControl.TabPages.Remove(featuresTab);
                projectTabControl.TabPages.Remove(componentsTab);
                projectTabControl.TabPages.Remove(fileSystemTab);
                projectTabControl.TabPages.Remove(registryTab);
            }
        }

        private void editCopyNewGuidItem_Click(object sender, System.EventArgs e)
        {
            Clipboard.SetDataObject(IzFree.Application.NewGuid());
        }

        private void editPasteNewGuidItem_Click(object sender, System.EventArgs e)
        {
            if (this.ActiveControl is TextBox)
            {
                this.ActiveControl.Text = IzFree.Application.NewGuid();
            }
        }

        private void primaryKeyListView_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            if (primaryKeyListView.SelectedItems.Count > 0)
            {

            }
        }

        private string PrimaryKeys(string table)
        {
            return "*";
        }

        private void taskScanDirectoryItem_Click(object sender, System.EventArgs e)
        {
            using (NewComponentsForm dlg =
                       new NewComponentsForm(m_application.Project))
            {
                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    // add components
                    dlg.Commit();
                    Modified = true;
                }
            }
        }

        private bool Modified
        {
            get { return m_modified; }
            set
            {
                if (m_modified && !value)
                {
                    // was modified, now isn't modified -- discard changes?
                }
                m_modified = value;
                ShowModified(m_modified);
                SetTitle();
            }
        }
        bool m_modified = false;

        private void SetTitle()
        {
            Text = "izfree 2.0";
            if (m_application.Project != null)
            {
                Text += " - " + (Modified ? "* " : "") +
                    m_application.Project.Filename;
            }
        }

        private void ShowModified(bool modified)
        {
            fileSaveItem.Enabled = modified;
            fileSaveAsItem.Enabled = modified;
        }

        private void tablesListBox_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            using (new UpdateHelper(primaryKeyListView))
            {
                primaryKeyListView.Items.Clear();
                string table = tablesListBox.SelectedItem.ToString();
                MSI.View view =
                    IzFree.Application.ExecView(m_application.Project.Database,
                    "SELECT " + PrimaryKeys(table) + " FROM `" + table + "`");
                for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                {
                    primaryKeyListView.Items.Add(rec.GetString(1));
                }
                view.Close();
            }
        
        }

        private void fileSaveItem_Click(object sender, System.EventArgs e)
        {
            m_application.SaveProject();
            Modified = false;
        }

        private void fileSaveAsItem_Click(object sender, System.EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "Setup Databases (*.msi)|*.msi|" +
                "Merge Modules (*.msm)|*.msm|" +
                "Patch Creation Parameters (*.pcp)|*.pcp|" +
                "ICE Databases (*.cub)|*.cub";
            dlg.FilterIndex = 0;
            dlg.OverwritePrompt = true;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                m_application.SaveProjectAs(dlg.FileName);
                Modified = false;
            }
        }

        private void fileCloseItem_Click(object sender, System.EventArgs e)
        {
            if (Modified)
            {
                // prompt to save first
                if (DialogResult.OK == MessageBox.Show(
                    "The package has been modified.  Do you want to save " +
                    "your changes before closing?", "Save Changes",
                    MessageBoxButtons.YesNo))
                {
                    m_application.SaveProject();
                }
            }
            m_application.CloseProject();
            DatabaseOpen(false);
        }
	}
}
