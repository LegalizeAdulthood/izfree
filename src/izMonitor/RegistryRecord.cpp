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
