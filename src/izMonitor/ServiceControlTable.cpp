// ServiceControlTable.cpp : Implementation of CServiceControlTable
#include "stdafx.h"
#include "IzMonitor.h"
#include "ServiceControlTable.h"

/////////////////////////////////////////////////////////////////////////////
// CServiceControlTable

STDMETHODIMP CServiceControlTable::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IServiceControlTable
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
