// TypeLibRecord.cpp : Implementation of CTypeLibRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "TypeLibRecord.h"

/////////////////////////////////////////////////////////////////////////////
// CTypeLibRecord

STDMETHODIMP CTypeLibRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITypeLibRecord
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTypeLibRecord::get_LibID(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTypeLibRecord::get_Language(LONG *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTypeLibRecord::get_Component(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTypeLibRecord::get_Version(LONG *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTypeLibRecord::get_Description(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTypeLibRecord::get_Directory(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTypeLibRecord::get_Feature(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTypeLibRecord::get_Cost(LONG *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
