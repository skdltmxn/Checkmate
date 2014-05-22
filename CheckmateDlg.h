
// CheckmateDlg.h : header file
//

#pragma once
#include "afxwin.h"

class CHash;
class CEncoding;

// CCheckmateDlg dialog
class CCheckmateDlg : public CDialog
{
// Construction
public:
    CCheckmateDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    enum { IDD = IDD_CHECKMATE_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDropFiles(HDROP hDropInfo);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    DECLARE_MESSAGE_MAP()

private:
    static BOOL IsEdit(CWnd *pWnd);
    void PerformHash(CHash &hash);

    enum { ENCODE = 1, DECODE };
    void PerformEncoding(CEncoding &encoding, int what);

public:
    afx_msg void OnBase64Encode();
    afx_msg void OnHelpExit();
    afx_msg void OnHelpAbout();

private:
    CEdit m_editBefore;
    CEdit m_editAfter;
    BOOL m_bFileHash;
    CEdit m_editFilePath;

public:
    afx_msg void OnBase64Decode();
    afx_msg void OnBnClickedButtonSwitch();
    afx_msg void OnBase85Encode();
    afx_msg void OnL33tEncode();
    afx_msg void OnL33tDecode();
    afx_msg void OnBase85Decode();
    afx_msg void OnUrlEncode();
    afx_msg void OnUrlDecode();
    afx_msg void OnHashesMd5();
    afx_msg void OnCiphersCeasarbruteforce();
    afx_msg void OnCiphersRot();
    afx_msg void OnEtcReverse();
    afx_msg void OnHashesSha1();
    afx_msg void OnEtcUppercase();
    afx_msg void OnEtcLowercase();
    afx_msg void OnHashesSha2256();
    afx_msg void OnHashesSha2512();
    afx_msg void OnHashesRipemd();
    afx_msg void OnHashesMd4();
    afx_msg void OnHashesMd2();
    afx_msg void OnTiger3192();
    afx_msg void OnTiger3160();
    afx_msg void OnTiger3128();
    afx_msg void OnTiger4192();
    afx_msg void OnTiger4160();
    afx_msg void OnTiger4128();
    afx_msg void OnBinaryEncode();
    afx_msg void OnBinaryDecode();
    afx_msg void OnHexEncode();
    afx_msg void OnHexDecode();
    afx_msg void OnHaval3128();
    afx_msg void OnHaval3160();
    afx_msg void OnHaval3192();
    afx_msg void OnHaval3224();
    afx_msg void OnHaval3256();
    afx_msg void OnHaval4128();
    afx_msg void OnHaval4160();
    afx_msg void OnHaval4192();
    afx_msg void OnHaval4224();
    afx_msg void OnHaval4256();
    afx_msg void OnHaval5128();
    afx_msg void OnHaval5160();
    afx_msg void OnHaval5192();
    afx_msg void OnHaval5224();
    afx_msg void OnHaval5256();
    afx_msg void OnSha3224();
    afx_msg void OnSha3256();
    afx_msg void OnSha3384();
    afx_msg void OnSha3512();
    afx_msg void OnBnClickedButtonFileopen();
    afx_msg void OnBnClickedCheckFilehash();
    afx_msg void OnSha2224();
    afx_msg void OnSha2384();
    afx_msg void OnSha2512224();
    afx_msg void OnSha2512256();
    afx_msg void OnHashesWhirlpool();
};
