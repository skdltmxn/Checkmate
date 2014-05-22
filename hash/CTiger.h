#pragma once

#include "CHash.h"

class CTiger : public CHash
{
public:
    CTiger(int exPass = 0, int length = 128);
    virtual ~CTiger();

private:
    virtual void _hashBlock(const BYTE *pbBlock);
    virtual void _padBlock(const BYTE *pbBlock, const QWORD qwLength);
    virtual void _finalize(BYTE *pbHash);
    void _pass(QWORD &a, QWORD &b, QWORD &c, const QWORD *w, const DWORD mul);
    void _keySchedule(QWORD *w);

    QWORD h[3];
    int m_exPass;

    static const QWORD sbox[];
};