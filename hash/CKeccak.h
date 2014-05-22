#pragma once

#include "CHash.h"

class CKeccak : public CHash
{
public:
    CKeccak(int bitrate, int length);
    virtual ~CKeccak();

private:
    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);

    void _round();

    QWORD state[25];
    int m_iBitRate;

    static const QWORD RC[];
    static const int r[];
};

class CKeccak224 : public CKeccak
{
public:
    CKeccak224() : CKeccak(1152, 224)
    {
    }

    virtual ~CKeccak224()
    {
    }
};

class CKeccak256 : public CKeccak
{
public:
    CKeccak256() : CKeccak(1088, 256)
    {
    }

    virtual ~CKeccak256()
    {
    }
};

class CKeccak384 : public CKeccak
{
public:
    CKeccak384() : CKeccak(832, 384)
    {
    }

    virtual ~CKeccak384()
    {
    }
};

class CKeccak512 : public CKeccak
{
public:
    CKeccak512() : CKeccak(576, 512)
    {
    }

    virtual ~CKeccak512()
    {
    }
};