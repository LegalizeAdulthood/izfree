using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace IzFree
{
	/// <summary>
	/// Summary description for NewPackageForm.
	/// </summary>
    [System.ComponentModel.DesignerCategory("Form")]
    public class NewPackageForm : System.Windows.Forms.Form
	{
        #region Form Components
        private System.Windows.Forms.Label templateDirectoryLabel;
        private System.Windows.Forms.TextBox templateDirectoryTextBox;
        private System.Windows.Forms.Button templateDirectoryBrowseButton;
        private System.Windows.Forms.Button createButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Label databaseFileNameLabel;
        private System.Windows.Forms.TextBox databaseFileNameTextBox;
        private System.Windows.Forms.Button databaseFileNameBrowseButton;
        private System.Windows.Forms.Label manufacturerLabel;
        private System.Windows.Forms.TextBox manufacturerTextBox;
        private System.Windows.Forms.Label productNameLabel;
        private System.Windows.Forms.TextBox productNameTextBox;
        private System.Windows.Forms.Label productVersionLabel;
        private System.Windows.Forms.TextBox productVersionTextBox;
        private System.Windows.Forms.ComboBox targetRootComboBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label productCodeLabel;
        private System.Windows.Forms.Label installationDirectoryLabel;
        private System.Windows.Forms.TextBox productCodeTextBox;
        private System.Windows.Forms.Button generateProductCodeButton;
        private System.Windows.Forms.Label packageCodeLabel;
        private System.Windows.Forms.TextBox packageCodeTextBox;
        private System.Windows.Forms.Button generatePackageCodeButton;
        private System.Windows.Forms.Label upgradeCodeLabel;
        private System.Windows.Forms.TextBox upgradeCodeTextBox;
        private System.Windows.Forms.Button generateUpgradeCodeButton;
        private System.Windows.Forms.TextBox targetDirectoryTextBox;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
        #endregion

		public NewPackageForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
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
            this.templateDirectoryLabel = new System.Windows.Forms.Label();
            this.databaseFileNameLabel = new System.Windows.Forms.Label();
            this.templateDirectoryTextBox = new System.Windows.Forms.TextBox();
            this.templateDirectoryBrowseButton = new System.Windows.Forms.Button();
            this.createButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.databaseFileNameTextBox = new System.Windows.Forms.TextBox();
            this.databaseFileNameBrowseButton = new System.Windows.Forms.Button();
            this.manufacturerLabel = new System.Windows.Forms.Label();
            this.manufacturerTextBox = new System.Windows.Forms.TextBox();
            this.productNameLabel = new System.Windows.Forms.Label();
            this.productNameTextBox = new System.Windows.Forms.TextBox();
            this.productVersionLabel = new System.Windows.Forms.Label();
            this.productVersionTextBox = new System.Windows.Forms.TextBox();
            this.installationDirectoryLabel = new System.Windows.Forms.Label();
            this.targetRootComboBox = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.targetDirectoryTextBox = new System.Windows.Forms.TextBox();
            this.productCodeLabel = new System.Windows.Forms.Label();
            this.productCodeTextBox = new System.Windows.Forms.TextBox();
            this.generateProductCodeButton = new System.Windows.Forms.Button();
            this.packageCodeLabel = new System.Windows.Forms.Label();
            this.packageCodeTextBox = new System.Windows.Forms.TextBox();
            this.generatePackageCodeButton = new System.Windows.Forms.Button();
            this.upgradeCodeLabel = new System.Windows.Forms.Label();
            this.upgradeCodeTextBox = new System.Windows.Forms.TextBox();
            this.generateUpgradeCodeButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // templateDirectoryLabel
            // 
            this.templateDirectoryLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.templateDirectoryLabel.Location = new System.Drawing.Point(64, 24);
            this.templateDirectoryLabel.Name = "templateDirectoryLabel";
            this.templateDirectoryLabel.Size = new System.Drawing.Size(168, 23);
            this.templateDirectoryLabel.TabIndex = 0;
            this.templateDirectoryLabel.Text = "Template Directory:";
            // 
            // databaseFileNameLabel
            // 
            this.databaseFileNameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.databaseFileNameLabel.Location = new System.Drawing.Point(64, 56);
            this.databaseFileNameLabel.Name = "databaseFileNameLabel";
            this.databaseFileNameLabel.Size = new System.Drawing.Size(168, 23);
            this.databaseFileNameLabel.TabIndex = 1;
            this.databaseFileNameLabel.Text = "Database File Name:";
            // 
            // templateDirectoryTextBox
            // 
            this.templateDirectoryTextBox.Location = new System.Drawing.Point(232, 24);
            this.templateDirectoryTextBox.Name = "templateDirectoryTextBox";
            this.templateDirectoryTextBox.Size = new System.Drawing.Size(312, 20);
            this.templateDirectoryTextBox.TabIndex = 2;
            this.templateDirectoryTextBox.Text = "";
            // 
            // templateDirectoryBrowseButton
            // 
            this.templateDirectoryBrowseButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.templateDirectoryBrowseButton.Location = new System.Drawing.Point(552, 24);
            this.templateDirectoryBrowseButton.Name = "templateDirectoryBrowseButton";
            this.templateDirectoryBrowseButton.Size = new System.Drawing.Size(24, 23);
            this.templateDirectoryBrowseButton.TabIndex = 3;
            this.templateDirectoryBrowseButton.Text = "...";
            this.templateDirectoryBrowseButton.Click += new System.EventHandler(this.templateDirectoryBrowseButton_Click);
            // 
            // createButton
            // 
            this.createButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.createButton.Location = new System.Drawing.Point(416, 352);
            this.createButton.Name = "createButton";
            this.createButton.TabIndex = 4;
            this.createButton.Text = "Create";
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(504, 352);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.TabIndex = 5;
            this.cancelButton.Text = "Cancel";
            // 
            // databaseFileNameTextBox
            // 
            this.databaseFileNameTextBox.Location = new System.Drawing.Point(232, 56);
            this.databaseFileNameTextBox.Name = "databaseFileNameTextBox";
            this.databaseFileNameTextBox.Size = new System.Drawing.Size(312, 20);
            this.databaseFileNameTextBox.TabIndex = 6;
            this.databaseFileNameTextBox.Text = "";
            // 
            // databaseFileNameBrowseButton
            // 
            this.databaseFileNameBrowseButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.databaseFileNameBrowseButton.Location = new System.Drawing.Point(552, 56);
            this.databaseFileNameBrowseButton.Name = "databaseFileNameBrowseButton";
            this.databaseFileNameBrowseButton.Size = new System.Drawing.Size(24, 23);
            this.databaseFileNameBrowseButton.TabIndex = 7;
            this.databaseFileNameBrowseButton.Text = "...";
            // 
            // manufacturerLabel
            // 
            this.manufacturerLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.manufacturerLabel.Location = new System.Drawing.Point(64, 88);
            this.manufacturerLabel.Name = "manufacturerLabel";
            this.manufacturerLabel.Size = new System.Drawing.Size(168, 23);
            this.manufacturerLabel.TabIndex = 8;
            this.manufacturerLabel.Text = "Manufacturer:";
            // 
            // manufacturerTextBox
            // 
            this.manufacturerTextBox.Location = new System.Drawing.Point(232, 88);
            this.manufacturerTextBox.Name = "manufacturerTextBox";
            this.manufacturerTextBox.Size = new System.Drawing.Size(312, 20);
            this.manufacturerTextBox.TabIndex = 9;
            this.manufacturerTextBox.Text = "";
            // 
            // productNameLabel
            // 
            this.productNameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.productNameLabel.Location = new System.Drawing.Point(64, 120);
            this.productNameLabel.Name = "productNameLabel";
            this.productNameLabel.Size = new System.Drawing.Size(168, 23);
            this.productNameLabel.TabIndex = 10;
            this.productNameLabel.Text = "Product Name:";
            // 
            // productNameTextBox
            // 
            this.productNameTextBox.Location = new System.Drawing.Point(232, 120);
            this.productNameTextBox.Name = "productNameTextBox";
            this.productNameTextBox.Size = new System.Drawing.Size(312, 20);
            this.productNameTextBox.TabIndex = 11;
            this.productNameTextBox.Text = "";
            // 
            // productVersionLabel
            // 
            this.productVersionLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.productVersionLabel.Location = new System.Drawing.Point(64, 152);
            this.productVersionLabel.Name = "productVersionLabel";
            this.productVersionLabel.Size = new System.Drawing.Size(168, 23);
            this.productVersionLabel.TabIndex = 12;
            this.productVersionLabel.Text = "Product Version:";
            // 
            // productVersionTextBox
            // 
            this.productVersionTextBox.Location = new System.Drawing.Point(232, 152);
            this.productVersionTextBox.Name = "productVersionTextBox";
            this.productVersionTextBox.Size = new System.Drawing.Size(80, 20);
            this.productVersionTextBox.TabIndex = 13;
            this.productVersionTextBox.Text = "";
            // 
            // installationDirectoryLabel
            // 
            this.installationDirectoryLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.installationDirectoryLabel.Location = new System.Drawing.Point(64, 184);
            this.installationDirectoryLabel.Name = "installationDirectoryLabel";
            this.installationDirectoryLabel.Size = new System.Drawing.Size(168, 23);
            this.installationDirectoryLabel.TabIndex = 14;
            this.installationDirectoryLabel.Text = "Installation Directory:";
            // 
            // targetRootComboBox
            // 
            this.targetRootComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.targetRootComboBox.Items.AddRange(new object[] {
                                                                    "AdminToolsFolder",
                                                                    "AppDataFolder",
                                                                    "CommonAppDataFolder",
                                                                    "CommonFilesFolder",
                                                                    "CommonFiles64Folder",
                                                                    "DesktopFolder",
                                                                    "FavoritesFolder",
                                                                    "FontsFolder",
                                                                    "LocalAppDataFolder",
                                                                    "MyPicturesFolder",
                                                                    "PersonalFolder",
                                                                    "ProgramFilesFolder",
                                                                    "ProgramFiles64Folder",
                                                                    "ProgramMenuFolder",
                                                                    "SendToFolder",
                                                                    "StartMenuFolder",
                                                                    "StartupFolder",
                                                                    "SystemFolder",
                                                                    "System16Folder",
                                                                    "System64Folder",
                                                                    "TempFolder",
                                                                    "TemplateFolder",
                                                                    "WindowsFolder",
                                                                    "WindowsVolume"});
            this.targetRootComboBox.Location = new System.Drawing.Point(232, 184);
            this.targetRootComboBox.Name = "targetRootComboBox";
            this.targetRootComboBox.Size = new System.Drawing.Size(144, 21);
            this.targetRootComboBox.TabIndex = 15;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(376, 184);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(16, 23);
            this.label2.TabIndex = 16;
            this.label2.Text = "/";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // targetDirectoryTextBox
            // 
            this.targetDirectoryTextBox.Location = new System.Drawing.Point(392, 184);
            this.targetDirectoryTextBox.Name = "targetDirectoryTextBox";
            this.targetDirectoryTextBox.Size = new System.Drawing.Size(136, 20);
            this.targetDirectoryTextBox.TabIndex = 17;
            this.targetDirectoryTextBox.Text = "";
            // 
            // productCodeLabel
            // 
            this.productCodeLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.productCodeLabel.Location = new System.Drawing.Point(64, 216);
            this.productCodeLabel.Name = "productCodeLabel";
            this.productCodeLabel.Size = new System.Drawing.Size(168, 23);
            this.productCodeLabel.TabIndex = 18;
            this.productCodeLabel.Text = "Product Code:";
            // 
            // productCodeTextBox
            // 
            this.productCodeTextBox.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.productCodeTextBox.Location = new System.Drawing.Point(232, 216);
            this.productCodeTextBox.Name = "productCodeTextBox";
            this.productCodeTextBox.Size = new System.Drawing.Size(272, 20);
            this.productCodeTextBox.TabIndex = 19;
            this.productCodeTextBox.Text = "";
            // 
            // generateProductCodeButton
            // 
            this.generateProductCodeButton.Location = new System.Drawing.Point(512, 216);
            this.generateProductCodeButton.Name = "generateProductCodeButton";
            this.generateProductCodeButton.Size = new System.Drawing.Size(64, 23);
            this.generateProductCodeButton.TabIndex = 20;
            this.generateProductCodeButton.Text = "Generate";
            this.generateProductCodeButton.Click += new System.EventHandler(this.generateProductCodeButton_Click);
            // 
            // packageCodeLabel
            // 
            this.packageCodeLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.packageCodeLabel.Location = new System.Drawing.Point(64, 248);
            this.packageCodeLabel.Name = "packageCodeLabel";
            this.packageCodeLabel.Size = new System.Drawing.Size(168, 23);
            this.packageCodeLabel.TabIndex = 21;
            this.packageCodeLabel.Text = "Package Code:";
            // 
            // packageCodeTextBox
            // 
            this.packageCodeTextBox.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.packageCodeTextBox.Location = new System.Drawing.Point(232, 248);
            this.packageCodeTextBox.Name = "packageCodeTextBox";
            this.packageCodeTextBox.Size = new System.Drawing.Size(272, 20);
            this.packageCodeTextBox.TabIndex = 22;
            this.packageCodeTextBox.Text = "";
            // 
            // generatePackageCodeButton
            // 
            this.generatePackageCodeButton.Location = new System.Drawing.Point(512, 248);
            this.generatePackageCodeButton.Name = "generatePackageCodeButton";
            this.generatePackageCodeButton.Size = new System.Drawing.Size(64, 23);
            this.generatePackageCodeButton.TabIndex = 23;
            this.generatePackageCodeButton.Text = "Generate";
            this.generatePackageCodeButton.Click += new System.EventHandler(this.generatePackageCodeButton_Click);
            // 
            // upgradeCodeLabel
            // 
            this.upgradeCodeLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.upgradeCodeLabel.Location = new System.Drawing.Point(64, 280);
            this.upgradeCodeLabel.Name = "upgradeCodeLabel";
            this.upgradeCodeLabel.Size = new System.Drawing.Size(168, 23);
            this.upgradeCodeLabel.TabIndex = 24;
            this.upgradeCodeLabel.Text = "Upgrade Code:";
            // 
            // upgradeCodeTextBox
            // 
            this.upgradeCodeTextBox.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.upgradeCodeTextBox.Location = new System.Drawing.Point(232, 280);
            this.upgradeCodeTextBox.Name = "upgradeCodeTextBox";
            this.upgradeCodeTextBox.Size = new System.Drawing.Size(272, 20);
            this.upgradeCodeTextBox.TabIndex = 25;
            this.upgradeCodeTextBox.Text = "";
            // 
            // generateUpgradeCodeButton
            // 
            this.generateUpgradeCodeButton.Location = new System.Drawing.Point(512, 280);
            this.generateUpgradeCodeButton.Name = "generateUpgradeCodeButton";
            this.generateUpgradeCodeButton.Size = new System.Drawing.Size(64, 23);
            this.generateUpgradeCodeButton.TabIndex = 26;
            this.generateUpgradeCodeButton.Tag = "";
            this.generateUpgradeCodeButton.Text = "Generate";
            this.generateUpgradeCodeButton.Click += new System.EventHandler(this.generateUpgradeCodeButton_Click);
            // 
            // NewPackageForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(592, 390);
            this.Controls.Add(this.generateUpgradeCodeButton);
            this.Controls.Add(this.upgradeCodeTextBox);
            this.Controls.Add(this.packageCodeTextBox);
            this.Controls.Add(this.productCodeTextBox);
            this.Controls.Add(this.targetDirectoryTextBox);
            this.Controls.Add(this.productVersionTextBox);
            this.Controls.Add(this.productNameTextBox);
            this.Controls.Add(this.manufacturerTextBox);
            this.Controls.Add(this.databaseFileNameTextBox);
            this.Controls.Add(this.templateDirectoryTextBox);
            this.Controls.Add(this.upgradeCodeLabel);
            this.Controls.Add(this.generatePackageCodeButton);
            this.Controls.Add(this.packageCodeLabel);
            this.Controls.Add(this.generateProductCodeButton);
            this.Controls.Add(this.productCodeLabel);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.targetRootComboBox);
            this.Controls.Add(this.installationDirectoryLabel);
            this.Controls.Add(this.productVersionLabel);
            this.Controls.Add(this.productNameLabel);
            this.Controls.Add(this.manufacturerLabel);
            this.Controls.Add(this.databaseFileNameBrowseButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.createButton);
            this.Controls.Add(this.templateDirectoryBrowseButton);
            this.Controls.Add(this.databaseFileNameLabel);
            this.Controls.Add(this.templateDirectoryLabel);
            this.Name = "NewPackageForm";
            this.Text = "Create A New Installation Package";
            this.Load += new System.EventHandler(this.NewPackageForm_Load);
            this.ResumeLayout(false);

        }
		#endregion

        #region Event Handlers
        private void templateDirectoryBrowseButton_Click(
            object sender, System.EventArgs e)
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            if (DialogResult.OK == dlg.ShowDialog())
            {
                templateDirectoryTextBox.Text = dlg.SelectedPath;
            }
        }

        private void NewPackageForm_Load(object sender, System.EventArgs e)
        {
            templateDirectoryTextBox.Text = StringSetting("templateDirectory",
                @"C:\Program Files\Microsoft SDK\Samples\SysMgmt\MSI\Database");
            databaseFileNameTextBox.Text = StringSetting("databaseFileName",
                "test.msi");
            manufacturerTextBox.Text = StringSetting("manufacturer", "");
            productNameTextBox.Text = StringSetting("productName", "");
            productVersionTextBox.Text = StringSetting("productVersion", "1.0");
            targetRootComboBox.SelectedIndex = targetRootComboBox.FindString(
                StringSetting("targetRoot", "ProgramFiles"));
            targetDirectoryTextBox.Text = StringSetting("targetDirectory",
                productNameTextBox.Text);
        }

        private void generateProductCodeButton_Click(object sender, System.EventArgs e)
        {
            productCodeTextBox.Text = IzFree.Application.NewGuid();
        }

        private void generatePackageCodeButton_Click(object sender, System.EventArgs e)
        {
            packageCodeTextBox.Text = IzFree.Application.NewGuid();
        }

        private void generateUpgradeCodeButton_Click(object sender, System.EventArgs e)
        {
            upgradeCodeTextBox.Text = IzFree.Application.NewGuid();
        }
        #endregion

        #region Private Methods
        private string StringSetting(string name, string defaultValue)
        {
            return IzFree.Application.ToolString(
                "NewPackage", name, defaultValue);
        }
        #endregion

        #region Properties
        public string TemplateDirectory
        {
            get { return templateDirectoryTextBox.Text; }
        }
        public string DatabaseFileName
        {
            get { return databaseFileNameTextBox.Text; }
        }
        public string Manufacturer
        {
            get { return manufacturerTextBox.Text; }
        }
        new public string ProductName
        {
            get { return productNameTextBox.Text; }
        }
        new public string ProductVersion
        {
            get { return productVersionTextBox.Text; }
        }
        public string TargetDirectoryRoot
        {
            get
            {
                return targetRootComboBox.Items[
                    targetRootComboBox.SelectedIndex] as string;
            }
        }
        public string TargetDirectory
        {
            get { return targetDirectoryTextBox.Text; }
        }
        public string ProductCode
        {
            get { return productCodeTextBox.Text; }
        }
        public string PackageCode
        {
            get { return packageCodeTextBox.Text; }
        }
        public string UpgradeCode
        {
            get { return upgradeCodeTextBox.Text; }
        }
        #endregion
	}
}
