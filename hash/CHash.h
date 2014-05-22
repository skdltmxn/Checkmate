#pragma once

#define ROL32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define ROR32(x, n) ROL32(x, 32 - (n))
#define ROL64(x, n) (((x) << (n)) | ((x) >> (64 - (n))))
#define ROR64(x, n) ROL64(x, 64 - (n))

class CHash
{
public:
    CHash(const DWORD iBlockSize, const DWORD iOutputSize);
    virtual ~CHash();

    inline DWORD getBlockSize() const
    {
        return m_dwBlockSize;
    }

    inline DWORD getOutputSize() const
    {
        return m_dwOutputSize;
    }

    void digestString(const CString &strPlain);
    bool digestFile(const CString &strFileName);
    void toString(CString &strHash);

protected:
    virtual void _hashBlock(const BYTE *pbBlock) = 0;
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength) = 0;
    virtual void _finalize(BYTE *pbHash) = 0;

private:
    void _digestString(const BYTE *pbPlain, BYTE *pbHash, QWORD qwLength);

    DWORD m_dwBlockSize; // Block size in bits
    DWORD m_dwOutputSize; // Output size in bits
    BYTE *m_pbHash; // Hashed binary
};