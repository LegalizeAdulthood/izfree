using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Pahvant.MSI
{
    class Session
    {
        private MSIHandle m_handle;

        public Session(IntPtr handle)
        {
            m_handle = new MSIHandle(handle);
        }

        private static void TR(UInt32 result)
        {
            Installer.TR(result);
        }

        #region Handle
        public IntPtr Handle
        {
            get { return m_handle.Handle; }
        }
        #endregion

        #region DoAction
        public void DoAction(string action)
        {
            TR(MsiDoAction(m_handle.Handle, action));
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiDoAction(IntPtr session, string action);
        #endregion

        #region EnumComponentCosts
        public void EnumComponentCosts(string component, int index,
            InstallState installState,
            out string driveResult, out int cost, out int tempCost)
        {
            int driveLength = Installer.MaxPathLength;
            StringBuilder drive = new StringBuilder(driveLength);
            TR(MsiEnumComponentCosts(m_handle.Handle, component, index,
                (UInt32) installState, drive, ref driveLength,
                out cost, out tempCost));
            driveResult = drive.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEnumComponentCosts(IntPtr session,
            string component, int index, UInt32 installState,
            StringBuilder drive, ref int driveLength,
            out int cost, out int tempCost);
        #endregion

        #region EvaluateCondition
        public MSI.Condition EvaluateCondition(string condition)
        {
            return (MSI.Condition)
                MsiEvaluateCondition(m_handle.Handle, condition);
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiEvaluateCondition(IntPtr session,
            string condition);
        #endregion

        #region FormatRecord
        public string FormatRecord(MSI.Record record)
        {
            int resultLength = Installer.MaxPathLength;
            StringBuilder result = new StringBuilder(resultLength);
            TR(MsiFormatRecord(m_handle.Handle, record.Handle,
                result, ref resultLength));
            return result.ToString();
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiFormatRecord(IntPtr session,
            IntPtr record, StringBuilder result, ref int resultLength);
        #endregion

        #region ActiveDatabase
        Database ActiveDatabase
        {
            get
            {
                return new Database(MsiGetActiveDatabase(m_handle.Handle));
            }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern IntPtr MsiGetActiveDatabase(IntPtr session);
        #endregion

        #region ComponentState
        public MSI.InstallState ComponentState(string component,
            out InstallState installedReturn, out InstallState actionReturn)
        {
            UInt32 installed;
            UInt32 action;
            MSI.InstallState result = (MSI.InstallState)
                MsiGetComponentState(m_handle.Handle, component,
                out installed, out action);
            installedReturn = (InstallState) installed;
            actionReturn = (InstallState) action;
            return result;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetComponentState(IntPtr session,
            string component, out UInt32 installed, out UInt32 action);
        #endregion

        #region FeatureCost
        public int FeatureCost(string feature, CostTree costTree,
            InstallState state)
        {
            int cost = 0;
            TR(MsiGetFeatureCost(m_handle.Handle, feature,
                (UInt32) costTree, (UInt32) state, out cost));
            return cost;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFeatureCost(IntPtr session,
            string feature, UInt32 costTree, UInt32 state, out int cost);
        #endregion

        #region FeatureState
        public MSI.InstallState FeatureState(string feature,
            out InstallState installedReturn, out InstallState actionReturn)
        {
            UInt32 installed;
            UInt32 action;
            MSI.InstallState result = (MSI.InstallState)
                MsiGetFeatureState(m_handle.Handle, feature,
                out installed, out action);
            installedReturn = (InstallState) installed;
            actionReturn = (InstallState) action;
            return result;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFeatureState(IntPtr session,
            string feature, out UInt32 installed, out UInt32 action);
        #endregion

        #region GetFeatureValidStates
        public InstallState GetFeatureValidStates(string feature)
        {
            UInt32 states;
            TR(MsiGetFeatureValidStates(m_handle.Handle, feature, out states));
            return (InstallState) states;
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetFeatureValidStates(IntPtr session,
            string feature, out UInt32 installState);
        #endregion

        #region Language
        int Language
        {
            get { return (int) MsiGetLanguage(m_handle.Handle); }
        }
        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetLanguage(IntPtr session);
        #endregion

        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 MsiGetMode(IntPtr session, int runMode);

        [DllImport(Installer.MSI_DLL, CharSet = CharSet.Auto)]
        private static extern UInt32 Msi(IntPtr session);

    }
}