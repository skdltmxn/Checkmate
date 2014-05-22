/*
 * CBase85.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CBase85 class
 *
 */

#include "stdafx.h"
#include "CBase85.h"

#define P4    52200625
#define P3    614125
#define P2    7225
#define P1    85

CBase85::CBase85()
    : CEncoding(true)
{
}

CBase85::~CBase85()
{
}

DWORD CBase85::_encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength)
{
    LPTSTR szEnc;
    DWORD i, ret = 0;
    DWORD dwPadding = (4 - dwLength % 4) % 4;

    szEnc = new TCHAR[(dwLength + dwPadding) / 4 * 5 + 1];

    // 4 bytes secured
    for (i = 0; dwLength / 4; i += 4, dwLength -= 4)
    {
        DWORD dwBlock = (pbPlain[i] << 24) | (pbPlain[i + 1] << 16) | (pbPlain[i + 2] << 8) | pbPlain[i + 3];

        szEnc[ret++] = (TCHAR)(dwBlock / P4 + 33);
        dwBlock %= P4;
        szEnc[ret++] = (TCHAR)(dwBlock / P3 + 33);
        dwBlock %= P3;
        szEnc[ret++] = (TCHAR)(dwBlock / P2 + 33);
        dwBlock %= P2;
        szEnc[ret++] = (TCHAR)(dwBlock / P1 + 33);
        szEnc[ret++] = (TCHAR)(dwBlock % P1 + 33);
    }

    // Process rest of message if necessary (padding)
    if (dwLength)
    {
        DWORD dwBlock = 0;
        for (int j = 0; dwLength--; i++, j++)
            dwBlock |= pbPlain[i] << (8 * (3 - j));

        szEnc[ret++] = (TCHAR)(dwBlock / P4 + 33);
        dwBlock %= P4;
        szEnc[ret++] = (TCHAR)(dwBlock / P3 + 33);
        dwBlock %= P3;
        szEnc[ret++] = (TCHAR)(dwBlock / P2 + 33);
        dwBlock %= P2;
        szEnc[ret++] = (TCHAR)(dwBlock / P1 + 33);
        szEnc[ret++] = (TCHAR)(dwBlock % P1 + 33);
    }
    
    szEnc[ret - dwPadding] = '\0';

    strEnc = "<~";
    strEnc += szEnc;
    strEnc += "~>";

    delete[] szEnc;

    return (ret - dwPadding);
}

DWORD CBase85::_decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength)
{
    LPTSTR szEnc;
    LPTSTR szDec;
    DWORD i, ret = 0;
    DWORD dwPadding;
    CString strEnc(pbEnc);

    strEnc.Remove('\r');
    strEnc.Remove('\n');
    strEnc.Remove('\t');
    strEnc.Remove(' ');

    dwLength = strEnc.GetLength();

    // Check valid format
    if (strEnc.Mid(0, 2) != _T("<~") || strEnc.Mid(dwLength - 2, 2) != _T("~>"))
    {
        strDec = "Invalid format!";
        return 0;
    }

    // Extract content
    strEnc = strEnc.Mid(2, dwLength - 4);
    dwLength = strEnc.GetLength();
    dwPadding = (5 - (dwLength % 5)) % 5;

    // Append 'u' if necessary
    if (dwPadding)
    {
        for (DWORD i = 0; i < dwPadding; i++)
            strEnc.Append(_T("u"));

        dwLength += dwPadding;
    }

    szEnc = strEnc.GetBuffer(dwLength);
    szDec = new TCHAR[dwLength / 5 * 4 + 1];

    // 5 bytes secured
    for (i = 0; i < dwLength; i += 5)
    {
        DWORD dwBlock = (szEnc[i] - 33) * P4 +
                        (szEnc[i + 1] - 33) * P3 + 
                        (szEnc[i + 2] - 33) * P2 + 
                        (szEnc[i + 3] - 33) * P1 + 
                        (szEnc[i + 4] - 33);

        szDec[ret++] = (dwBlock >> 24) & 0xFF;
        szDec[ret++] = (dwBlock >> 16) & 0xFF;
        szDec[ret++] = (dwBlock >> 8) & 0xFF;
        szDec[ret++] = dwBlock & 0xFF;
    }

    if (dwPadding)
        ret -= dwPadding;

    szDec[ret] = '\0';

    strDec = szDec;
    delete[] szDec;

    return ret;
}