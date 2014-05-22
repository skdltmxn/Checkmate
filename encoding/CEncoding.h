#pragma once

class CEncoding
{
public:
    CEncoding(const bool bFileSupport);
    virtual ~CEncoding();

    inline bool isFileSupported()
    {
        return m_bFileSupport;
    }

    inline CString &getResult()
    {
        return m_strResult;
    }

    void encodeString(const CString &strPlain);
    void decodeString(const CString &strEnc);
    bool encodeFile(CString &strFileName);
    bool decodeFile(CString &strFileName);
    

protected:
    virtual DWORD _encode(const BYTE *pbPlain, CString &strEnc, DWORD dwLength) = 0;
    virtual DWORD _decode(const BYTE *pbEnc, CString &strDec, DWORD dwLength) = 0;

private:
    const bool m_bFileSupport; // if current encoding supports files
    CString m_strResult; // result of en/decoding
};