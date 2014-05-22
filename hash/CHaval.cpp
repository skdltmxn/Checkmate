/*
 * CHaval.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CHaval class
 *
 */

#include "stdafx.h"
#include "CHaval.h"
#include "../helper/CEndian.h"

const int CHaval::wordOrder[] = {
    5, 14, 26, 18, 11, 28, 7, 16, 0, 23, 20, 22, 1, 10, 4, 8,
    30, 3, 21, 9, 17, 24, 29, 6, 19, 12, 15, 13, 2, 25, 31, 27,
    19, 9, 4, 20, 28, 17, 8, 22, 29, 14, 25, 12, 24, 30, 16, 26,
    31, 15, 7, 3, 1, 0, 18, 27, 13, 6, 21, 10, 23, 11, 5, 2,
    24, 4, 0, 14, 2, 7, 28, 23, 26, 6, 30, 20, 18, 25, 19, 3,
    22, 11, 31, 21, 8, 27, 12, 9, 1, 29, 5, 15, 17, 10, 16, 13,
    27, 3, 21, 26, 17, 11, 20, 29, 19, 0, 12, 7, 13, 8, 31, 10,
    5, 9, 14, 30, 18, 6, 28, 24, 2, 23, 16, 22, 4, 1, 25, 15
};

const DWORD CHaval::K[] = {
    0x452821e6, 0x38d01377, 0xbe5466cf, 0x34e90c6c, 0xc0ac29b7, 0xc97c50dd, 0x3f84d5b5, 0xb5470917,
    0x9216d5d9, 0x8979fb1b, 0xd1310ba6, 0x98dfb5ac, 0x2ffd72db, 0xd01adfb7, 0xb8e1afed, 0x6a267e96,
    0xba7c9045, 0xf12c7f99, 0x24a19947, 0xb3916cf7, 0x0801f2e2, 0x858efc16, 0x636920d8, 0x71574e69,
    0xa458fea3, 0xf4933d7e, 0x0d95748f, 0x728eb658, 0x718bcd58, 0x82154aee, 0x7b54a41d, 0xc25a59b5,
    0x9c30d539, 0x2af26013, 0xc5d1b023, 0x286085f0, 0xca417918, 0xb8db38ef, 0x8e79dcb0, 0x603a180e,
    0x6c9e0e8b, 0xb01e8a3e, 0xd71577c1, 0xbd314b27, 0x78af2fda, 0x55605c60, 0xe65525f3, 0xaa55ab94,
    0x57489862, 0x63e81440, 0x55ca396a, 0x2aab10b6, 0xb4cc5c34, 0x1141e8ce, 0xa15486af, 0x7c72e993,
    0xb3ee1411, 0x636fbc2a, 0x2ba9c55d, 0x741831f6, 0xce5c3e16, 0x9b87931e, 0xafd6ba33, 0x6c24cf5c,
    0x7a325381, 0x28958677, 0x3b8f4898, 0x6b4bb9af, 0xc4bfe81b, 0x66282193, 0x61d809cc, 0xfb21a991,
    0x487cac60, 0x5dec8032, 0xef845d5d, 0xe98575b1, 0xdc262302, 0xeb651b88, 0x23893e81, 0xd396acc5,
    0x0f6d6ff3, 0x83f44239, 0x2e0b4482, 0xa4842004, 0x69c8f04a, 0x9e1f9b5e, 0x21c66842, 0xf6e96c9a,
    0x670c9c61, 0xabd388f0, 0x6a51a0d2, 0xd8542f68, 0x960fa728, 0xab5133a3, 0x6eef0b6c, 0x137a3be4,
    0xba3bf050, 0x7efb2a98, 0xa1f1651d, 0x39af0176, 0x66ca593e, 0x82430e88, 0x8cee8619, 0x456f9fb4,
    0x7d84a5c3, 0x3b8b5ebe, 0xe06f75d8, 0x85c12073, 0x401a449f, 0x56c16aa6, 0x4ed3aa62, 0x363f7706,
    0x1bfedf72, 0x429b023d, 0x37d0d724, 0xd00a1248, 0xdb0fead3, 0x49f1c09b, 0x075372c9, 0x80991b7b,
    0x25d479d8, 0xf6e8def7, 0xe3fe501a, 0xb6794c3b, 0x976ce0bd, 0x04c006ba, 0xc1a94fb6, 0x409f60c4
};

