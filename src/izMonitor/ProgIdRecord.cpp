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
