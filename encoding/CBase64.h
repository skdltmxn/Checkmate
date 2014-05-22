#pragma once

#include "CEncoding.h"

class CBase64 : public CEncoding
{
public:
    CBase64();
    virtual ~CBase64();

private:
    virtual DWORD _encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength);
    virtual DWORD _decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength);
    int lookupIndex(TCHAR c);

    TCHAR    *m_szKey;
};
