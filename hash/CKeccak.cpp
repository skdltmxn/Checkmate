/*
 * CKeccak.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CKeccak class
 *
 */

#include "stdafx.h"
#include "CKeccak.h"
#include "../helper/CEndian.h"

const QWORD CKeccak::RC[] = {
    0x0000000000000001, 0x0000000000008082,
    0x800000000000808a, 0x8000000080008000,
    0x000000000000808b, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009,
    0x000000000000008a, 0x0000000000000088,
    0x0000000080008009, 0x000000008000000a,
    0x000000008000808b, 0x800000000000008b,
    0x8000000000008089, 0x8000000000008003,
    0x8000000000008002, 0x8000000000000080,
    0x000000000000800a, 0x800000008000000a,
    0x8000000080008081, 0x8000000000008080,
    0x0000000080000001, 0x8000000080008008
};

const int CKeccak::r[] = {
     0,  1, 62, 28, 27,
    36, 44,  6, 55, 20,
     3, 10, 43, 25, 39,
    41, 45, 15, 21,  8,
    18,  2, 61, 56, 14
};

CKeccak::CKeccak(int bitrate, int length) :
     CHash(bitrate, length), m_iBitRate(bitrate)
{
    memset(state, NULL, 200);
}

CKeccak::~CKeccak()
{
}

void CKeccak::_hashBlock(const BYTE *pbBlock)
{
    int lanes = m_iBitRate >> 6;

    // Absorb
    for (int i = 0; i < lanes; ++i)
        state[i] ^= ((QWORD *)pbBlock)[i];

    _round();
}

void CKeccak::_padBlock(const BYTE *pbBlock, const QWORD qwLength)
{
    register int iBlockSize = (getBlockSize() >> 3);
    DWORD dwTailLength = (qwLength % iBlockSize);
    DWORD dwPadding = iBlockSize;

    PBYTE pbPaddingBlock = new (std::nothrow) BYTE[iBlockSize];
    if (!pbPaddingBlock) return;

    memset(pbPaddingBlock, NULL, iBlockSize);
    memcpy(pbPaddingBlock, pbBlock, dwTailLength);

    // First byte of padding
    pbPaddingBlock[dwTailLength] = 0x01;
    pbPaddingBlock[iBlockSize - 1] |= 0x80;
    
    _hashBlock(pbPaddingBlock);

    delete []pbPaddingBlock;
}

void CKeccak::_finalize(BYTE *pbHash)
{
    CEndian::encodeLittle64(pbHash, state, getOutputSize() >> 3);
}

void CKeccak::_round()
{
    QWORD c[5];
    QWORD b[25];

    // 24 rounds
    for (int i = 0; i < 24; ++i)
    {
        // Theta step
        for (int x = 0; x < 5; ++x)
        {
            c[x] = state[x]         ^
                   state[x + 5]  ^
                   state[x + 10] ^
                   state[x + 15] ^
                   state[x + 20];
        }

        for (int x = 0; x < 5; ++x)
        {
            QWORD col = c[(x + 4) % 5] ^ ROL64(c[(x + 1) % 5], 1);
            state[x]      ^= col;
            state[x + 5]  ^= col;
            state[x + 10] ^= col;
            state[x + 15] ^= col;
            state[x + 20] ^= col;
        }

        register int pos = 0;
        // RoPi step
        for (int y = 0; y < 5; ++y)
        {
            for (int x = 0; x < 5; ++x)
            {
                int bpos = (10 * x + 16 * y) % 25;
                b[bpos] = ROL64(state[pos], r[pos]);
                ++pos;
            }
        }

        // Chi step
        for (int y = 0; y < 25; y += 5)
        {
            state[y] = b[y] ^ (~b[y + 1] & b[y + 2]);
            state[y + 1] = b[y + 1] ^ (~b[y + 2] & b[y + 3]);
            state[y + 2] = b[y + 2] ^ (~b[y + 3] & b[y + 4]);
            state[y + 3] = b[y + 3] ^ (~b[y + 4] & b[y]);
            state[y + 4] = b[y + 4] ^ (~b[y] & b[y + 1]);
        }

        // Iota step
        state[0] ^= RC[i];
    }
}