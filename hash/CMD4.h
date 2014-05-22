#pragma once

#include "CHash.h"

class CMD4 : public CHash
{
public:
    CMD4();
    virtual ~CMD4();

private:
    inline DWORD F(DWORD x, DWORD y, DWORD z) { return ((x & y) | (~x & z)); }
    inline DWORD G(DWORD x, DWORD y, DWORD z) { return ((x & y) | (x & z) | (y & z)); }
    inline DWORD H(DWORD x, DWORD y, DWORD z) { return (x ^ y ^ z); }

    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);

    DWORD h[4];

    static const DWORD shift[];
    static const DWORD k[];
};