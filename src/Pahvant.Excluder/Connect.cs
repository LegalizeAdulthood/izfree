namespace Pahvant
{
	using System;
	using Microsoft.Office.Core;
	using Extensibility;
	using System.Runtime.InteropServices;
	using EnvDTE;
    using DeployPluginsLib;
    using System.IO;

	#region Read me for Add-in installation and setup information.
	// When run, the Add-in wizard prepared the registry for the Add-in.
	// At a later time, if the Add-in becomes unavailable for reasons such as:
	//   1) You moved this project to a computer other than which is was originally created on.
	//   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
	//   3) Registry corruption.
	// you will need to re-register the Add-in by building the MyAddin21Setup project
	// by right clicking the project in the Solution Explorer, then choosing install.
	#endregion

	/// <summary>
	///   The object for implementing an Add-in.
	/// </summary>
	/// <seealso class='IDTExtensibility2' />
	[Guid("27BB3561-FD0A-4C9F-91B4-C040FDC95627"),
     ProgId("Pahvant.Excluder")]
	public class Excluder : Object, IDTExtensibility2
	{
		/// <summary>
		///		Implements the constructor for the Add-in object.
		///		Place your initialization code within this method.
		/// </summary>
		public Excluder()
		{
		}

		/// <summary>
		///      Implements the OnConnection method of the IDTExtensibility2 interface.
		///      Receives notification that the Add-in is being loaded.
		/// </summary>
		/// <param term='application'>
		///      Root object of the host application.
		/// </param>
		/// <param term='connectMode'>
		///      Describes how the Add-in is being loaded.
		/// </param>
		/// <param term='addInInst'>
		///      Object representing this Add-in.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnConnection(object application,
            ext_ConnectMode connectMode, object instance,
            ref System.Array custom)
		{
            m_commandLine = (connectMode == ext_ConnectMode.ext_cm_CommandLine);
            m_application = (_DTE) application;
            m_instance = (AddIn) instance;
            if (m_commandLine)
            {
                m_writer = System.Console.Out;
            }
            else
            {
                m_writer = File.AppendText(System.IO.Path.GetTempPath() +
                    @"\excluder.log");
            }
            m_solutionEvents =
                (SolutionEvents) m_application.Events.SolutionEvents;
            m_solutionEvents.Opened += new
                _dispSolutionEvents_OpenedEventHandler(SolutionEvents_Opened);
		}

		/// <summary>
		///     Implements the OnDisconnection method of the IDTExtensibility2 interface.
		///     Receives notification that the Add-in is being unloaded.
		/// </summary>
		/// <param term='disconnectMode'>
		///      Describes how the Add-in is being unloaded.
		/// </param>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnDisconnection(ext_DisconnectMode disconnectMode,
            ref System.Array custom)
		{
            m_solutionEvents.Opened -= new
                _dispSolutionEvents_OpenedEventHandler(SolutionEvents_Opened);
            if (!m_commandLine)
            {
                m_writer.Close();
            }
		}

		/// <summary>
		///      Implements the OnAddInsUpdate method of the IDTExtensibility2 interface.
		///      Receives notification that the collection of Add-ins has changed.
		/// </summary>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnAddInsUpdate(ref System.Array custom)
		{
		}

		/// <summary>
		///      Implements the OnStartupComplete method of the IDTExtensibility2 interface.
		///      Receives notification that the host application has completed loading.
		/// </summary>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnStartupComplete(ref System.Array custom)
		{
		}

		/// <summary>
		///      Implements the OnBeginShutdown method of the IDTExtensibility2 interface.
		///      Receives notification that the host application is being unloaded.
		/// </summary>
		/// <param term='custom'>
		///      Array of parameters that are host application specific.
		/// </param>
		/// <seealso class='IDTExtensibility2' />
		public void OnBeginShutdown(ref System.Array custom)
		{
		}

        public bool Exclude()
        {
            bool result = false;
            foreach (Project project in m_application.Solution.Projects)
            {
                if (project.Kind == vsProjectKindDeployment)
                {
                    IVsdDeployable deployable = (IVsdDeployable) project.Object;
                    if ((deployable.Type.TypeID == "MSM") ||
                        (deployable.Type.TypeID == "Setup"))
                    {
                        Log("Excluding project " + project.Name);
                        if (ExcludeProject(deployable.PlugIns))
                        {
                            result = true;
                        }
                    }
                }
            }
            return result;
        }

        private bool ExcludeProject(IVsdCollectionSubset plugins)
        {
            bool result = false;
            if (ExcludeMergeModules((plugins.Item("MergeModule") as IVsdMergeModulePlugIn).Items))
            {
                result = true;
            }
            if (ExcludeFiles((plugins.Item("File") as IVsdFilePlugIn).Items))
            {
                result = true;
            }
            return result;
        }

        private bool ExcludeMergeModules(IVsdManagedCollection items)
        {
            bool result = false;
            foreach (IVsdModule item in items)
            {
                if (item.IsDependency && !item.Exclude)
                {
                    Log("    Module " + item.SourcePath);
                    item.Exclude = true;
                    result = true;
                }
            }
            return result;
        }

        private bool ExcludeFiles(IVsdManagedCollection items)
        {
            bool result = false;
            foreach (object thing in items)
            {
                if (thing is IVsdFile)
                {
                    IVsdFile file = thing as IVsdFile;
                    if (file.IsDependency && !file.Exclude)
                    {
                        Log("    File " + file.SourcePath);
                        file.Exclude = true;
                        result = true;
                    }
                }
                else if (thing is IVsdAssembly)
                {
                    IVsdAssembly assy = thing as IVsdAssembly;
                    if (assy.IsDependency && !assy.Exclude)
                    {
                        Log("    Assembly " + assy.SourcePath);
                        assy.Exclude = true;
                        result = true;
                    }
                }
                else
                {
                    Log("Unknown type.");
                }
            }
            return result;
        }

        #region Private Instance Data
		private _DTE m_application;
		private AddIn m_instance;
        private bool m_commandLine = false;
        #endregion

        private const string vsProjectKindDeployment = 
            "{54435603-DBB4-11D2-8724-00A0C9A8B90C}";

        private void Log(string text)
        {
            m_writer.WriteLine(text);
        }

        private TextWriter m_writer;
        private SolutionEvents m_solutionEvents;

        private void SolutionEvents_Opened()
        {
            Exclude();
        }
    }
}
