#pragma once

#include "CEncoding.h"

class CUrl : public CEncoding
{
public:
    CUrl();
    virtual ~CUrl();

private:
    virtual DWORD _encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength);
    virtual DWORD _decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength);
};