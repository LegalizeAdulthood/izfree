// ServiceControlRecord.cpp : Implementation of CServiceControlRecord
#include "stdafx.h"
#include "IzMonitor.h"
#include "ServiceControlRecord.h"

/////////////////////////////////////////////////////////////////////////////
// CServiceControlRecord

STDMETHODIMP CServiceControlRecord::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IServiceControlRecord
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
