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
