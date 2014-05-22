#pragma once

#include "CEncoding.h"

class CBinary : public CEncoding
{
public:
    CBinary();
    virtual ~CBinary();

private:
    virtual DWORD _encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength);
    virtual DWORD _decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength);
};