CHaval::CHaval(int pass, int length) : CHash(1024, length)
{
    // How many passes
    switch (pass)
    {
    default:
    case 3:
        m_pass = 3;
        break;
    
    case 4:
        m_pass = 4;
        break;

    case 5:
        m_pass = 5;
        break;
    }

    // Magic init integers
    h[0] = 0x243f6a88;
    h[1] = 0x85a308d3;
    h[2] = 0x13198a2e;
    h[3] = 0x03707344;
    h[4] = 0xa4093822;
    h[5] = 0x299f31d0;
    h[6] = 0x082efa98;
    h[7] = 0xec4e6c89;
}

CHaval::~CHaval()
{
}

void CHaval::_hashBlock(const BYTE *pbBlock)
{
    // 1024 bit block
    DWORD w[32];
    DWORD t[8] = { 0, };

    memcpy(t, h, 32);
    CEndian::decodeLittle32(w, pbBlock, 128);

    _pass(t, w);

    for (int i = 0; i < 8; ++i)
        h[i] += t[i];
}

void CHaval::_padBlock(const BYTE *pbBlock, const QWORD qwLength)
{
    register DWORD dwBlockSize = (getBlockSize() >> 3);
    DWORD dwTailLength = (qwLength % dwBlockSize);
    DWORD dwPadding = dwBlockSize - dwTailLength;
    if (dwPadding <= 10) dwPadding += dwBlockSize;

    dwPadding += dwTailLength;

    PBYTE pbPaddingBlock = new (std::nothrow) BYTE[dwPadding];
    if (!pbPaddingBlock) return;

    memset(pbPaddingBlock, NULL, dwPadding);
    memcpy(pbPaddingBlock, pbBlock, dwTailLength);

    // First byte of padding
    pbPaddingBlock[dwTailLength] = 0x01;

    // Append length in bits
    WORD wUpperBits = ((WORD)getOutputSize() << 6) |
                      ((m_pass & 0x07) << 3) |
                      (HAVAL_VERSION & 0x07);
    QWORD qwBitLength = qwLength << 3;

    CEndian::encodeLittle16(&pbPaddingBlock[dwPadding - 10], &wUpperBits, 2);
    CEndian::encodeLittle64(&pbPaddingBlock[dwPadding - 8], &qwBitLength, 8);

    _hashBlock(pbPaddingBlock);

    // If there is one more padded block
    if (dwPadding > dwBlockSize)
        _hashBlock(pbPaddingBlock + dwBlockSize);

    _tailor(h);

    delete []pbPaddingBlock;
}

void CHaval::_finalize(BYTE *pbHash)
{
    CEndian::encodeLittle32(pbHash, h, getOutputSize() >> 3);
}

void CHaval::_pass(DWORD *t, const DWORD *w)
{
    DWORD dwRound = m_pass << 5;
    DWORD P, R;

    for (DWORD i = 0; i < dwRound; ++i)
    {
        // Pass 1
        if (i < 32)
        {
            if (m_pass == 3)
                P = f1(t[1], t[0], t[3], t[5], t[6], t[2], t[4]);
            else if (m_pass == 4)
                P = f1(t[2], t[6], t[1], t[4], t[5], t[3], t[0]);
            else
                P = f1(t[3], t[4], t[1], t[0], t[5], t[2], t[6]);

            R = ROR32(P, 7) + ROR32(t[7], 11) + *(w + i);
        }
        // Pass 2
        else if (i < 64)
        {
            if (m_pass == 3)
                P = f2(t[4], t[2], t[1], t[0], t[5], t[3], t[6]);
            else if (m_pass == 4)
                P = f2(t[3], t[5], t[2], t[0], t[1], t[6], t[4]);
            else
                P = f2(t[6], t[2], t[1], t[0], t[3], t[4], t[5]);

            R = ROR32(P, 7) + ROR32(t[7], 11) + *(w + wordOrder[(i - 32)]) + *(K + (i - 32));
        }
        // Pass 3
        else if (i < 96)
        {
            if (m_pass == 3)
                P = f3(t[6], t[1], t[2], t[3], t[4], t[5], t[0]);
            else if (m_pass == 4)
                P = f3(t[1], t[4], t[3], t[6], t[0], t[2], t[5]);
            else
                P = f3(t[2], t[6], t[0], t[4], t[3], t[1], t[5]);

            R = ROR32(P, 7) + ROR32(t[7], 11) + *(w + wordOrder[(i - 32)]) + *(K + (i - 32));
        }
        // Pass 4
        else if (i < 128)
        {
            if (m_pass == 4)
                P = f4(t[6], t[4], t[0], t[5], t[2], t[1], t[3]);
            else
                P = f4(t[1], t[5], t[3], t[2], t[0], t[4], t[6]);

            R = ROR32(P, 7) + ROR32(t[7], 11) + *(w + wordOrder[(i - 32)]) + *(K + (i - 32));
        }
        // Pass 5
        else
        {
            P = f5(t[2], t[5], t[0], t[6], t[4], t[3], t[1]);

            R = ROR32(P, 7) + ROR32(t[7], 11) + *(w + wordOrder[(i - 32)]) + *(K + (i - 32));
        }

        permutate(t, R);
    }
}

