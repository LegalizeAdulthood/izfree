// RegistryTable.cpp : Implementation of CRegistryTable
#include "stdafx.h"
#include "IzMonitor.h"
#include "RegistryTable.h"

/////////////////////////////////////////////////////////////////////////////
// CRegistryTable

STDMETHODIMP CRegistryTable::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRegistryTable
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
