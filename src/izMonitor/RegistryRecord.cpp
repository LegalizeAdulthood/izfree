// RegistryRecord.cpp : Implementation of CRegistryRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "RegistryRecord.h"

/////////////////////////////////////////////////////////////////////////////
// CRegistryRecord

STDMETHODIMP CRegistryRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRegistryRecord
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CRegistryRecord::get_Registry(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Root(LONG *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Key(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Name(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Value(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CRegistryRecord::get_Component(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
