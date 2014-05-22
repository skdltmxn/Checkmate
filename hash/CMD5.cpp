/*
 * CMD5.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CMD5 class
 *
 */

#include "stdafx.h"
#include "CMD5.h"
#include "../helper/CEndian.h"

const DWORD CMD5::shift[] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

const DWORD CMD5::sine[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

CMD5::CMD5() : CHash(512, 128)
{
    // Magic init integers
    h[0] = 0x67452301;
    h[1] = 0xefcdab89;
    h[2] = 0x98badcfe;
    h[3] = 0x10325476;
}

CMD5::~CMD5()
{
}

void CMD5::_hashBlock(const BYTE *pbBlock)
{
    // 512 bit block
    DWORD w[16];

    DWORD a = h[0];
    DWORD b = h[1];
    DWORD c = h[2];
    DWORD d = h[3];

    // Decode block
    CEndian::decodeLittle32(w, pbBlock, 64);

    // Roundings
    for (int i = 0; i < 64; ++i)
    {
        DWORD f, g;

        // Round 1
        if (i < 16)
        {
            f = F(b, c, d);
            g = i;
        }
        // Round 2
        else if (i < 32)
        {
            f = G(b, c, d);
            g = (i * 5 + 1) % 16;
        }
        // Round 3
        else if (i < 48)
        {
            f = H(b, c, d);
            g = (i * 3 + 5) % 16;
        }
        // Round 4
        else
        {
            f = I(b, c, d);
            g = (i * 7) % 16;
        }

        DWORD temp = d;
        d = c;
        c = b;
        b = b + ROL32((a + f + sine[i] + w[g]), shift[i]);
        a = temp;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
}

void CMD5::_padBlock(const BYTE *pbBlock, const QWORD qwLength)
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

void CMD5::_finalize(BYTE *pbHash)
{
    CEndian::encodeLittle32(pbHash, h, 16);
}