void CHaval::_tailor(DWORD *x)
{
    register DWORD temp;
    int length = getOutputSize();

    if (length == 128)
    {
        temp = (x[7] & 0x000000ff) |
               (x[6] & 0xff000000) |
               (x[5] & 0x00ff0000) |
               (x[4] & 0x0000ff00);

        x[0] += ROR32(temp, 8);

        temp = (x[7] & 0x0000ff00) |
               (x[6] & 0x000000ff) |
               (x[5] & 0xff000000) |
               (x[4] & 0x00ff0000);

        x[1] += ROR32(temp, 16);

        temp = (x[7] & 0x00ff0000) |
               (x[6] & 0x0000ff00) |
               (x[5] & 0x000000ff) |
               (x[4] & 0xff000000);

        x[2] += ROR32(temp, 24);

        temp = (x[7] & 0xff000000) |
               (x[6] & 0x00ff0000) |
               (x[5] & 0x0000ff00) |
               (x[4] & 0x000000ff);

        x[3] += temp;
    }
    else if (length == 160)
    {
        temp = (x[7] & 0x0000003f) |
               (x[6] & 0xfe000000) |
               (x[5] & 0x01f80000);

        x[0] += ROR32(temp, 19);

        temp = (x[7] & 0x00000fc0) |
               (x[6] & 0x0000003f) |
               (x[5] & 0xfe000000);

        x[1] += ROR32(temp, 25);

        temp = (x[7] & 0x0007f000) |
               (x[6] & 0x00000fc0) |
               (x[5] & 0x0000003f);

        x[2] += temp;

        temp = (x[7] & 0x01f80000) |
               (x[6] & 0x0007f000) |
               (x[5] & 0x00000fc0);

        x[3] += ROR32(temp, 6);

        temp = (x[7] & 0xfe000000) |
               (x[6] & 0x01f80000) |
               (x[5] & 0x0007f000);

        x[4] += ROR32(temp, 12);
    }
    else if (length == 192)
    {
        temp = (x[7] & 0x0000001f) |
               (x[6] & 0xfc000000);

        x[0] += ROR32(temp, 26);

        temp = (x[7] & 0x000003e0) |
               (x[6] & 0x0000001f);

        x[1] += temp;

        temp = (x[7] & 0x0000fc00) |
               (x[6] & 0x000003e0);

        x[2] += ROR32(temp, 5);

        temp = (x[7] & 0x001f0000) |
               (x[6] & 0x0000fc00);

        x[3] += ROR32(temp, 10);

        temp = (x[7] & 0x03e00000) |
               (x[6] & 0x001f0000);

        x[4] += ROR32(temp, 16);

        temp = (x[7] & 0xfc000000) |
               (x[6] & 0x03e00000);

        x[5] += ROR32(temp, 21);
    }
    else if (length == 224)
    {
        temp = x[7] & 0xf8000000;
        x[0] += ROR32(temp, 27);

        temp = x[7] & 0x07c00000;
        x[1] += ROR32(temp, 22);

        temp = x[7] & 0x003c0000;
        x[2] += ROR32(temp, 18);

        temp = x[7] & 0x0003e000;
        x[3] += ROR32(temp, 13);

        temp = x[7] & 0x00001e00;
        x[4] += ROR32(temp, 9);

        temp = x[7] & 0x000001f0;
        x[5] += ROR32(temp, 4);

        temp = x[7] & 0x0000000f;
        x[6] += temp;
    }

}