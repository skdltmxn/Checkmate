#pragma once

#include "CHash.h"

class CSha1 : public CHash
{
public:
    CSha1();
    virtual ~CSha1();

private:
    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);

    DWORD h[5];
};