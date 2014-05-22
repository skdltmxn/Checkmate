#pragma once

#include "CEncoding.h"

class CHex : public CEncoding
{
public:
    CHex();
    virtual ~CHex();

private:
    virtual DWORD _encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength);
    virtual DWORD _decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength);

    static const char *charset;
    int indexof(TCHAR c);
};