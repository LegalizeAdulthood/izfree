// ProgIdRecord.cpp : Implementation of CProgIdRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "ProgIdRecord.h"

/////////////////////////////////////////////////////////////////////////////
// CProgIdRecord

STDMETHODIMP CProgIdRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProgIdRecord
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CProgIdRecord::get_ProgId(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CProgIdRecord::get_Parent(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CProgIdRecord::get_Class(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CProgIdRecord::get_Description(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CProgIdRecord::get_Icon(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CProgIdRecord::get_IconIndex(LONG *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
