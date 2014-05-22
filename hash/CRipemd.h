#pragma once

#include "CHash.h"

class CRipemd : public CHash
{
public:
    CRipemd();
    virtual ~CRipemd();

private:
    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);

    DWORD h[5];

    static const DWORD shift[];
    static const DWORD shift2[];
    static const DWORD r[];
    static const DWORD r2[];
};