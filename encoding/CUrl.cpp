/*
 * CUrl.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CUrl class
 *
 */

#include "stdafx.h"
#include "CUrl.h"

CUrl::CUrl()
    : CEncoding(false)
{
}

CUrl::~CUrl()
{
}

DWORD CUrl::_encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength)
{
    CString strPlain(pbPlain);

    strPlain.Replace(_T("%"), _T("%25"));
    strPlain.Replace(_T("\t"), _T("%09"));
    strPlain.Replace(_T("\n"), _T("%0A"));
    strPlain.Replace(_T("\r"), _T("%0D"));
    strPlain.Replace(_T(" "), _T("%20"));
    strPlain.Replace(_T("!"), _T("%21"));
    strPlain.Replace(_T("\""), _T("%22"));
    strPlain.Replace(_T("#"), _T("%23"));
    strPlain.Replace(_T("$"), _T("%24"));
    strPlain.Replace(_T("&"), _T("%26"));
    strPlain.Replace(_T("'"), _T("%27"));
    strPlain.Replace(_T("("), _T("%28"));
    strPlain.Replace(_T(")"), _T("%29"));
    strPlain.Replace(_T("*"), _T("%2A"));
    strPlain.Replace(_T("+"), _T("%2B"));
    strPlain.Replace(_T(","), _T("%2C"));
    strPlain.Replace(_T("/"), _T("%2F"));
    strPlain.Replace(_T(":"), _T("%3A"));
    strPlain.Replace(_T(";"), _T("%3B"));
    strPlain.Replace(_T("<"), _T("%3C"));
    strPlain.Replace(_T("="), _T("%3D"));
    strPlain.Replace(_T(">"), _T("%3E"));
    strPlain.Replace(_T("?"), _T("%3F"));
    strPlain.Replace(_T("@"), _T("%40"));
    strPlain.Replace(_T("["), _T("%5B"));
    strPlain.Replace(_T("\\"), _T("%5C"));
    strPlain.Replace(_T("]"), _T("%5D"));
    strPlain.Replace(_T("^"), _T("%5E"));
    strPlain.Replace(_T("`"), _T("%60"));
    strPlain.Replace(_T("{"), _T("%7B"));
    strPlain.Replace(_T("|"), _T("%7C"));
    strPlain.Replace(_T("}"), _T("%7D"));
    strPlain.Replace(_T("~"), _T("%7E"));

    strEnc = strPlain;

    return dwLength;
}

DWORD CUrl::_decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength)
{
    CString strEnc(pbEnc);
    
    strEnc.Replace(_T("%09"), _T("\t"));
    strEnc.Replace(_T("%0A"), _T("\n"));
    strEnc.Replace(_T("%0a"), _T("\n"));
    strEnc.Replace(_T("%0D"), _T("\r"));
    strEnc.Replace(_T("%0d"), _T("\r"));
    strEnc.Replace(_T("%20"), _T(" "));
    strEnc.Replace(_T("%21"), _T("!"));
    strEnc.Replace(_T("%22"), _T("\""));
    strEnc.Replace(_T("%23"), _T("#"));
    strEnc.Replace(_T("%24"), _T("$"));
    strEnc.Replace(_T("%25"), _T("%"));
    strEnc.Replace(_T("%26"), _T("&"));
    strEnc.Replace(_T("%27"), _T("'"));
    strEnc.Replace(_T("%28"), _T("("));
    strEnc.Replace(_T("%29"), _T(")"));
    strEnc.Replace(_T("%2A"), _T("*"));
    strEnc.Replace(_T("%2a"), _T("*"));
    strEnc.Replace(_T("%2B"), _T("+"));
    strEnc.Replace(_T("%2b"), _T("+"));
    strEnc.Replace(_T("%2C"), _T(","));
    strEnc.Replace(_T("%2c"), _T(","));
    strEnc.Replace(_T("%2F"), _T("/"));
    strEnc.Replace(_T("%2f"), _T("/"));
    strEnc.Replace(_T("%3A"), _T(":"));
    strEnc.Replace(_T("%3a"), _T(":"));
    strEnc.Replace(_T("%3B"), _T(";"));
    strEnc.Replace(_T("%3b"), _T(";"));
    strEnc.Replace(_T("%3C"), _T("<"));
    strEnc.Replace(_T("%3c"), _T("<"));
    strEnc.Replace(_T("%3D"), _T("="));
    strEnc.Replace(_T("%3d"), _T("="));
    strEnc.Replace(_T("%3E"), _T(">"));
    strEnc.Replace(_T("%3e"), _T(">"));
    strEnc.Replace(_T("%3F"), _T("?"));
    strEnc.Replace(_T("%3f"), _T("?"));
    strEnc.Replace(_T("%40"), _T("@"));
    strEnc.Replace(_T("%5B"), _T("["));
    strEnc.Replace(_T("%5b"), _T("["));
    strEnc.Replace(_T("%5C"), _T("\\"));
    strEnc.Replace(_T("%5c"), _T("\\"));
    strEnc.Replace(_T("%5D"), _T("]"));
    strEnc.Replace(_T("%5d"), _T("]"));
    strEnc.Replace(_T("%5E"), _T("^"));
    strEnc.Replace(_T("%5e"), _T("^"));
    strEnc.Replace(_T("%60"), _T("`"));
    strEnc.Replace(_T("%7B"), _T("{"));
    strEnc.Replace(_T("%7b"), _T("{"));
    strEnc.Replace(_T("%7C"), _T("|"));
    strEnc.Replace(_T("%7c"), _T("|"));
    strEnc.Replace(_T("%7D"), _T("}"));
    strEnc.Replace(_T("%7d"), _T("}"));
    strEnc.Replace(_T("%7E"), _T("~"));
    strEnc.Replace(_T("%7e"), _T("~"));

    strDec = strEnc;

    return dwLength;
}