/*
 * CMD4.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CMD4 class
 *
 */

#include "stdafx.h"
#include "CMD4.h"
#include "../helper/CEndian.h"

#define ROL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

const DWORD CMD4::shift[] = {
    3, 7, 11, 19, 3, 7, 11, 19, 3, 7, 11, 19, 3, 7, 11, 19,
    3, 5, 9, 13, 3, 5, 9, 13, 3, 5, 9, 13, 3, 5, 9, 13,
    3, 9, 11, 15, 3, 9, 11, 15, 3, 9, 11, 15, 3, 9, 11, 15,
};

const DWORD CMD4::k[] = {
    0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
};

CMD4::CMD4() : CHash(512, 128)
{
    // Magic init integers
    h[0] = 0x67452301;
    h[1] = 0xefcdab89;
    h[2] = 0x98badcfe;
    h[3] = 0x10325476;
}

CMD4::~CMD4()
{
}

void CMD4::_hashBlock(const BYTE *pbBlock)
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
    for (int i = 0; i < 48; i++)
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
            f = G(b, c, d) + 0x5a827999;
            g = ((i * 4) % 16) + ((i / 4) - 4);
        }
        // Round 3
        else
        {
            f = H(b, c, d) + 0x6ed9eba1;
            g = k[i % 16];
        }

        DWORD temp = d;
        d = c;
        c = b;
        b = ROL((a + f + w[g]), shift[i]);
        a = temp;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
}

void CMD4::_padBlock(const BYTE *pbBlock, const QWORD qwLength)
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

void CMD4::_finalize(BYTE *pbHash)
{
    CEndian::encodeLittle32(pbHash, h, 16);
}