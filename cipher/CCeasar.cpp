/*
 * CCeasar.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CCeasar class
 *
 */

#include "stdafx.h"
#include "CCeasar.h"

CCeasar::CCeasar()
{
}

CCeasar::~CCeasar()
{
}

void CCeasar::ceasarRotate(CString &strPlain, CString &strRot, int rot)
{
    if (rot < 0) rot += 26;
    rot %= 26;

    LPTSTR szPlain = strPlain.GetBuffer(strPlain.GetLength());

    for (int i = 0; i < strPlain.GetLength(); i++)
    {
        if (szPlain[i] >= 'a' && szPlain[i] <= 'z')
        {
            szPlain[i] += rot;
            if (szPlain[i] > 'z') szPlain[i] += ('a' - 'z' - 1);
        }
        else if (szPlain[i] >= 'A' && szPlain[i] <= 'Z')
        {
            szPlain[i] += rot;
            if (szPlain[i] > 'Z') szPlain[i] += ('A' - 'Z' - 1);
        }
    }

    strRot = szPlain;
}

void CCeasar::ceasarBruteforce(CString &strPlain, CString &strRot)
{
    for (int i = 1; i < 26; i++)
    {
        CString strOrg = strPlain;

        CString temp;
        ceasarRotate(strOrg, temp, i);

        strRot.Format(_T("%sROT-%d: %s\r\n"), strRot, i, temp);
    }
}