/*
 * CEndian.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements endian helper class
 *
 */

#include "stdafx.h"
#include "CEndian.h"

CEndian::CEndian()
{
}

CEndian::~CEndian()
{
}

void CEndian::encodeLittle16(BYTE *pbOutput, const WORD *pwInput, const DWORD dwLength)
{
    for (DWORD i = 0, j = 0; j < dwLength; ++i, j += 2)
    {
        pbOutput[j] = (BYTE)(pwInput[i] & 0xFF);
        pbOutput[j + 1] = (BYTE)((pwInput[i] >> 8) & 0xFF);
    }
}

void CEndian::decodeLittle16(WORD *pwOutput, const BYTE *pbInput, const DWORD dwLength)
{
    for (DWORD i = 0, j = 0; j < dwLength; ++i, j += 2)
        pwOutput[i] = (pbInput[j] & 0xFF) |
                       (pbInput[j + 1] << 8);
}

void CEndian::encodeBig16(BYTE *pbOutput, const WORD *pwInput, const DWORD dwLength)
{
    for (DWORD i = 0, j = 0; j < dwLength; ++i, j += 2)
    {
        pbOutput[j + 1] = (BYTE)(pwInput[i] & 0xFF);
        pbOutput[j] = (BYTE)((pwInput[i] >> 8) & 0xFF);
    }
}

void CEndian::decodeBig16(WORD *pwOutput, const BYTE *pbInput, const DWORD dwLength)
{
    for (DWORD i = 0, j = 0; j < dwLength; ++i, j += 2)
        pwOutput[i] = (pbInput[j + 1] & 0xFF) |
                       (pbInput[j] << 8);
}

void CEndian::encodeLittle32(BYTE *pbOutput, const DWORD *pdwInput, const DWORD dwLength)
{
    DWORD i, j;
    DWORD dwRemain = dwLength;

    for (i = 0, j = 0; dwRemain >= 4; ++i, j += 4, dwRemain -= 4)
    {
        pbOutput[j] = (BYTE)(pdwInput[i] & 0xFF);
        pbOutput[j + 1] = (BYTE)((pdwInput[i] >> 8) & 0xFF);
        pbOutput[j + 2] = (BYTE)((pdwInput[i] >> 16) & 0xFF);
        pbOutput[j + 3] = (BYTE)((pdwInput[i] >> 24) & 0xFF);
    }

    if (dwRemain)
        CEndian::encodeLittle16(pbOutput + j, (WORD *)(pdwInput + i), dwRemain);
}

void CEndian::decodeLittle32(DWORD *pdwOutput, const BYTE *pbInput, const DWORD dwLength)
{
    for (DWORD i = 0, j = 0; j < dwLength; ++i, j += 4)
        pdwOutput[i] = (pbInput[j] & 0xFF) |
                       (pbInput[j + 1] << 8) |
                       (pbInput[j + 2] << 16) |
                       (pbInput[j + 3] << 24);
}

void CEndian::encodeBig32(BYTE *pbOutput, const DWORD *pdwInput, const DWORD dwLength)
{
    DWORD i, j;
    DWORD dwRemain = dwLength;

    for (i = 0, j = 0; dwRemain >= 4; ++i, j += 4, dwRemain -= 4)
    {
        pbOutput[j + 3] = (BYTE)(pdwInput[i] & 0xFF);
        pbOutput[j + 2] = (BYTE)((pdwInput[i] >> 8) & 0xFF);
        pbOutput[j + 1] = (BYTE)((pdwInput[i] >> 16) & 0xFF);
        pbOutput[j] = (BYTE)((pdwInput[i] >> 24) & 0xFF);
    }

    if (dwRemain)
        CEndian::encodeBig16(pbOutput + j, (WORD *)(pdwInput + i), dwRemain);
}

void CEndian::decodeBig32(DWORD *pdwOutput, const BYTE *pbInput, const DWORD dwLength)
{
    for (DWORD i = 0, j = 0; j < dwLength; ++i, j += 4)
        pdwOutput[i] = (pbInput[j + 3] & 0xFF) |
                       (pbInput[j + 2] << 8) |
                       (pbInput[j + 1] << 16) |
                       (pbInput[j] << 24);
}

