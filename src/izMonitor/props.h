#if !defined(PROPS_H)
#define PROPS_H

#define CHECK_PROPERTY_POINTER()                                            \
if (!pVal)                                                                  \
{                                                                           \
    return Error(_T("A NULL pointer was passed for an output argument."),   \
        PROPERTY_IID, E_POINTER);                                           \
} else 0

#define STORE_STRING_PROPERTY(member_)                      \
    CHECK_PROPERTY_POINTER();                               \
    *pVal = CComBSTR(m_record->member_.c_str()).Detach()

#define STORE_LONG_PROPERTY(member_)    \
    CHECK_PROPERTY_POINTER();           \
    *pVal = m_record->member_

#endif
