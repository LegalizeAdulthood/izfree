using Crownwood.Magic;
using Crownwood.Magic.Controls;
using Crownwood.Magic.Forms;
using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace IzFree
{
	public class NewComponentsForm : Crownwood.Magic.Forms.WizardDialog
	{
        private Crownwood.Magic.Controls.WizardPage wizardPage1;
        private Crownwood.Magic.Controls.WizardPage wizardPage2;
        private Crownwood.Magic.Controls.WizardPage wizardPage3;
        private Crownwood.Magic.Controls.WizardPage wizardPage4;
        private System.Windows.Forms.Label scanDirectoryLabel;
        private System.Windows.Forms.TextBox scanDirectoryTextBox;
        private System.Windows.Forms.Button browseButton;
        private System.Windows.Forms.PropertyGrid componentPropertyGrid;
        private System.Windows.Forms.ListBox componentListBox;
        private System.Windows.Forms.TreeView rootFeatureTreeView;
        private System.Windows.Forms.Label rootFeatureLabel;
        private System.Windows.Forms.ComboBox rootDirectoryComboBox;
        private System.Windows.Forms.Label rootDirectoryLabel;
        private System.Windows.Forms.Label summaryLabel;
		private System.ComponentModel.IContainer components = null;

		public NewComponentsForm(Project project)
		{
			// This call is required by the Windows Form Designer.
			InitializeComponent();

			m_project = project;
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

		#region Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            this.wizardPage1 = new Crownwood.Magic.Controls.WizardPage();
            this.browseButton = new System.Windows.Forms.Button();
            this.scanDirectoryTextBox = new System.Windows.Forms.TextBox();
            this.scanDirectoryLabel = new System.Windows.Forms.Label();
            this.wizardPage2 = new Crownwood.Magic.Controls.WizardPage();
            this.componentListBox = new System.Windows.Forms.ListBox();
            this.componentPropertyGrid = new System.Windows.Forms.PropertyGrid();
            this.wizardPage3 = new Crownwood.Magic.Controls.WizardPage();
            this.rootFeatureTreeView = new System.Windows.Forms.TreeView();
            this.rootFeatureLabel = new System.Windows.Forms.Label();
            this.rootDirectoryComboBox = new System.Windows.Forms.ComboBox();
            this.rootDirectoryLabel = new System.Windows.Forms.Label();
            this.wizardPage4 = new Crownwood.Magic.Controls.WizardPage();
            this.summaryLabel = new System.Windows.Forms.Label();
            this.wizardPage1.SuspendLayout();
            this.wizardPage2.SuspendLayout();
            this.wizardPage3.SuspendLayout();
            this.wizardPage4.SuspendLayout();
            // 
            // wizardControl
            // 
            this.wizardControl.AssignDefaultButton = true;
            this.wizardControl.Name = "wizardControl";
            this.wizardControl.SelectedIndex = 2;
            this.wizardControl.Size = new System.Drawing.Size(592, 416);
            this.wizardControl.Title = "New Components Wizard";
            this.wizardControl.WizardPages.AddRange(new Crownwood.Magic.Controls.WizardPage[] {
                                                                                                  this.wizardPage1,
                                                                                                  this.wizardPage2,
                                                                                                  this.wizardPage3,
                                                                                                  this.wizardPage4});
            this.wizardControl.Load += new System.EventHandler(this.wizardControl_Load);
            this.wizardControl.NextClick += new System.ComponentModel.CancelEventHandler(this.wizardControl_NextClick);
            this.wizardControl.FinishClick += new System.EventHandler(this.wizardControl_FinishClick);
            this.wizardControl.BackClick += new System.ComponentModel.CancelEventHandler(this.wizardControl_BackClick);
            // 
            // wizardPage1
            // 
            this.wizardPage1.CaptionTitle = "Select Scan Directory";
            this.wizardPage1.Controls.Add(this.browseButton);
            this.wizardPage1.Controls.Add(this.scanDirectoryTextBox);
            this.wizardPage1.Controls.Add(this.scanDirectoryLabel);
            this.wizardPage1.FullPage = false;
            this.wizardPage1.Location = new System.Drawing.Point(0, 0);
            this.wizardPage1.Name = "wizardPage1";
            this.wizardPage1.Selected = false;
            this.wizardPage1.Size = new System.Drawing.Size(592, 287);
            this.wizardPage1.SubTitle = "Select a directory on the local machine to scan for new Windows Installer compone" +
                "nts.";
            this.wizardPage1.TabIndex = 0;
            // 
            // browseButton
            // 
            this.browseButton.Location = new System.Drawing.Point(472, 136);
            this.browseButton.Name = "browseButton";
            this.browseButton.TabIndex = 2;
            this.browseButton.Text = "Browse...";
            this.browseButton.Click += new System.EventHandler(this.browseButton_Click);
            // 
            // scanDirectoryTextBox
            // 
            this.scanDirectoryTextBox.Location = new System.Drawing.Point(88, 136);
            this.scanDirectoryTextBox.Name = "scanDirectoryTextBox";
            this.scanDirectoryTextBox.Size = new System.Drawing.Size(368, 21);
            this.scanDirectoryTextBox.TabIndex = 1;
            this.scanDirectoryTextBox.Text = "";
            this.scanDirectoryTextBox.TextChanged += new System.EventHandler(this.scanDirectoryTextBox_TextChanged);
            // 
            // scanDirectoryLabel
            // 
            this.scanDirectoryLabel.Location = new System.Drawing.Point(88, 104);
            this.scanDirectoryLabel.Name = "scanDirectoryLabel";
            this.scanDirectoryLabel.TabIndex = 0;
            this.scanDirectoryLabel.Text = "Scan Directory:";
            // 
            // wizardPage2
            // 
            this.wizardPage2.CaptionTitle = "Review Components";
            this.wizardPage2.Controls.Add(this.componentListBox);
            this.wizardPage2.Controls.Add(this.componentPropertyGrid);
            this.wizardPage2.FullPage = false;
            this.wizardPage2.Location = new System.Drawing.Point(0, 0);
            this.wizardPage2.Name = "wizardPage2";
            this.wizardPage2.Selected = false;
            this.wizardPage2.Size = new System.Drawing.Size(592, 287);
            this.wizardPage2.SubTitle = "Review and modify automatically created Windows Installer components.";
            this.wizardPage2.TabIndex = 1;
            // 
            // componentListBox
            // 
            this.componentListBox.Location = new System.Drawing.Point(24, 24);
            this.componentListBox.Name = "componentListBox";
            this.componentListBox.Size = new System.Drawing.Size(248, 238);
            this.componentListBox.TabIndex = 5;
            this.componentListBox.SelectedIndexChanged += new System.EventHandler(this.componentListBox_SelectedIndexChanged);
            // 
            // componentPropertyGrid
            // 
            this.componentPropertyGrid.CommandsVisibleIfAvailable = true;
            this.componentPropertyGrid.HelpVisible = false;
            this.componentPropertyGrid.LargeButtons = false;
            this.componentPropertyGrid.LineColor = System.Drawing.SystemColors.ScrollBar;
            this.componentPropertyGrid.Location = new System.Drawing.Point(280, 24);
            this.componentPropertyGrid.Name = "componentPropertyGrid";
            this.componentPropertyGrid.Size = new System.Drawing.Size(288, 240);
            this.componentPropertyGrid.TabIndex = 4;
            this.componentPropertyGrid.Text = "component property grid";
            this.componentPropertyGrid.ToolbarVisible = false;
            this.componentPropertyGrid.ViewBackColor = System.Drawing.SystemColors.Window;
            this.componentPropertyGrid.ViewForeColor = System.Drawing.SystemColors.WindowText;
            // 
            // wizardPage3
            // 
            this.wizardPage3.CaptionTitle = "Select Feature";
            this.wizardPage3.Controls.Add(this.rootFeatureTreeView);
            this.wizardPage3.Controls.Add(this.rootFeatureLabel);
            this.wizardPage3.Controls.Add(this.rootDirectoryComboBox);
            this.wizardPage3.Controls.Add(this.rootDirectoryLabel);
            this.wizardPage3.FullPage = false;
            this.wizardPage3.Location = new System.Drawing.Point(0, 0);
            this.wizardPage3.Name = "wizardPage3";
            this.wizardPage3.Size = new System.Drawing.Size(592, 287);
            this.wizardPage3.SubTitle = "Select the feature and root directory to associate with the new components.";
            this.wizardPage3.TabIndex = 2;
            // 
            // rootFeatureTreeView
            // 
            this.rootFeatureTreeView.ImageIndex = -1;
            this.rootFeatureTreeView.Location = new System.Drawing.Point(168, 91);
            this.rootFeatureTreeView.Name = "rootFeatureTreeView";
            this.rootFeatureTreeView.SelectedImageIndex = -1;
            this.rootFeatureTreeView.ShowRootLines = false;
            this.rootFeatureTreeView.Size = new System.Drawing.Size(320, 136);
            this.rootFeatureTreeView.TabIndex = 7;
            // 
            // rootFeatureLabel
            // 
            this.rootFeatureLabel.Location = new System.Drawing.Point(56, 99);
            this.rootFeatureLabel.Name = "rootFeatureLabel";
            this.rootFeatureLabel.Size = new System.Drawing.Size(104, 24);
            this.rootFeatureLabel.TabIndex = 6;
            this.rootFeatureLabel.Text = "Associated Feature:";
            this.rootFeatureLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // rootDirectoryComboBox
            // 
            this.rootDirectoryComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.rootDirectoryComboBox.Location = new System.Drawing.Point(168, 59);
            this.rootDirectoryComboBox.Name = "rootDirectoryComboBox";
            this.rootDirectoryComboBox.Size = new System.Drawing.Size(320, 21);
            this.rootDirectoryComboBox.TabIndex = 5;
            // 
            // rootDirectoryLabel
            // 
            this.rootDirectoryLabel.Location = new System.Drawing.Point(56, 59);
            this.rootDirectoryLabel.Name = "rootDirectoryLabel";
            this.rootDirectoryLabel.Size = new System.Drawing.Size(104, 24);
            this.rootDirectoryLabel.TabIndex = 4;
            this.rootDirectoryLabel.Text = "Root Directory:";
            this.rootDirectoryLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // wizardPage4
            // 
            this.wizardPage4.CaptionTitle = "Commit Components";
            this.wizardPage4.Controls.Add(this.summaryLabel);
            this.wizardPage4.FullPage = false;
            this.wizardPage4.Location = new System.Drawing.Point(0, 0);
            this.wizardPage4.Name = "wizardPage4";
            this.wizardPage4.Selected = false;
            this.wizardPage4.Size = new System.Drawing.Size(592, 287);
            this.wizardPage4.SubTitle = "Commit the new components to the database.";
            this.wizardPage4.TabIndex = 3;
            // 
            // summaryLabel
            // 
            this.summaryLabel.Location = new System.Drawing.Point(72, 59);
            this.summaryLabel.Name = "summaryLabel";
            this.summaryLabel.Size = new System.Drawing.Size(448, 168);
            this.summaryLabel.TabIndex = 13;
            this.summaryLabel.Text = "summary text";
            this.summaryLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // NewComponentsForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(592, 416);
            this.Name = "NewComponentsForm";
            this.Text = "New Components Wizard";
            this.wizardPage1.ResumeLayout(false);
            this.wizardPage2.ResumeLayout(false);
            this.wizardPage3.ResumeLayout(false);
            this.wizardPage4.ResumeLayout(false);

        }
		#endregion

        private void wizardControl_Load(object sender, System.EventArgs e)
        {
            wizardControl.EnableNextButton =
            wizardControl.EnableFinishButton = WizardControl.Status.No;
        }

        IzFree.Project m_project;

        private void browseButton_Click(object sender, System.EventArgs e)
        {
            using (FolderBrowserDialog dlg = new FolderBrowserDialog())
            {
                if (Directory.Exists(scanDirectoryTextBox.Text))
                {
                    dlg.SelectedPath = scanDirectoryTextBox.Text;
                }
                if (DialogResult.OK == dlg.ShowDialog())
                {
                    scanDirectoryTextBox.Text = dlg.SelectedPath;
                }
            }
        }

        private void scanDirectoryTextBox_TextChanged(object sender, System.EventArgs e)
        {
            wizardControl.EnableNextButton =
            wizardControl.EnableFinishButton =
                ((scanDirectoryTextBox.Text.Length > 0) &&
                Directory.Exists(scanDirectoryTextBox.Text)) ?
                WizardControl.Status.Yes : WizardControl.Status.No;
        }

        private void wizardControl_BackClick(object sender, System.ComponentModel.CancelEventArgs e)
        {
            wizardControl.EnableNextButton = WizardControl.Status.Yes;
        }

        private void wizardControl_NextClick(object sender, System.ComponentModel.CancelEventArgs e)
        {
            PerformStep(wizardControl.SelectedIndex);
            if (0 == wizardControl.SelectedIndex)
            {
                BuildComponents();
            }
            else if (1 == wizardControl.SelectedIndex)
            {
                // build feature tree and directory combobox
                BuildFeatures();
                BuildDirectories();
            }
            else if (2 == wizardControl.SelectedIndex)
            {
                BuildSummary();
                wizardControl.EnableNextButton = WizardControl.Status.No;
            }
        }

        private void wizardControl_FinishClick(object sender, System.EventArgs e)
        {
            for (int i = wizardControl.SelectedIndex;
                i < wizardControl.WizardPages.Count-1; i++)
            {
                PerformStep(i);
            }
        }
        public void Commit()
        {
            m_scanner.Commit(m_project, RootDirectory, RootFeature);
        }
        private void BuildComponents()
        {
            componentListBox.Items.Clear();
            Scan.Component[] components = m_scanner.Components;
            for (int i = 0; i < components.Length; i++)
            {
                componentListBox.Items.Add(components[i].Name);
            }
            componentListBox.SelectedIndex = 0;
        }

        private void BuildFeatures()
        {
            ArrayList roots = new ArrayList();
            Hashtable tree = new Hashtable();
            using (MSI.View view = Application.ExecView(m_project.Database,
                       "SELECT `Feature`,`Feature_Parent` FROM `Feature` " +
                       "ORDER BY `Feature_Parent`"))
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
            }
            roots.Sort();

            rootFeatureTreeView.Nodes.Clear();
            for (int i = 0; i < roots.Count; i++)
            {
                string feature = roots[i] as string;
                TreeNode root = new TreeNode(feature);
                root.Tag = "R" + i.ToString();
                rootFeatureTreeView.Nodes.Add(root);
                AddFeatures(tree, rootFeatureTreeView,
                    root.Tag as string, feature);
            }
            rootFeatureTreeView.SelectedNode = rootFeatureTreeView.Nodes[0];
        }

        private void AddFeatures(Hashtable tree, TreeView tv,
            string parentLabel, string parent)
        {
            if (tree.ContainsKey(parent))
            {
                ArrayList kids = tree[parent] as ArrayList;
                kids.Sort();
                for (int i = 0; i < kids.Count; i++)
                {
                    string kid = kids[i] as string;
                    TreeNode child = new TreeNode(kid);
                    child.Tag = parentLabel + ".F" + i.ToString();
                    tv.Nodes.Add(child);
                    AddFeatures(tree, tv, child.Tag as string, kid);
                }
            }
        }

        private void BuildDirectories()
        {
            rootDirectoryComboBox.Items.Clear();
            Scan.Directory[] directories = m_scanner.Directories;
            for (int i = 0; i < directories.Length; i++)
            {
                rootDirectoryComboBox.Items.Add(directories[i].Name);
            }
            rootDirectoryComboBox.SelectedIndex = 0;
        }

        private void BuildSummary()
        {
            // build confirmation display
            summaryLabel.Text = String.Format("Scanning directory \"{0}\" " +
                "resulted in {1} components, " +
                "{2} directories and " +
                "{3} files.  The new components will be associated " +
                "with the feature \"{4}\" and installed to the " +
                "target directory \"{5}\".",
                scanDirectoryTextBox.Text,
                m_scanner.Components.Length,
                m_scanner.Directories.Length,
                m_scanner.Files.Length,
                RootFeature,
                RootDirectory);
        }

        private void PerformStep(int step)
        {
            if (0 == step)
            {
                m_scanner.Scan(scanDirectoryTextBox.Text);
            }
        }

        public string ScanDirectory
        {
            get { return scanDirectoryTextBox.Text; }
        }

        public string RootDirectory
        {
            get { return rootDirectoryComboBox.Text; }
        }

        public string RootFeature
        {
            get { return rootFeatureTreeView.SelectedNode.Text; }
        }

        private Scan.Scanner m_scanner = new Scan.Scanner();

        private void componentListBox_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            componentPropertyGrid.SelectedObject = m_scanner.FindComponent(
                componentListBox.SelectedItem.ToString());
        }
    }
}