void CEndian::encodeLittle64(BYTE *pbOutput, const QWORD *pqwInput, const DWORD dwLength)
{
    DWORD i, j;
    DWORD dwRemain = dwLength;

    for (i = 0, j = 0; dwRemain >= 8; ++i, j += 8, dwRemain -= 8)
    {
        pbOutput[j] = (BYTE)(pqwInput[i] & 0xFF);
        pbOutput[j + 1] = (BYTE)((pqwInput[i] >> 8) & 0xFF);
        pbOutput[j + 2] = (BYTE)((pqwInput[i] >> 16) & 0xFF);
        pbOutput[j + 3] = (BYTE)((pqwInput[i] >> 24) & 0xFF);
        pbOutput[j + 4] = (BYTE)((pqwInput[i] >> 32) & 0xFF);
        pbOutput[j + 5] = (BYTE)((pqwInput[i] >> 40) & 0xFF);
        pbOutput[j + 6] = (BYTE)((pqwInput[i] >> 48) & 0xFF);
        pbOutput[j + 7] = (BYTE)((pqwInput[i] >> 56) & 0xFF);
    }

    if (dwRemain)
        CEndian::encodeLittle32(pbOutput + j, (DWORD *)(pqwInput + i), dwRemain);
}

void CEndian::decodeLittle64(QWORD *pqwOutput, const BYTE *pbInput, const DWORD dwLength)
{
    for (DWORD i = 0, j = 0; j < dwLength; ++i, j += 8)
    {
        pqwOutput[i] = (((QWORD)pbInput[j]) & 0xff |
                        ((QWORD)pbInput[j + 1]) << 8 |
                        ((QWORD)pbInput[j + 2]) << 16 |
                        ((QWORD)pbInput[j + 3]) << 24 |
                        ((QWORD)pbInput[j + 4]) << 32 |
                        ((QWORD)pbInput[j + 5]) << 40 |
                        ((QWORD)pbInput[j + 6]) << 48 |
                        ((QWORD)pbInput[j + 7]) << 56);
                       
    }
}

void CEndian::encodeBig64(BYTE *pbOutput, const QWORD *pqwInput, const DWORD dwLength)
{
    DWORD i, j;
    DWORD dwRemain = dwLength;

    for (i = 0, j = 0; dwRemain >= 8; ++i, j += 8, dwRemain -= 8)
    {
        pbOutput[j + 7] = (BYTE)(pqwInput[i] & 0xFF);
        pbOutput[j + 6] = (BYTE)((pqwInput[i] >> 8) & 0xFF);
        pbOutput[j + 5] = (BYTE)((pqwInput[i] >> 16) & 0xFF);
        pbOutput[j + 4] = (BYTE)((pqwInput[i] >> 24) & 0xFF);
        pbOutput[j + 3] = (BYTE)((pqwInput[i] >> 32) & 0xFF);
        pbOutput[j + 2] = (BYTE)((pqwInput[i] >> 40) & 0xFF);
        pbOutput[j + 1] = (BYTE)((pqwInput[i] >> 48) & 0xFF);
        pbOutput[j] = (BYTE)((pqwInput[i] >> 56) & 0xFF);
    }

    if (dwRemain)
        CEndian::encodeBig32(pbOutput + j, (DWORD *)(pqwInput + i), dwRemain);
}

void CEndian::decodeBig64(QWORD *pqwOutput, const BYTE *pbInput, const DWORD dwLength)
{
    for (DWORD i = 0, j = 0; j < dwLength; ++i, j += 8)
    {
        pqwOutput[i] = (((QWORD)pbInput[j + 7]) & 0xff |
                        ((QWORD)pbInput[j + 6]) << 8 |
                        ((QWORD)pbInput[j + 5]) << 16 |
                        ((QWORD)pbInput[j + 4]) << 24 |
                        ((QWORD)pbInput[j + 3]) << 32 |
                        ((QWORD)pbInput[j + 2]) << 40 |
                        ((QWORD)pbInput[j + 1]) << 48 |
                        ((QWORD)pbInput[j]) << 56);
    }
}