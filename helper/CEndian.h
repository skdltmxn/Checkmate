#pragma once

class CEndian
{
public:
    CEndian();
    ~CEndian();

    /* 16-bits */
    static void encodeLittle16(BYTE *pbOutput, const WORD *pwInput, const DWORD dwLength);
    static void decodeLittle16(WORD *pwOutput, const BYTE *pbInput, const DWORD dwLength);
    static void encodeBig16(BYTE *pbOutput, const WORD *pwInput, const DWORD dwLength);
    static void decodeBig16(WORD *pwOutput, const BYTE *pbInput, const DWORD dwLength);

    /* 32-bits */
    static void encodeLittle32(BYTE *pbOutput, const DWORD *pdwInput, const DWORD dwLength);
    static void decodeLittle32(DWORD *pdwOutput, const BYTE *pbInput, const DWORD dwLength);
    static void encodeBig32(BYTE *pbOutput, const DWORD *pdwInput, const DWORD dwLength);
    static void decodeBig32(DWORD *pdwOutput, const BYTE *pbInput, const DWORD dwLength);

    /* 64-bits */
    static void encodeLittle64(BYTE *pbOutput, const QWORD *pqwInput, const DWORD dwLength);
    static void decodeLittle64(QWORD *pqwOutput, const BYTE *pbInput, const DWORD dwLength);
    static void encodeBig64(BYTE *pbOutput, const QWORD *pqwInput, const DWORD dwLength);
    static void decodeBig64(QWORD *pqwOutput, const BYTE *pbInput, const DWORD dwLength);
};