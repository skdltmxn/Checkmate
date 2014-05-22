#pragma once

#include "CHash.h"

class CMD5 : public CHash
{
public:
    CMD5();
    virtual ~CMD5();
    
private:
    inline DWORD F(DWORD x, DWORD y, DWORD z) { return ((x & y) | (~x & z)); }
    inline DWORD G(DWORD x, DWORD y, DWORD z) { return ((x & z) | (y & ~z)); }
    inline DWORD H(DWORD x, DWORD y, DWORD z) { return (x ^ y ^ z); }
    inline DWORD I(DWORD x, DWORD y, DWORD z) { return (y ^ (x | ~z)); }

    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);

    DWORD h[4];

    static const DWORD shift[];
    static const DWORD sine[];
};