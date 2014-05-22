/*
 * CHash.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements CHash class
 *
 */

#include "stdafx.h"
#include "CHash.h"

CHash::CHash(const DWORD dwBlockSize, const DWORD dwOutputSize)
    : m_dwBlockSize(dwBlockSize), m_dwOutputSize(dwOutputSize), m_pbHash(NULL)
{
}

CHash::~CHash()
{
    if (m_pbHash)
        delete[] m_pbHash;
}

void CHash::digestString(const CString &strPlain)
{
    int iPlainLength = strPlain.GetLength();
    int iDigestLength = (getOutputSize() >> 3);

    m_pbHash = new (std::nothrow) BYTE[iDigestLength];
    if (!m_pbHash) return;

    memset(m_pbHash, NULL, iDigestLength);

    LPCTSTR plain = (LPCTSTR)strPlain;
    CHAR *mbsPlain = NULL;

#ifdef UNICODE
    mbsPlain = new (std::nothrow) CHAR[iPlainLength + 1];
    if (!mbsPlain) return;

    mbsPlain[wcstombs(mbsPlain, plain, iPlainLength)] = '\0';
#else
    mbsPlain = plain;
#endif

    _digestString((BYTE *)mbsPlain, m_pbHash, iPlainLength);

#ifdef UNICODE
    delete[] mbsPlain;
#endif
}

void CHash::_digestString(const BYTE *pbPlain, BYTE *pbHash, QWORD qwLength)
{
    int iBlockLength = (getBlockSize() >> 3);
    QWORD qwLengthSaved = qwLength;
    
    // Hash each block
    while (qwLength >= iBlockLength)
    {
        _hashBlock(pbPlain);

        pbPlain += iBlockLength;
        qwLength -= iBlockLength;
    }

    _padBlock(pbPlain, qwLengthSaved);
    _finalize(pbHash);
}

bool CHash::digestFile(const CString &strFileName)
{
    CFile file;
    if (!file.Open(strFileName, CFile::modeRead))
    {
        AfxMessageBox(_T("File not found"), MB_ICONERROR);
        return false;
    }

    BYTE *pbBuffer = NULL;
    DWORD dwBlockLength = (getBlockSize() >> 3);
    DWORD dwBufferLength = dwBlockLength << 14; // Approx. 1MB
    pbBuffer = new (std::nothrow) BYTE[dwBufferLength];
    if (!pbBuffer)
        return false;

    DWORD dwDigestLength = (getOutputSize() >> 3);
    m_pbHash = new (std::nothrow) BYTE[dwDigestLength];
    if (!m_pbHash)
        goto out;

    memset(m_pbHash, NULL, dwDigestLength);
    
    QWORD qwTotalLength = 0;
    UINT nRead = 0;
    BYTE *pbNow = pbBuffer;

    while ((nRead = file.Read(pbBuffer, dwBufferLength)) >= dwBlockLength)
    {
        pbNow = pbBuffer;
        qwTotalLength += nRead;
        do
        {
            _hashBlock(pbNow);
            pbNow += dwBlockLength;
            nRead -= dwBlockLength;
        } while (nRead >= dwBlockLength);
    }

    qwTotalLength += nRead;
    _padBlock(pbNow, qwTotalLength);
    _finalize(m_pbHash);

out:
    delete[] pbBuffer;
    file.Close();

    return true;
}

void CHash::toString(CString &strHash)
{
    static TCHAR charset[] = _T("0123456789abcdef");
    DWORD dwLength = (getOutputSize() >> 2);
    TCHAR *szHash = new (std::nothrow) TCHAR[dwLength + 1];

    if (szHash)
    {
        DWORD i;
        DWORD j;
        for (i = 0, j = 0; i < dwLength; i += 2, ++j)
        {
            BYTE p = *(m_pbHash + j);

            *(szHash + i)      =    charset[(p >> 4) & 0x0F];
            *(szHash + i + 1) = charset[p & 0x0F];
        }
        szHash[i] = '\0';

        strHash = szHash;

        delete[] szHash;
    }
    else
        strHash = _T("");
}