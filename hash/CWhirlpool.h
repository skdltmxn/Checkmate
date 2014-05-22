#pragma once

#include "CHash.h"

#define ROUND    10

class CWhirlpool : public CHash
{
public:
    CWhirlpool();
    virtual ~CWhirlpool();

private:
    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);

    QWORD h[8];

    static const QWORD C0[256];
    static const QWORD C1[256];
    static const QWORD C2[256];
    static const QWORD C3[256];
    static const QWORD C4[256];
    static const QWORD C5[256];
    static const QWORD C6[256];
    static const QWORD C7[256];
    static const QWORD RC[ROUND + 1];
};