#pragma once

#include "CHash.h"

#define HAVAL_VERSION    1

class CHaval : public CHash
{
public:
    CHaval(int pass = 3, int length = 128);
    virtual ~CHaval();

private:
    inline const DWORD f1(
        const DWORD x6,
        const DWORD x5,
        const DWORD x4,
        const DWORD x3,
        const DWORD x2,
        const DWORD x1,
        const DWORD x0)
    {
        return x1 & (x0 ^ x4) ^ x2 & x5 ^ x3 & x6 ^ x0;
    }

    inline const DWORD f2(
        const DWORD x6,
        const DWORD x5,
        const DWORD x4,
        const DWORD x3,
        const DWORD x2,
        const DWORD x1,
        const DWORD x0)
    {
        return x2 &
            (x1 & ~x3 ^ x4 & x5 ^ x6 ^ x0) ^
            x4 & (x1 ^ x5) ^
            x3 & x5 ^ x0;
    }

    inline const DWORD f3(
        const DWORD x6,
        const DWORD x5,
        const DWORD x4,
        const DWORD x3,
        const DWORD x2,
        const DWORD x1,
        const DWORD x0)
    {
        return x3 &
            (x1 & x2 ^ x6 ^ x0) ^
            x1 & x4 ^ x2 & x5 ^ x0;
    }

    inline const DWORD f4(
        const DWORD x6,
        const DWORD x5,
        const DWORD x4,
        const DWORD x3,
        const DWORD x2,
        const DWORD x1,
        const DWORD x0)
    {
        return x4 &
            (x5 & ~x2 ^ x3 & ~x6 ^ x1 ^ x6 ^ x0) ^
            x3 & (x1 & x2 ^ x5 ^ x6) ^
            x2 & x6 ^ x0;
    }

    inline const DWORD f5(
        const DWORD x6,
        const DWORD x5,
        const DWORD x4,
        const DWORD x3,
        const DWORD x2,
        const DWORD x1,
        const DWORD x0)
    {
        return x0 &
            (x1 & x2 & x3 ^ ~x5) ^
            x1 & x4 ^ x2 & x5 ^ x3 & x6;
    }

    inline void permutate(DWORD *t, const DWORD R)
    {
        for (int i = 7; i; --i)
            t[i] = t[i - 1];

        t[0] = R;
    }

    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);
    
    void _pass(DWORD *t, const DWORD *w);
    void _tailor(DWORD *x);

    int m_pass;
    DWORD h[8];

    static const int wordOrder[];
    static const DWORD K[];
};