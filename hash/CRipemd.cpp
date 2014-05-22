/*
 * CRipemd.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CRipemd class
 *
 */

#include "stdafx.h"
#include "CRipemd.h"
#include "../helper/CEndian.h"

#define F1(x, y, z) ((x) ^ (y) ^ (z))
#define F2(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define F3(x, y, z) (((x) | (~y)) ^ (z))
#define F4(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define F5(x, y, z) ((x) ^ ((y) | (~z)))

const DWORD CRipemd::shift[] = {
    11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8,
    7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12,
    11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5,
    11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12,
    9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6
};

const DWORD CRipemd::shift2[] = {
    8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6,
    9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11,
    9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5,
    15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8,
    8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11
};

const DWORD CRipemd::r[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8,
    3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12,
    1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2,
    4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13
};

const DWORD CRipemd::r2[] = {
    5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12,
    6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2,
    15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13,
    8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14,
    12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11
};

CRipemd::CRipemd() : CHash(512, 160)
{
    // Magic init integers
    h[0] = 0x67452301;
    h[1] = 0xefcdab89;
    h[2] = 0x98badcfe;
    h[3] = 0x10325476;
    h[4] = 0xc3d2e1f0;
}

CRipemd::~CRipemd()
{
}

void CRipemd::_hashBlock(const BYTE *pbBlock)
{
    // 512 bit block
    DWORD w[16];

    DWORD a = h[0], a2 = h[0];
    DWORD b = h[1], b2 = h[1];
    DWORD c = h[2], c2 = h[2];
    DWORD d = h[3], d2 = h[3];
    DWORD e = h[4], e2 = h[4];
    DWORD t1, t2;

    // Decode block
    CEndian::decodeLittle32(w, pbBlock, 64);

    for (int i = 0; i < 80; ++i)
    {
        if (i < 16)
        {
            t1 = ROL32((a + F1(b, c, d) + w[r[i]]), shift[i]) + e;
            t2 = ROL32((a2 + F5(b2, c2, d2) + w[r2[i]] + 0x50a28be6), shift2[i]) + e2;
        }
        else if (i < 32)
        {
            t1 = ROL32((a + F2(b, c, d) + w[r[i]] + 0x5a827999), shift[i]) + e;
            t2 = ROL32((a2 + F4(b2, c2, d2) + w[r2[i]] + 0x5c4dd124), shift2[i]) + e2;
        }
        else if (i < 48)
        {
            t1 = ROL32((a + F3(b, c, d) + w[r[i]] + 0x6ed9eba1), shift[i]) + e;
            t2 = ROL32((a2 + F3(b2, c2, d2) + w[r2[i]] + 0x6d703ef3), shift2[i]) + e2;
        }
        else if (i < 64)
        {
            t1 = ROL32((a + F4(b, c, d) + w[r[i]] + 0x8f1bbcdc), shift[i]) + e;
            t2 = ROL32((a2 + F2(b2, c2, d2) + w[r2[i]] + 0x7a6d76e9), shift2[i]) + e2;
        }
        else
        {
            t1 = ROL32((a + F5(b, c, d) + w[r[i]] + 0xa953fd4e), shift[i]) + e;
            t2 = ROL32((a2 + F1(b2, c2, d2) + w[r2[i]]), shift2[i]) + e2;
        }

        a = e;
        e = d;
        d = ROL32(c, 10);
        c = b;
        b = t1;

        a2 = e2;
        e2 = d2;
        d2 = ROL32(c2, 10);
        c2 = b2;
        b2 = t2;
    }

    DWORD t = h[1] + c + d2;
    h[1] = h[2] + d + e2;
    h[2] = h[3] + e + a2;
    h[3] = h[4] + a + b2;
    h[4] = h[0] + b + c2;
    h[0] = t;
}

void CRipemd::_padBlock(const BYTE *pbBlock, const QWORD qwLength)
{
    register DWORD dwBlockSize = (getBlockSize() >> 3);
    DWORD dwTailLength = (qwLength % dwBlockSize);
    DWORD dwPadding = dwBlockSize - dwTailLength;
    if (dwPadding <= 8) dwPadding += dwBlockSize;

    dwPadding += dwTailLength;

    PBYTE pbPaddingBlock = new (std::nothrow) BYTE[dwPadding];
    if (!pbPaddingBlock) return;

    memset(pbPaddingBlock, NULL, dwPadding);
    memcpy(pbPaddingBlock, pbBlock, dwTailLength);

    // First byte of padding
    pbPaddingBlock[dwTailLength] = 0x80;

    // Append length in bits
    QWORD qwBitLength = qwLength << 3;
    CEndian::encodeLittle64(&pbPaddingBlock[dwPadding - 8], &qwBitLength, 8);

    _hashBlock(pbPaddingBlock);

    // If there is one more padded block
    if (dwPadding > dwBlockSize)
        _hashBlock(pbPaddingBlock + dwBlockSize);

    delete []pbPaddingBlock;
}

void CRipemd::_finalize(BYTE *pbHash)
{
    CEndian::encodeLittle32(pbHash, h, 20);
}