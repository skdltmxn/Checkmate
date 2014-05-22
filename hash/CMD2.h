#pragma once

#include "CHash.h"

class CMD2 : public CHash
{
public:
    CMD2();
    virtual ~CMD2();

private:
    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);

    BYTE h[48];
    BYTE checksum[16];
    bool updateChecksum;

    static const BYTE s[];
};