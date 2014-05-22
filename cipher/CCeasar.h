#pragma once

class CCeasar
{
public:
    CCeasar();
    ~CCeasar();

    void ceasarRotate(CString &strPlain, CString &strRot, int rot);
    void ceasarBruteforce(CString &strPlain, CString &strRot);

private:
};