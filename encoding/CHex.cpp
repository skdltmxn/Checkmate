/*
 * CHex.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CHex class
 *
 */

#include "stdafx.h"
#include "CHex.h"

const char *CHex::charset = "0123456789ABCDEF";

CHex::CHex()
    : CEncoding(true)
{
}

CHex::~CHex()
{
}

DWORD CHex::_encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength)
{
    LPTSTR szEnc;
    DWORD i, ret = 0;

    szEnc = new TCHAR[dwLength * 3];

    for (i = 0; i < dwLength; ++i)
    {
        TCHAR c = *(pbPlain + i);

        szEnc[ret++] = charset[(c & 0xF0) >> 4];
        szEnc[ret++] = charset[(c & 0x0F)];
        szEnc[ret++] = ' ';
    }

    szEnc[--ret] = '\0';

    strEnc = szEnc;
    delete[] szEnc;

    return ret;
}

DWORD CHex::_decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength)
{
    LPTSTR szDec;
    DWORD i, ret = 0;
    DWORD dwDecLength = dwLength >> 1;
    bool bNewByte = true;

    if (!dwDecLength)
        return ret;

    szDec = new TCHAR[dwDecLength + 1];

    for (i = 0; i < dwLength; ++i)
    {
        TCHAR c = *(pbEnc + i);

        // make lowercase
        if (c >= 'a' && c <= 'z')
            c -= 0x20;

        if ((c < '0' || c > '9' ) && (c < 'A' || c > 'Z'))
            continue;
        
        if (bNewByte)
        {
            *(szDec + ret) = indexof(c) << 4;
            bNewByte = false;
        }
        else
        {
            *(szDec + ret++) |= indexof(c);
            bNewByte = true;
        }
    }

    szDec[ret] = '\0';

    strDec = szDec;
    delete[] szDec;

    return ret;
}

int CHex::indexof(TCHAR c)
{
    size_t i;
    int index = -1;
    size_t len = strlen(charset);

    for (i = 0; i < len; ++i)
    {
        if (*(charset + i) == c)
        {
            index = static_cast<int>(i);
            break;
        }
    }

    return index;
}