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
