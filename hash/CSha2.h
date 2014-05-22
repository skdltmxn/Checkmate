#pragma once

#include "CHash.h"

class CSha2In512 : public CHash
{
public:
    explicit CSha2In512(int length);
    virtual ~CSha2In512();

protected:
    DWORD h[8];

private:
    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);

    static const DWORD k[];
};

class CSha2In1024: public CHash
{
public:
    explicit CSha2In1024(int length);
    virtual ~CSha2In1024();

protected:
    QWORD h[8];

private:
    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);

    static const QWORD k[];
};

// Sha2-224
class CSha224 : public CSha2In512
{
public:
    CSha224() : CSha2In512(224)
    {
        // Magic init integers
        h[0] = 0xc1059ed8;
        h[1] = 0x367cd507;
        h[2] = 0x3070dd17;
        h[3] = 0xf70e5939;
        h[4] = 0xffc00b31;
        h[5] = 0x68581511;
        h[6] = 0x64f98fa7;
        h[7] = 0xbefa4fa4;
    }

    virtual ~CSha224()
    {
    }

private:
};

// Sha2-256
class CSha256 : public CSha2In512
{
public:
    CSha256() : CSha2In512(256)
    {
        // Magic init integers
        h[0] = 0x6a09e667;
        h[1] = 0xbb67ae85;
        h[2] = 0x3c6ef372;
        h[3] = 0xa54ff53a;
        h[4] = 0x510e527f;
        h[5] = 0x9b05688c;
        h[6] = 0x1f83d9ab;
        h[7] = 0x5be0cd19;
    }

    virtual ~CSha256()
    {
    }

private:
};

// Sha2-384
class CSha384 : public CSha2In1024
{
public:
    CSha384() : CSha2In1024(384)
    {
        // Magic init integers
        h[0] = 0xcbbb9d5dc1059ed8;
        h[1] = 0x629a292a367cd507;
        h[2] = 0x9159015a3070dd17;
        h[3] = 0x152fecd8f70e5939;
        h[4] = 0x67332667ffc00b31;
        h[5] = 0x8eb44a8768581511;
        h[6] = 0xdb0c2e0d64f98fa7;
        h[7] = 0x47b5481dbefa4fa4;
    }

    virtual ~CSha384()
    {
    }

private:
};

// Sha2-512
class CSha512 : public CSha2In1024
{
public:
    CSha512() : CSha2In1024(512)
    {
        // Magic init integers
        h[0] = 0x6a09e667f3bcc908;
        h[1] = 0xbb67ae8584caa73b;
        h[2] = 0x3c6ef372fe94f82b;
        h[3] = 0xa54ff53a5f1d36f1;
        h[4] = 0x510e527fade682d1;
        h[5] = 0x9b05688c2b3e6c1f;
        h[6] = 0x1f83d9abfb41bd6b;
        h[7] = 0x5be0cd19137e2179;
    }

    virtual ~CSha512()
    {
    }

private:
};

// SHA2-512/224
class CSha512224 : public CSha2In1024
{
public:
    CSha512224() : CSha2In1024(224)
    {
        // Magic init integers
        h[0] = 0x8c3d37c819544da2;
        h[1] = 0x73e1996689dcd4d6;
        h[2] = 0x1dfab7ae32ff9c82;
        h[3] = 0x679dd514582f9fcf;
        h[4] = 0x0f6d2b697bd44da8;
        h[5] = 0x77e36f7304c48942;
        h[6] = 0x3f9d85a86a1d36c8;
        h[7] = 0x1112e6ad91d692a1;
    }

    virtual ~CSha512224()
    {
    }

private:
};

// SHA2-512/256
class CSha512256 : public CSha2In1024
{
public:
    CSha512256() : CSha2In1024(256)
    {
        // Magic init integers
        h[0] = 0x22312194fc2bf72c;
        h[1] = 0x9f555fa3c84c64c2;
        h[2] = 0x2393b86b6f53b151;
        h[3] = 0x963877195940eabd;
        h[4] = 0x96283ee2a88effe3;
        h[5] = 0xbe5e1e2553863992;
        h[6] = 0x2b0199fc2c85b8aa;
        h[7] = 0x0eb72ddc81c52ca2;
    }

    virtual ~CSha512256()
    {
    }

private:
};