// ServiceInstallRecord.cpp : Implementation of CServiceInstallRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "ServiceInstallRecord.h"

/////////////////////////////////////////////////////////////////////////////
// CServiceInstallRecord

STDMETHODIMP CServiceInstallRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IServiceInstallRecord
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CServiceInstallRecord::get_ServiceInstall(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Name(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_DisplayName(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_ServiceType(LONG *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_StartType(LONG *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_ErrorControl(LONG *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_LoadOrderGroup(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Dependencies(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_StartName(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Password(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Arguments(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Component(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CServiceInstallRecord::get_Description(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
