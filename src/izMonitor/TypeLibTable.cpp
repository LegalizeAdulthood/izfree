// TypeLibTable.cpp : Implementation of CTypeLibTable
#include "stdafx.h"
#include "IzMonitor.h"
#include "TypeLibTable.h"

/////////////////////////////////////////////////////////////////////////////
// CTypeLibTable

STDMETHODIMP CTypeLibTable::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITypeLibTable
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
