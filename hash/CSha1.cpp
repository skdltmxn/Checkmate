/*
 * CSha1.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CSha1 class
 *
 */

#include "stdafx.h"
#include "CSha1.h"
#include "../helper/CEndian.h"

CSha1::CSha1() : CHash(512, 160)
{
    // Magic init integers
    h[0] = 0x67452301;
    h[1] = 0xefcdab89;
    h[2] = 0x98badcfe;
    h[3] = 0x10325476;
    h[4] = 0xc3d2e1f0;
}

CSha1::~CSha1()
{
}

void CSha1::_hashBlock(const BYTE *pbBlock)
{
    // 512 bit block
    DWORD w[16];

    DWORD a = h[0];
    DWORD b = h[1];
    DWORD c = h[2];
    DWORD d = h[3];
    DWORD e = h[4];

    // Decode block
    CEndian::decodeBig32(w, pbBlock, 64);

    for (int i = 0; i < 80; ++i)
    {
        DWORD f, k;
        int s = i & 0x0f;

        if (i >= 16)
            w[s] = ROL32(( w[(s + 13) & 0x0f] ^ w[(s + 8) & 0x0f] ^ w[(s + 2) & 0x0f] ^ w[s] ), 1);

        if (i < 20)
        {
            f = (b & c) | (~b & d);
            k = 0x5a827999;
        }
        else if (i < 40)
        {
            f = b ^ c ^ d;
            k = 0x6ed9eba1;
        }
        else if (i < 60)
        {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8f1bbcdc;
        }
        else
        {
            f = b ^ c ^ d;
            k = 0xca62c1d6;
        }

        DWORD temp = ROL32(a, 5) + f + e + k + w[s];
        e = d;
        d = c;
        c = ROL32(b, 30);
        b = a;
        a = temp;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
}

void CSha1::_padBlock(const BYTE *pbBlock, const QWORD qwLength)
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

void CSha1::_finalize(BYTE *pbHash)
{
    CEndian::encodeBig32(pbHash, h, 20);
}