using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using MsmMergeTypeLib;

namespace IzFree
{
	/// <summary>
	/// Summary description for ApplyMergeModuleForm.
	/// </summary>
	public class ApplyMergeModuleForm : System.Windows.Forms.Form
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public ApplyMergeModuleForm()
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
			this.components = new System.ComponentModel.Container();
			this.Size = new System.Drawing.Size(300,300);
			this.Text = "ApplyMergeModuleForm";
		}
		#endregion

        private void AddColumn(TextBox row, string text)
        {
            row.Text = text;
        }

        private string Collection(IMsmStrings strings)
        {
            string result = "";
            if (strings.Count > 0)
            {
                result = strings[1];
                for (int i = 2; i <= strings.Count; i++)
                {
                    result += ", " + strings[i];
                }
            }
            return result;
        }

        private void AddErrorRow(IMsmError error)
        {
            TextBox row = new TextBox();
            AddColumn(row, error.Type.ToString());
            AddColumn(row, error.Path);
            AddColumn(row, error.Language.ToString());
            AddColumn(row, error.DatabaseTable);
            AddColumn(row, error.ModuleTable);
            AddColumn(row, Collection(error.DatabaseKeys));
            AddColumn(row, Collection(error.ModuleKeys));
        }

        private void Apply()
        {
            string target = "";
            string module = "";
            string feature = "";
            m_merger.OpenDatabase(target);
            m_merger.OpenModule(module, 0);
            m_merger.Merge(feature, "");
            if (m_merger.Errors.Count > 0)
            {
                //countLabel.Text = m_merger.Errors.Count.ToString();
                foreach (IMsmError error in m_merger.Errors)
                {
                    AddErrorRow(error);
                }
            }
        }

        private MsmMerge2Class m_merger = new MsmMerge2Class();
	}
}
