using System;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using MSI = Pahvant.MSI;

namespace IzFree
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
    [System.ComponentModel.DesignerCategory("Form")]
    public class MainForm : System.Windows.Forms.Form
    {
        #region Forms Components
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
        private System.Windows.Forms.MenuItem toolsMenu;
        private System.Windows.Forms.MenuItem toolScanDirectoryItem;
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
        private System.Windows.Forms.MenuItem toolExtractCOMItem;
        private System.Windows.Forms.MenuItem fileCloseItem;
        private System.Windows.Forms.MenuItem fileSeparatorItem;
        private System.Windows.Forms.MenuItem fileSummaryInformationItem;
        private System.Windows.Forms.TabPage dialogPreviewTab;
        private System.Windows.Forms.Label dialogsLabel;
        private System.Windows.Forms.ListBox dialogsListBox;
        private System.Windows.Forms.ComboBox actionsComboBox;
        private System.Windows.Forms.GroupBox standardDialogsGroupBox;
        private System.Windows.Forms.Label fatalErrorLabel;
        private System.Windows.Forms.Label userExitLabel;
        private System.Windows.Forms.Label exitLabel;
        private System.Windows.Forms.LinkLabel fatalErrorLinkLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.LinkLabel userExitLinkLabel;
        private System.Windows.Forms.LinkLabel exitLinkLabel;
        private System.Windows.Forms.LinkLabel errorDialogLinkLabel;
        private System.Windows.Forms.Label eventsLabel;
        private System.Windows.Forms.ListBox eventsListBox;
        private System.Windows.Forms.GroupBox eventDetailGroupBox;
        private System.Windows.Forms.Label eventNameLabel;
        private System.Windows.Forms.Label eventOrderingLabel;
        private System.Windows.Forms.Label eventConditionLabel;
        private System.Windows.Forms.Label eventNameValueLabel;
        private System.Windows.Forms.Label eventOrderingValueLabel;
        private System.Windows.Forms.Label eventConditionValueLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button showButton;
        private System.Windows.Forms.Button hideButton;
        private System.Windows.Forms.Button cloneButton;
        private System.Windows.Forms.MenuItem menuItem1;
        private System.Windows.Forms.MenuItem groupPolicyItem;
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.Container components = null;
        #endregion

        public MainForm()
        {
            InitializeComponent();
        }

        #region Dispose
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (components != null) 
                {
                    components.Dispose();
                }
            }
            base.Dispose(disposing);
        }
        #endregion

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
            this.toolsMenu = new System.Windows.Forms.MenuItem();
            this.toolScanDirectoryItem = new System.Windows.Forms.MenuItem();
            this.toolExtractCOMItem = new System.Windows.Forms.MenuItem();
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
            this.dialogPreviewTab = new System.Windows.Forms.TabPage();
            this.cloneButton = new System.Windows.Forms.Button();
            this.hideButton = new System.Windows.Forms.Button();
            this.showButton = new System.Windows.Forms.Button();
            this.eventDetailGroupBox = new System.Windows.Forms.GroupBox();
            this.eventConditionValueLabel = new System.Windows.Forms.Label();
            this.eventOrderingValueLabel = new System.Windows.Forms.Label();
            this.eventNameValueLabel = new System.Windows.Forms.Label();
            this.eventConditionLabel = new System.Windows.Forms.Label();
            this.eventOrderingLabel = new System.Windows.Forms.Label();
            this.eventNameLabel = new System.Windows.Forms.Label();
            this.eventsListBox = new System.Windows.Forms.ListBox();
            this.eventsLabel = new System.Windows.Forms.Label();
            this.standardDialogsGroupBox = new System.Windows.Forms.GroupBox();
            this.errorDialogLinkLabel = new System.Windows.Forms.LinkLabel();
            this.exitLinkLabel = new System.Windows.Forms.LinkLabel();
            this.userExitLinkLabel = new System.Windows.Forms.LinkLabel();
            this.label2 = new System.Windows.Forms.Label();
            this.exitLabel = new System.Windows.Forms.Label();
            this.userExitLabel = new System.Windows.Forms.Label();
            this.fatalErrorLinkLabel = new System.Windows.Forms.LinkLabel();
            this.fatalErrorLabel = new System.Windows.Forms.Label();
            this.actionsComboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.dialogsListBox = new System.Windows.Forms.ListBox();
            this.dialogsLabel = new System.Windows.Forms.Label();
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.groupPolicyItem = new System.Windows.Forms.MenuItem();
            this.projectTabControl.SuspendLayout();
            this.tablesTab.SuspendLayout();
            this.featuresTab.SuspendLayout();
            this.dialogPreviewTab.SuspendLayout();
            this.eventDetailGroupBox.SuspendLayout();
            this.standardDialogsGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainMenu
            // 
            this.mainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                     this.fileMenu,
                                                                                     this.editMenu,
                                                                                     this.toolsMenu,
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
            // toolsMenu
            // 
            this.toolsMenu.Index = 2;
            this.toolsMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                      this.toolScanDirectoryItem,
                                                                                      this.toolExtractCOMItem,
                                                                                      this.menuItem1,
                                                                                      this.groupPolicyItem});
            this.toolsMenu.Text = "Tools";
            // 
            // toolScanDirectoryItem
            // 
            this.toolScanDirectoryItem.Enabled = false;
            this.toolScanDirectoryItem.Index = 0;
            this.toolScanDirectoryItem.Text = "Scan &Directory for Components...";
            this.toolScanDirectoryItem.Click += new System.EventHandler(this.toolScanDirectoryItem_Click);
            // 
            // toolExtractCOMItem
            // 
            this.toolExtractCOMItem.Enabled = false;
            this.toolExtractCOMItem.Index = 1;
            this.toolExtractCOMItem.Text = "Extract COM Registration...";
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
            this.projectTabControl.Controls.Add(this.dialogPreviewTab);
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
            this.tableRowPropertyGrid.HelpVisible = false;
            this.tableRowPropertyGrid.LargeButtons = false;
            this.tableRowPropertyGrid.LineColor = System.Drawing.SystemColors.ScrollBar;
            this.tableRowPropertyGrid.Location = new System.Drawing.Point(288, 8);
            this.tableRowPropertyGrid.Name = "tableRowPropertyGrid";
            this.tableRowPropertyGrid.Size = new System.Drawing.Size(296, 446);
            this.tableRowPropertyGrid.TabIndex = 2;
            this.tableRowPropertyGrid.Text = "PropertyGrid";
            this.tableRowPropertyGrid.ToolbarVisible = false;
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
            // dialogPreviewTab
            // 
            this.dialogPreviewTab.Controls.Add(this.cloneButton);
            this.dialogPreviewTab.Controls.Add(this.hideButton);
            this.dialogPreviewTab.Controls.Add(this.showButton);
            this.dialogPreviewTab.Controls.Add(this.eventDetailGroupBox);
            this.dialogPreviewTab.Controls.Add(this.eventsListBox);
            this.dialogPreviewTab.Controls.Add(this.eventsLabel);
            this.dialogPreviewTab.Controls.Add(this.standardDialogsGroupBox);
            this.dialogPreviewTab.Controls.Add(this.actionsComboBox);
            this.dialogPreviewTab.Controls.Add(this.label1);
            this.dialogPreviewTab.Controls.Add(this.dialogsListBox);
            this.dialogPreviewTab.Controls.Add(this.dialogsLabel);
            this.dialogPreviewTab.Location = new System.Drawing.Point(4, 22);
            this.dialogPreviewTab.Name = "dialogPreviewTab";
            this.dialogPreviewTab.Size = new System.Drawing.Size(596, 468);
            this.dialogPreviewTab.TabIndex = 6;
            this.dialogPreviewTab.Text = "UI Preview";
            // 
            // cloneButton
            // 
            this.cloneButton.Enabled = false;
            this.cloneButton.Location = new System.Drawing.Point(208, 80);
            this.cloneButton.Name = "cloneButton";
            this.cloneButton.Size = new System.Drawing.Size(80, 23);
            this.cloneButton.TabIndex = 11;
            this.cloneButton.Text = "Clone...";
            this.cloneButton.Click += new System.EventHandler(this.cloneButton_Click);
            // 
            // hideButton
            // 
            this.hideButton.Enabled = false;
            this.hideButton.Location = new System.Drawing.Point(208, 56);
            this.hideButton.Name = "hideButton";
            this.hideButton.Size = new System.Drawing.Size(80, 23);
            this.hideButton.TabIndex = 10;
            this.hideButton.Text = "Hide";
            this.hideButton.Click += new System.EventHandler(this.hideButton_Click);
            // 
            // showButton
            // 
            this.showButton.Location = new System.Drawing.Point(208, 32);
            this.showButton.Name = "showButton";
            this.showButton.Size = new System.Drawing.Size(80, 23);
            this.showButton.TabIndex = 9;
            this.showButton.Text = "Show";
            this.showButton.Click += new System.EventHandler(this.showButton_Click);
            // 
            // eventDetailGroupBox
            // 
            this.eventDetailGroupBox.Controls.Add(this.eventConditionValueLabel);
            this.eventDetailGroupBox.Controls.Add(this.eventOrderingValueLabel);
            this.eventDetailGroupBox.Controls.Add(this.eventNameValueLabel);
            this.eventDetailGroupBox.Controls.Add(this.eventConditionLabel);
            this.eventDetailGroupBox.Controls.Add(this.eventOrderingLabel);
            this.eventDetailGroupBox.Controls.Add(this.eventNameLabel);
            this.eventDetailGroupBox.Location = new System.Drawing.Point(272, 240);
            this.eventDetailGroupBox.Name = "eventDetailGroupBox";
            this.eventDetailGroupBox.Size = new System.Drawing.Size(312, 208);
            this.eventDetailGroupBox.TabIndex = 8;
            this.eventDetailGroupBox.TabStop = false;
            this.eventDetailGroupBox.Text = "Event Detail";
            // 
            // eventConditionValueLabel
            // 
            this.eventConditionValueLabel.Location = new System.Drawing.Point(72, 88);
            this.eventConditionValueLabel.Name = "eventConditionValueLabel";
            this.eventConditionValueLabel.Size = new System.Drawing.Size(232, 112);
            this.eventConditionValueLabel.TabIndex = 10;
            this.eventConditionValueLabel.Text = "event condition";
            // 
            // eventOrderingValueLabel
            // 
            this.eventOrderingValueLabel.Location = new System.Drawing.Point(72, 56);
            this.eventOrderingValueLabel.Name = "eventOrderingValueLabel";
            this.eventOrderingValueLabel.Size = new System.Drawing.Size(232, 24);
            this.eventOrderingValueLabel.TabIndex = 9;
            this.eventOrderingValueLabel.Text = "event order";
            // 
            // eventNameValueLabel
            // 
            this.eventNameValueLabel.Location = new System.Drawing.Point(72, 24);
            this.eventNameValueLabel.Name = "eventNameValueLabel";
            this.eventNameValueLabel.Size = new System.Drawing.Size(232, 24);
            this.eventNameValueLabel.TabIndex = 8;
            this.eventNameValueLabel.Text = "event name";
            // 
            // eventConditionLabel
            // 
            this.eventConditionLabel.Location = new System.Drawing.Point(8, 88);
            this.eventConditionLabel.Name = "eventConditionLabel";
            this.eventConditionLabel.Size = new System.Drawing.Size(56, 24);
            this.eventConditionLabel.TabIndex = 7;
            this.eventConditionLabel.Text = "Condition:";
            this.eventConditionLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // eventOrderingLabel
            // 
            this.eventOrderingLabel.Location = new System.Drawing.Point(8, 56);
            this.eventOrderingLabel.Name = "eventOrderingLabel";
            this.eventOrderingLabel.Size = new System.Drawing.Size(56, 24);
            this.eventOrderingLabel.TabIndex = 6;
            this.eventOrderingLabel.Text = "Ordering:";
            this.eventOrderingLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // eventNameLabel
            // 
            this.eventNameLabel.Location = new System.Drawing.Point(8, 24);
            this.eventNameLabel.Name = "eventNameLabel";
            this.eventNameLabel.Size = new System.Drawing.Size(56, 24);
            this.eventNameLabel.TabIndex = 5;
            this.eventNameLabel.Text = "Event:";
            this.eventNameLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // eventsListBox
            // 
            this.eventsListBox.Location = new System.Drawing.Point(8, 264);
            this.eventsListBox.Name = "eventsListBox";
            this.eventsListBox.Size = new System.Drawing.Size(248, 186);
            this.eventsListBox.TabIndex = 7;
            this.eventsListBox.DoubleClick += new System.EventHandler(this.eventsListBox_DoubleClick);
            this.eventsListBox.SelectedIndexChanged += new System.EventHandler(this.eventsListBox_SelectedIndexChanged);
            // 
            // eventsLabel
            // 
            this.eventsLabel.Location = new System.Drawing.Point(8, 240);
            this.eventsLabel.Name = "eventsLabel";
            this.eventsLabel.Size = new System.Drawing.Size(100, 16);
            this.eventsLabel.TabIndex = 6;
            this.eventsLabel.Text = "Events:";
            // 
            // standardDialogsGroupBox
            // 
            this.standardDialogsGroupBox.Controls.Add(this.errorDialogLinkLabel);
            this.standardDialogsGroupBox.Controls.Add(this.exitLinkLabel);
            this.standardDialogsGroupBox.Controls.Add(this.userExitLinkLabel);
            this.standardDialogsGroupBox.Controls.Add(this.label2);
            this.standardDialogsGroupBox.Controls.Add(this.exitLabel);
            this.standardDialogsGroupBox.Controls.Add(this.userExitLabel);
            this.standardDialogsGroupBox.Controls.Add(this.fatalErrorLinkLabel);
            this.standardDialogsGroupBox.Controls.Add(this.fatalErrorLabel);
            this.standardDialogsGroupBox.Location = new System.Drawing.Point(304, 64);
            this.standardDialogsGroupBox.Name = "standardDialogsGroupBox";
            this.standardDialogsGroupBox.Size = new System.Drawing.Size(280, 152);
            this.standardDialogsGroupBox.TabIndex = 5;
            this.standardDialogsGroupBox.TabStop = false;
            this.standardDialogsGroupBox.Text = "Standard Dialogs";
            // 
            // errorDialogLinkLabel
            // 
            this.errorDialogLinkLabel.Location = new System.Drawing.Point(104, 120);
            this.errorDialogLinkLabel.Name = "errorDialogLinkLabel";
            this.errorDialogLinkLabel.Size = new System.Drawing.Size(168, 24);
            this.errorDialogLinkLabel.TabIndex = 7;
            this.errorDialogLinkLabel.TabStop = true;
            this.errorDialogLinkLabel.Text = "error dialog";
            this.errorDialogLinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.errorDialogLinkLabel_LinkClicked);
            // 
            // exitLinkLabel
            // 
            this.exitLinkLabel.Location = new System.Drawing.Point(104, 88);
            this.exitLinkLabel.Name = "exitLinkLabel";
            this.exitLinkLabel.Size = new System.Drawing.Size(168, 24);
            this.exitLinkLabel.TabIndex = 6;
            this.exitLinkLabel.TabStop = true;
            this.exitLinkLabel.Text = "exit";
            this.exitLinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.exitLinkLabel_LinkClicked);
            // 
            // userExitLinkLabel
            // 
            this.userExitLinkLabel.Location = new System.Drawing.Point(104, 56);
            this.userExitLinkLabel.Name = "userExitLinkLabel";
            this.userExitLinkLabel.Size = new System.Drawing.Size(168, 24);
            this.userExitLinkLabel.TabIndex = 5;
            this.userExitLinkLabel.TabStop = true;
            this.userExitLinkLabel.Text = "user exit";
            this.userExitLinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.userExitLinkLabel_LinkClicked);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(8, 120);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(88, 24);
            this.label2.TabIndex = 4;
            this.label2.Text = "[ErrorDialog]";
            this.label2.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // exitLabel
            // 
            this.exitLabel.Location = new System.Drawing.Point(8, 88);
            this.exitLabel.Name = "exitLabel";
            this.exitLabel.Size = new System.Drawing.Size(88, 24);
            this.exitLabel.TabIndex = 3;
            this.exitLabel.Text = "Exit (-1):";
            this.exitLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // userExitLabel
            // 
            this.userExitLabel.Location = new System.Drawing.Point(8, 56);
            this.userExitLabel.Name = "userExitLabel";
            this.userExitLabel.Size = new System.Drawing.Size(88, 24);
            this.userExitLabel.TabIndex = 2;
            this.userExitLabel.Text = "User Exit (-2):";
            this.userExitLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // fatalErrorLinkLabel
            // 
            this.fatalErrorLinkLabel.Location = new System.Drawing.Point(104, 24);
            this.fatalErrorLinkLabel.Name = "fatalErrorLinkLabel";
            this.fatalErrorLinkLabel.Size = new System.Drawing.Size(168, 24);
            this.fatalErrorLinkLabel.TabIndex = 1;
            this.fatalErrorLinkLabel.TabStop = true;
            this.fatalErrorLinkLabel.Text = "fatal error";
            this.fatalErrorLinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.fatalErrorLinkLabel_LinkClicked);
            // 
            // fatalErrorLabel
            // 
            this.fatalErrorLabel.Location = new System.Drawing.Point(8, 24);
            this.fatalErrorLabel.Name = "fatalErrorLabel";
            this.fatalErrorLabel.Size = new System.Drawing.Size(88, 24);
            this.fatalErrorLabel.TabIndex = 0;
            this.fatalErrorLabel.Text = "Fatal Error (-3):";
            this.fatalErrorLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // actionsComboBox
            // 
            this.actionsComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.actionsComboBox.Location = new System.Drawing.Point(304, 32);
            this.actionsComboBox.Name = "actionsComboBox";
            this.actionsComboBox.Size = new System.Drawing.Size(184, 21);
            this.actionsComboBox.TabIndex = 3;
            this.actionsComboBox.SelectedIndexChanged += new System.EventHandler(this.actionsComboBox_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(304, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(152, 16);
            this.label1.TabIndex = 2;
            this.label1.Text = "Install UI Sequence Dialogs:";
            // 
            // dialogsListBox
            // 
            this.dialogsListBox.Location = new System.Drawing.Point(8, 32);
            this.dialogsListBox.Name = "dialogsListBox";
            this.dialogsListBox.Size = new System.Drawing.Size(184, 186);
            this.dialogsListBox.TabIndex = 1;
            this.dialogsListBox.SelectedIndexChanged += new System.EventHandler(this.dialogsListBox_SelectedIndexChanged);
            // 
            // dialogsLabel
            // 
            this.dialogsLabel.Location = new System.Drawing.Point(8, 8);
            this.dialogsLabel.Name = "dialogsLabel";
            this.dialogsLabel.Size = new System.Drawing.Size(100, 16);
            this.dialogsLabel.TabIndex = 0;
            this.dialogsLabel.Text = "Dialogs:";
            // 
            // menuItem1
            // 
            this.menuItem1.Index = 2;
            this.menuItem1.Text = "-";
            // 
            // groupPolicyItem
            // 
            this.groupPolicyItem.Index = 3;
            this.groupPolicyItem.Text = "System Group Policy";
            this.groupPolicyItem.Click += new System.EventHandler(this.groupPolicyItem_Click);
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
            this.dialogPreviewTab.ResumeLayout(false);
            this.eventDetailGroupBox.ResumeLayout(false);
            this.standardDialogsGroupBox.ResumeLayout(false);
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

        #region Private Methods
        private MSI.View ExecView(string sql)
        {
            return Application.ExecView(Database, sql);
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
        private void DatabaseOpen(bool openNotClosed)
        {
            fileCloseItem.Enabled = openNotClosed;
            fileSummaryInformationItem.Enabled = openNotClosed;
            toolScanDirectoryItem.Enabled = openNotClosed;
            toolExtractCOMItem.Enabled = openNotClosed;
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

        private void NewDatabase()
        {
            PopulateTabs();
            DatabaseOpen(true);
        }

        private void PopulateComponentsTab()
        {
            Debug.WriteLine("\nComponents:");
            using (MSI.View view = ExecView(
                       "SELECT `Component`,`ComponentId`,`Directory_`," +
                       "`Attributes`,`Condition`,`KeyPath` FROM `Component`" +
                       " ORDER BY `Component`"))
            {
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
        }

        private void PopulateFeaturesTab()
        {
            ArrayList roots = new ArrayList();
            Hashtable tree = new Hashtable();
            using (MSI.View view = ExecView(
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
                    rec.Dispose();
                }
                view.Close();
            }

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

        private void PopulateFileSystemTab()
        {
            Debug.WriteLine("\nFiles:");
            using (MSI.View view = ExecView(
                       "SELECT `File`,`Component_`,`FileName`,`FileSize`," +
                       "`Version`,`Language`,`Attributes`,`Sequence` " +
                       "FROM `File` ORDER BY `File`"))
            {
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
        }

        private void PopulateRegistryTab()
        {
            using (MSI.View view = ExecView(
                       "SELECT `Registry`,`Root`,`Key`,`Name`,`Value`,`Component_`" +
                       " FROM `Registry` ORDER BY `Registry`"))
            {
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
        }

        private void PopulateTablesTab()
        {
            using (new UpdateHelper(tablesListBox))
            {
                tablesListBox.Items.Clear();
                using (MSI.View view = ExecView(
                           "SELECT * FROM `_Tables` ORDER BY `Name`"))
                {
                    for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                    {
                        tablesListBox.Items.Add(rec.GetString(1));
                        rec.Dispose();
                    }
                    view.Close();
                }
            }
        }

        private string GetUIAction(int sequence)
        {
            using (MSI.View view = ExecView(
                       "SELECT `Action` FROM `InstallUISequence` WHERE " +
                       "`Sequence`=" + sequence.ToString()))
            {
                MSI.Record rec = view.Fetch();
                view.Close();
                if (rec != null)
                {
                    string action = rec.GetString(1);
                    rec.Dispose();
                    return action;
                }
            }
            return "";
        }

        private void LoadStandardDialogs()
        {
            if (Project.TableExists("InstallUISequence"))
            {
                fatalErrorLinkLabel.Text = GetUIAction(-3);
                userExitLinkLabel.Text = GetUIAction(-2);
                exitLinkLabel.Text = GetUIAction(-1);
            }
            if (Project.TableExists("Property"))
            {
                errorDialogLinkLabel.Text = Project.GetProperty("ErrorDialog");
            }
        }

        private void LoadWizards(ArrayList dialogs)
        {
            ArrayList uiDialogs = new ArrayList();
            using (MSI.View view = ExecView(
                       "SELECT `Action` FROM `InstallUISequence` WHERE " +
                       "`Sequence` >= 0 ORDER BY `Sequence`"))
            {
                for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                {
                    if (dialogs.Contains(rec.GetString(1)))
                    {
                        uiDialogs.Add(rec.GetString(1));
                    }
                    rec.Dispose();
                }
                view.Close();
            }
            for (int i = 0; i < uiDialogs.Count; i++)
            {
                actionsComboBox.Items.Add(uiDialogs[i]);
            }
        }

        private void PopulateDialogsTab()
        {
            dialogsListBox.Items.Clear();
            actionsComboBox.Items.Clear();
            fatalErrorLinkLabel.Text = "";
            userExitLinkLabel.Text = "";
            exitLinkLabel.Text = "";
            errorDialogLinkLabel.Text = "";

            eventsListBox.Items.Clear();
            eventNameValueLabel.Text = "";
            eventOrderingValueLabel.Text = "";
            eventConditionValueLabel.Text = "";

            if (Project.TableExists("Dialog"))
            {
                LoadStandardDialogs();
                ArrayList dialogs = new ArrayList();
                using (new UpdateHelper(dialogsListBox))
                {
                    dialogsListBox.Items.Clear();
                    using (MSI.View view = ExecView(
                               "SELECT `Dialog` FROM `Dialog` ORDER BY `Dialog`"))
                    {
                        for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                        {
                            dialogs.Add(rec.GetString(1));
                            rec.Dispose();
                        }
                        view.Close();
                    }
                    dialogs.Sort();
                    dialogsListBox.Items.AddRange(dialogs.ToArray());
                }
                LoadWizards(dialogs);
            }
        }

        private void PopulateTabs()
        {
            PopulateTablesTab();
            PopulateFeaturesTab();
            PopulateComponentsTab();
            PopulateFileSystemTab();
            PopulateRegistryTab();
            PopulateDialogsTab();
        }

        public static string SqlQuote(string text)
        {
            return "`" + text + "`";
        }

        private string PrimaryKeys(string table)
        {
            string[] keys = Database.PrimaryKeys(table);
            string result = SqlQuote(keys[0]);
            for (int i = 1; i < keys.Length; i++)
            {
                result += "," + SqlQuote(keys[i]);
            }
            return result;
        }

        private void SetTitle()
        {
            Text = "izfree 2.0";
            if (Project != null)
            {
                Text += " - " + (Modified ? "* " : "") +
                    Project.Filename;
            }
        }

        private void ShowModified(bool modified)
        {
            fileSaveItem.Enabled = modified;
            fileSaveAsItem.Enabled = modified;
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
                projectTabControl.TabPages.Add(dialogPreviewTab);
            }
            else
            {
                projectTabControl.TabPages.Remove(tablesTab);
                projectTabControl.TabPages.Remove(featuresTab);
                projectTabControl.TabPages.Remove(componentsTab);
                projectTabControl.TabPages.Remove(fileSystemTab);
                projectTabControl.TabPages.Remove(registryTab);
                projectTabControl.TabPages.Remove(dialogPreviewTab);
            }
        }

        private void CloneDialogRows(string table, string insertQuery,
            string parent, string clone, string column)
        {
            ArrayList records = new ArrayList();
            // gather source records
            using (MSI.View view = ExecView("SELECT * FROM `" + table +
                       "` WHERE `" + table + "`.`" + column + "` = '" +
                       parent + "'"))
            {
                for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                {
                    rec.SetString(1, clone);
                    records.Add(rec);
                }
                view.Close();
            }

            // insert cloned records
            using (MSI.View view = Database.OpenView(
                       "INSERT INTO `" + table + "` " + insertQuery))
            {
                for (int i = 0; i < records.Count; i++)
                {
                    MSI.Record rec = records[i] as MSI.Record;
                    view.Execute(rec);
                    rec.Dispose();
                }
                view.Close();
            }
        }

        private void CloneDialog(string dialog, string clone)
        {
            CloneDialogRows("Dialog",
                "(`Dialog`,`HCentering`,`VCentering`,`Width`,`Height`," +
                "`Attributes`,`Title`,`Control_First`,`Control_Default`," +
                "`Control_Cancel`) VALUES (?,?,?,?,?,?,?,?,?,?)",
                dialog, clone, "Dialog");
        }

        private void CloneControls(string dialog, string clone)
        {
            CloneDialogRows("Control",
                "(`Dialog_`,`Control`,`Type`,`X`,`Y`,`Width`,`Height`," +
                "`Attributes`,`Property`,`Text`,`Control_Next`,`Help`) " +
                "VALUES (?,?,?,?,?,?,?,?,?,?,?,?)",
                dialog, clone, "Dialog_");
        }

        private void CloneControlConditions(string dialog, string clone)
        {
            CloneDialogRows("ControlCondition",
                "(`Dialog_`,`Control_`,`Action`,`Condition`) VALUES (?,?,?,?)",
                dialog, clone, "Dialog_");
        }

        private void CloneControlEvents(string dialog, string clone)
        {
            CloneDialogRows("ControlEvent",
                "(`Dialog_`,`Control_`,`Event`,`Argument`,`Condition`,`Ordering`) " +
                "VALUES (?,?,?,?,?,?)",
                dialog, clone, "Dialog_");
        }

        private void CloneEventMappings(string dialog, string clone)
        {
            CloneDialogRows("EventMapping",
                "(`Dialog_`,`Control_`,`Event`,`Attribute`) VALUES (?,?,?,?)",
                dialog, clone, "Dialog_");
        }

        private void Preview()
        {
            string dialog = dialogsListBox.SelectedItem as string;
            if (m_previewEnabled && (m_currentDialog != dialog))
            {
                m_currentDialog = dialog;
                m_preview.PreviewDialog(m_currentDialog);
                Activate();
            }
        }

        private static string NullInteger(MSI.Record rec, int field)
        {
            return rec.IsNull(field) ? "" : rec.GetInteger(field).ToString();
        }
        private static string NullString(MSI.Record rec, int field)
        {
            return rec.IsNull(field) ? "" : rec.GetString(field);
        }
        #endregion

        #region Event Handlers
        #region Main Form
        private void MainForm_Load(object sender, System.EventArgs e)
        {
            ShowProjectTabs(false);
        }
        #endregion

        #region File Menu
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
        #endregion

        #region Edit Menu
        private void editCopyNewGuidItem_Click(object sender, System.EventArgs e)
        {
            Clipboard.SetDataObject(Application.NewGuid());
        }

        private void editPasteNewGuidItem_Click(object sender, System.EventArgs e)
        {
            if (this.ActiveControl is TextBox)
            {
                this.ActiveControl.Text = Application.NewGuid();
            }
        }
        #endregion

        #region Tools Menu
        private void toolScanDirectoryItem_Click(object sender, System.EventArgs e)
        {
            using (NewComponentsForm dlg =
                       new NewComponentsForm(Project))
            {
                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    // add components
                    dlg.Commit();
                    Modified = true;
                }
            }
        }
        private void groupPolicyItem_Click(object sender, System.EventArgs e)
        {
            // launch mmc gpedit.msc (and preselect windows installer node?)
        }
        #endregion

        #region Tables View
        private void primaryKeyListView_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            if (primaryKeyListView.SelectedItems.Count > 0)
            {

            }
        }

        private void tablesListBox_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            using (new UpdateHelper(primaryKeyListView))
            {
                primaryKeyListView.Items.Clear();
                string table = tablesListBox.SelectedItem.ToString();
                MSI.View view =
                    Application.ExecView(Project.Database,
                    "SELECT " + PrimaryKeys(table) + " FROM `" + table + "`");
                for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                {
                    primaryKeyListView.Items.Add(rec.GetString(1));
                }
                view.Close();
            }
        
        }
        #endregion

        #region Dialog Preview
        #region Link Labels
        private void LinkDialog(LinkLabel control)
        {
            dialogsListBox.SelectedIndex = dialogsListBox.FindString(control.Text);
        }
        private void fatalErrorLinkLabel_LinkClicked(object sender, System.Windows.Forms.LinkLabelLinkClickedEventArgs e)
        {
            LinkDialog(fatalErrorLinkLabel);
        }

        private void userExitLinkLabel_LinkClicked(object sender, System.Windows.Forms.LinkLabelLinkClickedEventArgs e)
        {
            LinkDialog(userExitLinkLabel);
        }

        private void exitLinkLabel_LinkClicked(object sender, System.Windows.Forms.LinkLabelLinkClickedEventArgs e)
        {
            LinkDialog(exitLinkLabel);
        }

        private void errorDialogLinkLabel_LinkClicked(object sender, System.Windows.Forms.LinkLabelLinkClickedEventArgs e)
        {
            LinkDialog(errorDialogLinkLabel);
        }
        #endregion

        private void actionsComboBox_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            dialogsListBox.SelectedIndex = dialogsListBox.FindString(
                actionsComboBox.SelectedItem as string);
        }

        private void dialogsListBox_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            cloneButton.Enabled = true;

            eventsListBox.Items.Clear();
            eventNameValueLabel.Text = "";
            eventOrderingValueLabel.Text = "";
            eventConditionValueLabel.Text = "";

            // populate the events list box
            // need to handle the case where we have the following idiom:
            //
            //      Control [Property1] Target1     Condition1          1
            //      Control [Property1] Target2     Condition2          2
            //      Control [Property2] Target3     Condition3          3
            //      Control [Property2] Target4     Condition4          4
            //      Control NewDialog   [Property1] DialogCondition1    5
            //      Control NewDialog   [Property2] DialogCondition2    6
            //      Control NewDialog   [Property2] DialogCondition3    7
            //
            // Convert to:
            //
            //      Control Target1 Property1=Target1 AND Condition1 AND DialogCondition1     5
            //      Control Target2 Property1=Target2 AND Condition2 AND DialogCondition1     5
            //      Control Target3 Property2=Target3 AND Condition3 AND DialogCondition2     6
            //      Control Target4 Property2=Target3 AND Condition4 AND DialogCondition2     6
            //      Control Target3 Property2=Target3 AND Condition3 AND DialogCondition3     7
            //      Control Target4 Property2=Target4 AND Condition4 AND DialogCondition3     7
            //
            // If no SetProperty events are in the ControlEvent table, then
            // the formatted property alone can take you to any dialog.  However
            // 'Left[Property1]Mid[Property2]Right' can only take you to dialogs that end in the
            // containing the given literal text, in order.  This can be used
            // to filter down the possible list of dialogs from all dialogs
            //
            string dlg = dialogsListBox.SelectedItem as string;
            using (MSI.View view = ExecView(
                "SELECT `Control_`,`Event`,`Argument`,`Condition`,`Ordering` " + 
                "FROM `ControlEvent` WHERE `Dialog_` = '" + dlg + "' " +
                "ORDER BY `Control_`,`Ordering`"))
            {
                for (MSI.Record rec = view.Fetch(); rec != null; rec = view.Fetch())
                {
                    string controlEvent = rec.GetString(2);
                    if ((controlEvent == "NewDialog") || (controlEvent == "SpawnDialog"))
                    {
                        string target = rec.GetString(3);
                        if (target.IndexOf('[') >= 0)
                        {
                            // target dialog key contains a formatted property
                            // skip for now
                        }
                        else
                        {
                            eventsListBox.Items.Add(rec.GetString(1) + " -> " + target);
                        }
                    }
                    else if (controlEvent.IndexOf('[') >= 0)
                    {
                        // event is formatting a property
                    }
                    rec.Dispose();
                }
            }

            Preview();
        }

        private void showButton_Click(object sender, System.EventArgs e)
        {
            m_previewEnabled = true;
            if (null == m_preview)
            {
                m_preview = Database.EnableUIPreview();
            }
            Preview();
            hideButton.Enabled = true;
        }

        private void hideButton_Click(object sender, System.EventArgs e)
        {
            m_previewEnabled = false;
            m_currentDialog = "";
            m_preview.PreviewDialog("");
            hideButton.Enabled = false;
            showButton.Focus();
        }

        private void eventsListBox_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            eventNameValueLabel.Text = "";
            eventOrderingValueLabel.Text = "";
            eventConditionValueLabel.Text = "";

            if (eventsListBox.SelectedIndex >= 0)
            {
                string dialog = dialogsListBox.SelectedItem as string;
                string[] pieces = (eventsListBox.SelectedItem as string).Split(new char[] { ' ' });
                using (MSI.View view = ExecView(
                           "SELECT `Condition`,`Ordering`,`Event` FROM " +
                           "`ControlEvent` WHERE `Dialog_`='" + dialog + "' " +
                           "AND `Control_`='" + pieces[0] + "' " +
                           "AND `Argument`='" + pieces[2] + "'"))
                {
                    MSI.Record rec = view.Fetch();
                    if (null == rec)
                    {
                        throw new InvalidOperationException("Didn't expect NULL result set from ControlEvent query");
                    }
                    eventNameValueLabel.Text = NullString(rec, 3);
                    eventOrderingValueLabel.Text = NullInteger(rec, 2);
                    eventConditionValueLabel.Text = NullString(rec, 1);
                    rec.Dispose();
                }
            }
        }

        private void eventsListBox_DoubleClick(object sender, System.EventArgs e)
        {
            string dialog = (eventsListBox.SelectedItem as string).
                Split(new char[] { ' ' })[2];
            dialogsListBox.SelectedIndex = dialogsListBox.FindString(dialog);
        }

        private void cloneButton_Click(object sender, System.EventArgs e)
        {
            string clone = "NewClone";
            string dialog = dialogsListBox.SelectedItem as string;
            CloneDialog(dialog, clone);
            CloneControls(dialog, clone);
            CloneControlConditions(dialog, clone);
            CloneControlEvents(dialog, clone);
            CloneEventMappings(dialog, clone);
            Modified = true;
            // refresh dialog list
        }
        #endregion
        #endregion

        #region Properties
        #region Project
        private Project Project
        {
            get { return m_application.Project; }
        }
        #endregion

        #region Database
        private MSI.Database Database
        {
            get { return Project.Database; }
        }
        #endregion

        #region Modified
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
        #endregion
        #endregion

        #region Private Instance Data
        Application m_application = new Application();
        private bool m_previewEnabled = false;
        private string m_currentDialog = "";
        private MSI.UIPreview m_preview = null;
        #endregion
    }
}
