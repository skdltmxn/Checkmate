#pragma once

#include "CEncoding.h"

class CBase85 : public CEncoding
{
public:
    CBase85();
    virtual ~CBase85();

private:
    virtual DWORD _encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength);
    virtual DWORD _decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength);

private:
};