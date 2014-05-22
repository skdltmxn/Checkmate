#pragma once

#include "CEncoding.h"

class Cl33t : public CEncoding
{
public:
    Cl33t();
    virtual ~Cl33t();
    
private:
    virtual DWORD _encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength);
    virtual DWORD _decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength);
};