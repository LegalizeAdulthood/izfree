// IClassTable.cpp : Implementation of IClassTable
#include "stdafx.h"
#include "IzMonitor.h"
#include "ClassTable.h"

/////////////////////////////////////////////////////////////////////////////
// CClassTable

#define CHECK_POINTER(var_) \
    if (!var_) \
    { \
        return Error(_T("A NULL pointer was passed for an output argument."), \
                     IID_IClassTable, E_POINTER); \
    } else 0

STDMETHODIMP CClassTable::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IClassTable
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CClassTable::get_Count(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CClassTable::get_Item(long row, IClassRecord **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CClassTable::_NewEnum(IUnknown **enumerator)
{
    CHECK_POINTER(enumerator);
	return S_OK;
}

