/*
 * CSha2In512.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CSha2In512 class
 *
 */

#include "stdafx.h"
#include "CSha2.h"
#include "../helper/CEndian.h"

#define CH(x, y, z) (((x) & (y)) ^ ((~x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

const DWORD CSha2In512::k[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

CSha2In512::CSha2In512(int length) : CHash(512, length)
{
}

CSha2In512::~CSha2In512()
{
}

void CSha2In512::_hashBlock(const BYTE *pbBlock)
{
    // 512 bit block
    DWORD w[16];

    DWORD a = h[0];
    DWORD b = h[1];
    DWORD c = h[2];
    DWORD d = h[3];
    DWORD e = h[4];
    DWORD f = h[5];
    DWORD g = h[6];
    DWORD j = h[7];

    // Decode block
    CEndian::decodeBig32(w, pbBlock, 64);

    for (int i = 0; i < 64; ++i)
    {
        int s = i & 0x0f;
        DWORD s0, s1, t1, t2;

        if (i >= 16)
        {
            s0 = ROR32(w[(s + 1) & 0x0f], 7) ^ ROR32(w[(s + 1) & 0x0f], 18) ^ (w[(s + 1) & 0x0f] >> 3);
            s1 = ROR32(w[(s + 14) & 0x0f], 17) ^ ROR32(w[(s + 14) & 0x0f], 19) ^ (w[(s + 14) & 0x0f] >> 10);
            w[s] = w[s] + s0 + w[(s + 9) & 0x0f] + s1;
        }

        s0 = ROR32(a, 2) ^ ROR32(a, 13) ^ ROR32(a, 22);
        s1 = ROR32(e, 6) ^ ROR32(e, 11) ^ ROR32(e, 25);
        t1 = j + s1 + CH(e, f, g) + k[i] + w[s];
        t2 = s0 + MAJ(a, b, c);

        j = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += j;
}

void CSha2In512::_padBlock(const BYTE *pbBlock, const QWORD qwLength)
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
    CEndian::encodeBig64(&pbPaddingBlock[dwPadding - 8], &qwBitLength, 8);

    _hashBlock(pbPaddingBlock);

    // If there is one more padded block
    if (dwPadding > dwBlockSize)
        _hashBlock(pbPaddingBlock + dwBlockSize);

    delete []pbPaddingBlock;
}

void CSha2In512::_finalize(BYTE *pbHash)
{
    CEndian::encodeBig32(pbHash, h, getOutputSize() >> 3);
}