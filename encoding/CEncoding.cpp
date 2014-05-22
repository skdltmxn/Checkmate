/*
 * CEncoding.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CEncoding class
 *
 */

#include "stdafx.h"
#include "CEncoding.h"

#define BUFFER_SIZE    4096

CEncoding::CEncoding(const bool bFileSupport)
    : m_bFileSupport(bFileSupport)
{
}

CEncoding::~CEncoding()
{
}

void CEncoding::encodeString(const CString &strPlain)
{
    int iPlainLength = strPlain.GetLength();

    LPCTSTR plain = (LPCTSTR)strPlain;
    CHAR *mbsPlain = NULL;

#ifdef UNICODE
    mbsPlain = new (std::nothrow) CHAR[iPlainLength + 1];
    if (!mbsPlain) return;

    mbsPlain[wcstombs(mbsPlain, plain, iPlainLength)] = '\0';
#else
    mbsPlain = plain;
#endif

    _encode((BYTE *)mbsPlain, m_strResult, iPlainLength);

#ifdef UNICODE
    delete[] mbsPlain;
#endif
}

void CEncoding::decodeString(const CString &strEnc)
{
    int iPlainLength = strEnc.GetLength();

    LPCTSTR szEnc = (LPCTSTR)strEnc;
    CHAR *mbsEnc = NULL;

#ifdef UNICODE
    mbsEnc = new (std::nothrow) CHAR[iPlainLength + 1];
    if (!mbsEnc) return;

    mbsEnc[wcstombs(mbsEnc, szEnc, iPlainLength)] = '\0';
#else
    mbsPlain = plain;
#endif

    _decode((BYTE *)mbsEnc, m_strResult, iPlainLength);

#ifdef UNICODE
    delete[] mbsEnc;
#endif
}

bool CEncoding::encodeFile(CString &strFileName)
{
    if (isFileSupported() == false)
    {
        AfxMessageBox(_T("This encoding does not support files"), MB_ICONERROR);
        return false;
    }

    CFile file;
    if (!file.Open(strFileName, CFile::modeRead))
    {
        AfxMessageBox(_T("File not found"), MB_ICONERROR);
        return false;
    }

    DWORD dwLength = (DWORD)file.GetLength();
    UINT nRead = 0;
    BYTE *pbBuffer = new (std::nothrow) BYTE[dwLength];

    if (!pbBuffer)
    {
        AfxMessageBox(_T("Memory allocation failed"), MB_ICONERROR);
        file.Close();
        return false;
    }

    file.Read(pbBuffer, dwLength);

    _encode(pbBuffer, m_strResult, dwLength);

    delete[] pbBuffer;
    file.Close();
    return true;
}

bool CEncoding::decodeFile(CString &strFileName)
{
    if (isFileSupported() == false)
    {
        AfxMessageBox(_T("This encoding does not support files"), MB_ICONERROR);
        return false;
    }

    CFile file;
    if (!file.Open(strFileName, CFile::modeRead))
    {
        AfxMessageBox(_T("File not found"), MB_ICONERROR);
        return false;
    }

    DWORD dwLength = (DWORD)file.GetLength();
    UINT nRead = 0;
    BYTE *pbBuffer = new (std::nothrow) BYTE[dwLength];

    if (!pbBuffer)
    {
        AfxMessageBox(_T("Memory allocation failed"), MB_ICONERROR);
        file.Close();
        return false;
    }

    file.Read(pbBuffer, dwLength);

    _decode(pbBuffer, m_strResult, dwLength);

    delete[] pbBuffer;
    file.Close();
    return true;
}