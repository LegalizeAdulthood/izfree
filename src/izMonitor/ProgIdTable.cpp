// ProgIdTable.cpp : Implementation of CProgIdTable
#include "stdafx.h"
#include "IzMonitor.h"
#include "ProgIdTable.h"

/////////////////////////////////////////////////////////////////////////////
// CProgIdTable

STDMETHODIMP CProgIdTable::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProgIdTable
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
