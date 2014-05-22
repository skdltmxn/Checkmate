/*
 * CBase64.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CBase64 class
 *
 */

#include "stdafx.h"
#include "CBase64.h"

CBase64::CBase64()
    : CEncoding(true), m_szKey(_T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"))
{
}

CBase64::~CBase64()
{
}

DWORD CBase64::_encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength)
{
    LPTSTR szEnc;
    DWORD i, ret = 0;
    DWORD dwPadding = (3 - dwLength % 3) % 3;

    // Calculate encoded message length
    szEnc = new TCHAR[(dwLength + dwPadding) / 3 * 4 + 1];

    // 3 bytes secured
    for (i = 0; dwLength / 3; i += 3, dwLength -= 3)
    {
        DWORD dwBlock = ((pbPlain[i] << 16) | (pbPlain[i + 1] << 8) | pbPlain[i + 2]);

        szEnc[ret++] = m_szKey[(dwBlock >> 18) & 0x3F];
        szEnc[ret++] = m_szKey[(dwBlock >> 12) & 0x3F];
        szEnc[ret++] = m_szKey[(dwBlock >> 6) & 0x3F];
        szEnc[ret++] = m_szKey[dwBlock & 0x3F];
    }

    // Process rest of message if necessary (padding)
    if (dwLength)
    {
        DWORD dwBlock = 0;

        if (dwLength == 1)
        {
            dwBlock = pbPlain[i] << 16;
            szEnc[ret++] = m_szKey[(dwBlock >> 18) & 0x3F];
            szEnc[ret++] = m_szKey[(dwBlock >> 12) & 0x3F];
            szEnc[ret++] = '=';
            szEnc[ret++] = '=';
        }
        else if (dwLength == 2)
        {
            dwBlock = ((pbPlain[i] << 16) | (pbPlain[i + 1] << 8));
            szEnc[ret++] = m_szKey[(dwBlock >> 18) & 0x3F];
            szEnc[ret++] = m_szKey[(dwBlock >> 12) & 0x3F];
            szEnc[ret++] = m_szKey[(dwBlock >> 6) & 0x3F];
            szEnc[ret++] = '=';
        }
    }

    szEnc[ret] = '\0';

    strEnc = szEnc; 
    delete[] szEnc;

    return ret;
}

DWORD CBase64::_decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength)
{
    LPTSTR szEnc;
    LPTSTR szDec;
    DWORD i, ret = 0;
    CString strEnc(pbEnc);

    strEnc.Remove('\r');
    strEnc.Remove('\n');
    strEnc.Remove('\t');
    strEnc.Remove(' ');

    if (dwLength % 4 != 0)
    {
        for (DWORD i = 0; i < (4 - dwLength % 4); i++)
            strEnc += "=";

        dwLength += (4 - dwLength % 4);
    }

    szEnc = strEnc.GetBuffer(dwLength);
    szDec = new TCHAR[dwLength];

    // 4 bytes secured
    for (i = 0; i <= dwLength - 4; i += 4)
    {
        DWORD dwBlock = 0;
        dwBlock |= ((lookupIndex(szEnc[i]) & 0x3F) << 18);
        dwBlock |= ((lookupIndex(szEnc[i + 1]) & 0x3F) << 12);
        dwBlock |= ((lookupIndex(szEnc[i + 2]) & 0x3F) << 6);
        dwBlock |= (lookupIndex(szEnc[i + 3]) & 0x3F);

        szDec[ret++] = (dwBlock >> 16) & 0xFF;
        szDec[ret++] = (dwBlock >> 8) & 0xFF;
        szDec[ret++] = (dwBlock & 0xFF);
    }

    // Handle last block (padding)
    int dwPadding = 0;
    DWORD dwBlock = 0;

    for (int j = 0; j < 4; j++)
    {
        if (szEnc[i + j] == '=') dwPadding++;
        dwBlock |= ((lookupIndex(szEnc[i + j]) & 0x3F) << (6 * (3 - j)));
    }

    if (dwPadding)
    {
        if (dwPadding == 1)
        {
            szDec[ret++] = (dwBlock >> 16) & 0xFF;
            szDec[ret++] = (dwBlock >> 8) & 0xFF;
        }
        else if (dwPadding == 2)
        {
            szDec[ret++] = (dwBlock >> 16) & 0xFF;
        }
    }


    szDec[ret] = '\0';
    strDec = szDec;

    delete[] szDec;

    return ret;
}

int CBase64::lookupIndex(TCHAR c)
{
    for (int i = 0; i < lstrlen(m_szKey); i++)
    {
        if (m_szKey[i] == c) return i;
    }

    return 0;
}