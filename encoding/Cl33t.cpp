/*
 * Cl33t.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements Cl33t class
 *
 */

#include "stdafx.h"
#include "Cl33t.h"

Cl33t::Cl33t()
    : CEncoding(false)
{
}

Cl33t::~Cl33t()
{
}

DWORD Cl33t::_encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength)
{
    CString strPlain(pbPlain);

    strPlain.Replace('a', '4');
    strPlain.Replace('A', '4');

    strPlain.Replace('e', '3');
    strPlain.Replace('E', '3');

    strPlain.Replace('s', '5');
    strPlain.Replace('S', '5');

    strPlain.Replace('o', '0');
    strPlain.Replace('O', '0');

    strPlain.Replace('t', '7');
    strPlain.Replace('T', '7');

    strPlain.Replace('i', '1');
    strPlain.Replace('I', '1');

    strEnc = strPlain;

    return dwLength;
}

DWORD Cl33t::_decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength)
{
    CString strEnc(pbEnc);

    strEnc.Replace('4', 'a');
    strEnc.Replace('3', 'e');
    strEnc.Replace('5', 's');
    strEnc.Replace('0', 'o');
    strEnc.Replace('7', 't');
    strEnc.Replace('1', 'i');

    strDec = strEnc;

    return dwLength;
}