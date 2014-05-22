/*
 * CBinary.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CBinary class
 *
 */

#include "stdafx.h"
#include "CBinary.h"

CBinary::CBinary()
    : CEncoding(true)
{
}

CBinary::~CBinary()
{
}

DWORD CBinary::_encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength)
{
    LPTSTR szEnc;
    DWORD i, ret = 0;

    szEnc = new TCHAR[(dwLength << 3) + dwLength];

    for (i = 0; i < dwLength; ++i)
    {
        TCHAR c = *(pbPlain + i);
        DWORD j;

        // Process 8 bits
        for (j = 0; j < 8; ++j)
            szEnc[ret++] = (c & (0x80 >> j)) ? _T('1') : _T('0');

        szEnc[ret++] = _T(' ');
    }

    szEnc[--ret] = _T('\0');

    strEnc = szEnc;
    delete[] szEnc;

    return ret;
}

DWORD CBinary::_decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength)
{
    LPTSTR szDec;
    DWORD i, ret = 0;
    int pos = 7;

    if (dwLength < 8)
    {
        strDec = _T("");
        return ret;
    }

    szDec = new TCHAR[(dwLength >> 3) + 1];

    for (i = 0; i < dwLength; ++i)
    {
        TCHAR c = *(pbEnc + i);

        // Skip non-binary
        if (c != _T('0') && c != _T('1'))
            continue;

        if (pos == 7)
            szDec[ret] = ((c - _T('0')) << pos--);
        else
            szDec[ret] |= ((c - _T('0')) << pos--);

        // Next character
        if (pos < 0)
        {
            ++ret;
            pos = 7;
        }
    }

    szDec[ret] = '\0';
    strDec = szDec;
    delete[] szDec;

    return ret;
}