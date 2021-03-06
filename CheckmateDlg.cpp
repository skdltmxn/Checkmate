/*
 * CheckmateDlg.cpp
 *
 *   Copyright (c) 2013-2014 skdltmxn <supershop@naver.com>
 *
 * Implements Checkmate dialog
 *
 */

#include "stdafx.h"
#include "Checkmate.h"
#include "CheckmateDlg.h"
#include "encoding/CBase64.h"
#include "encoding/CBase85.h"
#include "encoding/Cl33t.h"
#include "encoding/CUrl.h"
#include "encoding/CBinary.h"
#include "encoding/CHex.h"
#include "hash/CMD2.h"
#include "hash/CMD4.h"
#include "hash/CMD5.h"
#include "hash/CSha1.h"
#include "hash/CSha2.h"
#include "hash/CKeccak.h" // SHA-3
#include "hash/CRipemd.h"
#include "hash/CTiger.h"
#include "hash/CHaval.h"
#include "hash/CWhirlpool.h"
#include "cipher/CCeasar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    // Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetDlgItemText(IDC_STATIC_COPYLEFT, _T("Copyright (c) 2013-2014"));

    return TRUE;
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCheckmateDlg dialog




CCheckmateDlg::CCheckmateDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCheckmateDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON);
}

void CCheckmateDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_BEFORE, m_editBefore);
    DDX_Control(pDX, IDC_EDIT_AFTER, m_editAfter);
    DDX_Control(pDX, IDC_EDIT_FILEPATH, m_editFilePath);
}

BEGIN_MESSAGE_MAP(CCheckmateDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_DROPFILES()
    //}}AFX_MSG_MAP
    ON_COMMAND(ID_BASE64_ENCODE, &CCheckmateDlg::OnBase64Encode)
    ON_COMMAND(ID_HELP_EXIT, &CCheckmateDlg::OnHelpExit)
    ON_COMMAND(ID_HELP_ABOUT, &CCheckmateDlg::OnHelpAbout)
    ON_COMMAND(ID_BASE64_DECODE, &CCheckmateDlg::OnBase64Decode)
    ON_BN_CLICKED(IDC_BUTTON_SWITCH, &CCheckmateDlg::OnBnClickedButtonSwitch)
    ON_COMMAND(ID_BASE85_ENCODE, &CCheckmateDlg::OnBase85Encode)
    ON_COMMAND(ID_L33T_ENCODE, &CCheckmateDlg::OnL33tEncode)
    ON_COMMAND(ID_L33T_DECODE, &CCheckmateDlg::OnL33tDecode)
    ON_COMMAND(ID_BASE85_DECODE, &CCheckmateDlg::OnBase85Decode)
    ON_COMMAND(ID_URL_ENCODE, &CCheckmateDlg::OnUrlEncode)
    ON_COMMAND(ID_URL_DECODE, &CCheckmateDlg::OnUrlDecode)
    ON_COMMAND(ID_HASHES_MD5, &CCheckmateDlg::OnHashesMd5)
    ON_COMMAND(ID_CIPHERS_CEASARBRUTEFORCE, &CCheckmateDlg::OnCiphersCeasarbruteforce)
    ON_COMMAND(ID_CIPHERS_ROT, &CCheckmateDlg::OnCiphersRot)
    ON_COMMAND(ID_ETC_REVERSE, &CCheckmateDlg::OnEtcReverse)
    ON_COMMAND(ID_HASHES_SHA, &CCheckmateDlg::OnHashesSha1)
    ON_COMMAND(ID_ETC_UPPERCASE, &CCheckmateDlg::OnEtcUppercase)
    ON_COMMAND(ID_ETC_LOWERCASE, &CCheckmateDlg::OnEtcLowercase)
    ON_COMMAND(ID_HASHES_SHA256, &CCheckmateDlg::OnHashesSha2256)
    ON_COMMAND(ID_HASHES_SHA512, &CCheckmateDlg::OnHashesSha2512)
    ON_COMMAND(ID_HASHES_RIPEMD, &CCheckmateDlg::OnHashesRipemd)
    ON_COMMAND(ID_HASHES_MD4, &CCheckmateDlg::OnHashesMd4)
    ON_COMMAND(ID_HASHES_MD2, &CCheckmateDlg::OnHashesMd2)
    ON_COMMAND(ID_TIGER_3_192, &CCheckmateDlg::OnTiger3192)
    ON_COMMAND(ID_TIGER_3_160, &CCheckmateDlg::OnTiger3160)
    ON_COMMAND(ID_TIGER_3_128, &CCheckmateDlg::OnTiger3128)
    ON_COMMAND(ID_TIGER_4_192, &CCheckmateDlg::OnTiger4192)
    ON_COMMAND(ID_TIGER_4_160, &CCheckmateDlg::OnTiger4160)
    ON_COMMAND(ID_TIGER_4_128, &CCheckmateDlg::OnTiger4128)
    ON_COMMAND(ID_BINARY_ENCODE, &CCheckmateDlg::OnBinaryEncode)
    ON_COMMAND(ID_BINARY_DECODE, &CCheckmateDlg::OnBinaryDecode)
    ON_COMMAND(ID_HEX_ENCODE, &CCheckmateDlg::OnHexEncode)
    ON_COMMAND(ID_HEX_DECODE, &CCheckmateDlg::OnHexDecode)
    ON_COMMAND(ID_HAVAL_128BITS, &CCheckmateDlg::OnHaval3128)
    ON_COMMAND(ID_HAVAL_160BITS, &CCheckmateDlg::OnHaval3160)
    ON_COMMAND(ID_HAVAL_192BITS, &CCheckmateDlg::OnHaval3192)
    ON_COMMAND(ID_HAVAL_224BITS, &CCheckmateDlg::OnHaval3224)
    ON_COMMAND(ID_HAVAL_256BITS, &CCheckmateDlg::OnHaval3256)
    ON_COMMAND(ID_HAVAL_128BITS32836, &CCheckmateDlg::OnHaval4128)
    ON_COMMAND(ID_HAVAL_160BITS32837, &CCheckmateDlg::OnHaval4160)
    ON_COMMAND(ID_HAVAL_192BITS32838, &CCheckmateDlg::OnHaval4192)
    ON_COMMAND(ID_HAVAL_224BITS32839, &CCheckmateDlg::OnHaval4224)
    ON_COMMAND(ID_HAVAL_256BITS32840, &CCheckmateDlg::OnHaval4256)
    ON_COMMAND(ID_HAVAL_128BITS32841, &CCheckmateDlg::OnHaval5128)
    ON_COMMAND(ID_HAVAL_160BITS32842, &CCheckmateDlg::OnHaval5160)
    ON_COMMAND(ID_HAVAL_192BITS32843, &CCheckmateDlg::OnHaval5192)
    ON_COMMAND(ID_HAVAL_224BITS32844, &CCheckmateDlg::OnHaval5224)
    ON_COMMAND(ID_HAVAL_256BITS32845, &CCheckmateDlg::OnHaval5256)
    ON_COMMAND(ID_SHA_224BITS, &CCheckmateDlg::OnSha3224)
    ON_COMMAND(ID_SHA_256BITS, &CCheckmateDlg::OnSha3256)
    ON_COMMAND(ID_SHA_384BITS, &CCheckmateDlg::OnSha3384)
    ON_COMMAND(ID_SHA_512BITS, &CCheckmateDlg::OnSha3512)
    ON_BN_CLICKED(IDC_BUTTON_FILEOPEN, &CCheckmateDlg::OnBnClickedButtonFileopen)
    ON_BN_CLICKED(IDC_CHECK_FILEHASH, &CCheckmateDlg::OnBnClickedCheckFilehash)
    ON_COMMAND(ID_SHA_224BITS32852, &CCheckmateDlg::OnSha2224)
    ON_COMMAND(ID_SHA_384BITS32853, &CCheckmateDlg::OnSha2384)
    ON_COMMAND(ID_SHA_512, &CCheckmateDlg::OnSha2512224)
    ON_COMMAND(ID_SHA_513, &CCheckmateDlg::OnSha2512256)
    ON_COMMAND(ID_HASHES_WHIRLPOOL, &CCheckmateDlg::OnHashesWhirlpool)
END_MESSAGE_MAP()


// CCheckmateDlg message handlers

BOOL CCheckmateDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    DragAcceptFiles();
    SetDlgItemText(IDC_BUTTON_SWITCH, _T("↕"));
    m_bFileHash = false;

    return TRUE;
}

void CCheckmateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

void CCheckmateDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCheckmateDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CCheckmateDlg::OnDropFiles(HDROP hDropInfo)
{
    CString strFile;
    DWORD dwBufferLen = 0;

    dwBufferLen = DragQueryFile(hDropInfo, 0, NULL, 0);
    DragQueryFile(hDropInfo, 0, strFile.GetBuffer(dwBufferLen + 1), dwBufferLen + 1);
    strFile.ReleaseBuffer();

    m_editFilePath.SetWindowTextW(strFile);
    ((CButton *)GetDlgItem(IDC_CHECK_FILEHASH))->SetCheck(TRUE);
    m_bFileHash = TRUE;

    DragFinish(hDropInfo);
}

BOOL CCheckmateDlg::IsEdit(CWnd *pWnd)
{
    if (!pWnd) return FALSE;
    HWND hWnd = pWnd->GetSafeHwnd();
    if (hWnd == NULL)
        return FALSE;

    TCHAR szClassName[6];
    return ::GetClassName(hWnd, szClassName, 6) &&
        _tcsicmp(szClassName, _T("Edit")) == 0;
}

BOOL CCheckmateDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        // Ctrl-A
        if (pMsg->wParam == 'A' && GetKeyState(VK_CONTROL) < 0)
        {
            CWnd *wnd = GetFocus();
            if (wnd && IsEdit(wnd))
                ((CEdit *)wnd)->SetSel(0, -1);
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}

void CCheckmateDlg::PerformHash(CHash &hash)
{
    CString strAfter;

    // Hashing file
    if (m_bFileHash)
    {
        CString strPath;
        m_editFilePath.GetWindowText(strPath);

        if (!hash.digestFile(strPath))
            return;

        hash.toString(strAfter);

        m_editAfter.SetWindowText(strAfter);
    }
    else
    {
        CString strBefore;
        m_editBefore.GetWindowText(strBefore);

        hash.digestString(strBefore);
        hash.toString(strAfter);

        m_editAfter.SetWindowText(strAfter);
    }
}

/*
 * @brief Performs encoding
 * @param encoding: Encoding method
 *        what: 1 - encoding
 *              2 - decoding
 */
void CCheckmateDlg::PerformEncoding(CEncoding &encoding, int what)
{
    // Encoding file
    if (m_bFileHash)
    {
        CString strPath;
        m_editFilePath.GetWindowText(strPath);

        bool result = false;
        if (what == ENCODE)
            result = encoding.encodeFile(strPath);
        else
            result = encoding.decodeFile(strPath);

        if (!result)
            return;

        m_editAfter.SetWindowText(encoding.getResult());
    }
    else
    {
        CString strBefore;
        m_editBefore.GetWindowText(strBefore);

        if (what == ENCODE)
            encoding.encodeString(strBefore);
        else
            encoding.decodeString(strBefore);

        m_editAfter.SetWindowText(encoding.getResult());
    }
}

void CCheckmateDlg::OnBnClickedButtonSwitch()
{
    CString strBefore;
    CString strAfter;

    m_editBefore.GetWindowText(strBefore);
    m_editAfter.GetWindowText(strAfter);

    m_editBefore.SetWindowText(strAfter);
    m_editAfter.SetWindowText(strBefore);
}

void CCheckmateDlg::OnBnClickedButtonFileopen()
{
    CFileDialog cfd(TRUE,
        NULL,
        NULL,
        OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NONETWORKBUTTON,
        NULL,
        NULL,
        0,
        TRUE);

    if (cfd.DoModal() == IDOK)
        m_editFilePath.SetWindowText(cfd.GetPathName());
}

void CCheckmateDlg::OnBnClickedCheckFilehash()
{
    m_bFileHash = (m_bFileHash == FALSE);
}

void CCheckmateDlg::OnHelpExit()
{
    EndDialog(0);
}

void CCheckmateDlg::OnHelpAbout()
{
    CAboutDlg dlg;
    dlg.DoModal();
}

void CCheckmateDlg::OnBase64Encode()
{
    CBase64 b64;
    PerformEncoding(b64, ENCODE);
}

void CCheckmateDlg::OnBase64Decode()
{
    CBase64 b64;
    PerformEncoding(b64, DECODE);
}

void CCheckmateDlg::OnBase85Encode()
{
    CBase85 b85;
    PerformEncoding(b85, ENCODE);
}

void CCheckmateDlg::OnBase85Decode()
{
    CBase85 b85;
    PerformEncoding(b85, DECODE);
}

void CCheckmateDlg::OnL33tEncode()
{
    Cl33t l33t;
    PerformEncoding(l33t, ENCODE);
}

void CCheckmateDlg::OnL33tDecode()
{
    Cl33t l33t;
    PerformEncoding(l33t, DECODE);
}
void CCheckmateDlg::OnUrlEncode()
{
    CUrl url;
    PerformEncoding(url, ENCODE);
}

void CCheckmateDlg::OnUrlDecode()
{
    CUrl url;
    PerformEncoding(url, DECODE);
}

void CCheckmateDlg::OnBinaryEncode()
{
    CBinary binary;
    PerformEncoding(binary, ENCODE);
}

void CCheckmateDlg::OnBinaryDecode()
{
    CBinary binary;
    PerformEncoding(binary, DECODE);
}

void CCheckmateDlg::OnHexEncode()
{
    CHex hex;
    PerformEncoding(hex, ENCODE);
}

void CCheckmateDlg::OnHexDecode()
{
    CHex hex;
    PerformEncoding(hex, DECODE);
}

// MD2
void CCheckmateDlg::OnHashesMd2()
{
    CMD2 md2;
    PerformHash(md2);
}

// MD4
void CCheckmateDlg::OnHashesMd4()
{
    CMD4 md4;
    PerformHash(md4);
}

// MD5
void CCheckmateDlg::OnHashesMd5()
{
    CMD5 md5;
    PerformHash(md5);
}

void CCheckmateDlg::OnCiphersCeasarbruteforce()
{
    CString strBefore;
    m_editBefore.GetWindowText(strBefore);

    if (strBefore.IsEmpty()) return;

    CCeasar ceasar;
    CString strAfter;

    ceasar.ceasarBruteforce(strBefore, strAfter);

    m_editAfter.SetWindowText(strAfter);
}

void CCheckmateDlg::OnCiphersRot()
{
    CString strBefore;
    m_editBefore.GetWindowText(strBefore);

    if (strBefore.IsEmpty()) return;

    CCeasar ceasar;
    CString strAfter;

    ceasar.ceasarRotate(strBefore, strAfter, 13);

    m_editAfter.SetWindowText(strAfter);
}

void CCheckmateDlg::OnEtcReverse()
{
    CString strBefore;
    m_editBefore.GetWindowText(strBefore);

    if (strBefore.IsEmpty()) return;

    CString strAfter;

    strAfter = strBefore.MakeReverse();

    m_editAfter.SetWindowText(strAfter);
}

// SHA-1
void CCheckmateDlg::OnHashesSha1()
{
    CSha1 sha1;
    PerformHash(sha1);
}

void CCheckmateDlg::OnEtcUppercase()
{
    CString strBefore;
    m_editBefore.GetWindowText(strBefore);

    if (strBefore.IsEmpty()) return;

    CString strAfter;

    strAfter = strBefore.MakeUpper();

    m_editAfter.SetWindowText(strAfter);
}

void CCheckmateDlg::OnEtcLowercase()
{
    CString strBefore;
    m_editBefore.GetWindowText(strBefore);

    if (strBefore.IsEmpty()) return;

    CString strAfter;

    strAfter = strBefore.MakeLower();

    m_editAfter.SetWindowText(strAfter);
}

// SHA-2-256
void CCheckmateDlg::OnHashesSha2256()
{
    CSha256 sha256;
    PerformHash(sha256);
}

// SHA-2-512
void CCheckmateDlg::OnHashesSha2512()
{
    CSha512 sha512;
    PerformHash(sha512);
}

// Ripemd-160
void CCheckmateDlg::OnHashesRipemd()
{
    CRipemd ripemd;
    PerformHash(ripemd);
}

// Tiger-3-192
void CCheckmateDlg::OnTiger3192()
{
    CTiger tiger(0, 192);
    PerformHash(tiger);
}

// Tiger-3-160
void CCheckmateDlg::OnTiger3160()
{
    CTiger tiger(0, 160);
    PerformHash(tiger);
}

// Tiger-3-128
void CCheckmateDlg::OnTiger3128()
{
    CTiger tiger(0, 128);
    PerformHash(tiger);
}

// Tiger-4-192
void CCheckmateDlg::OnTiger4192()
{
    CTiger tiger(1, 192);
    PerformHash(tiger);
}

// Tiger-4-160
void CCheckmateDlg::OnTiger4160()
{
    CTiger tiger(1, 160);
    PerformHash(tiger);
}

// Tiger-4-128
void CCheckmateDlg::OnTiger4128()
{
    CTiger tiger(1, 128);
    PerformHash(tiger);
}

// HAVAL-3-128
void CCheckmateDlg::OnHaval3128()
{
    CHaval haval(3, 128);
    PerformHash(haval);
}

// HAVAL-3-160
void CCheckmateDlg::OnHaval3160()
{
    CHaval haval(3, 160);
    PerformHash(haval);
}

// HAVAL-3-192
void CCheckmateDlg::OnHaval3192()
{
    CHaval haval(3, 192);
    PerformHash(haval);
}

// HAVAL-3-224
void CCheckmateDlg::OnHaval3224()
{
    CHaval haval(3, 224);
    PerformHash(haval);
}

// HAVAL-3-256
void CCheckmateDlg::OnHaval3256()
{
    CHaval haval(3, 256);
    PerformHash(haval);
}

// HAVAL-4-128
void CCheckmateDlg::OnHaval4128()
{
    CHaval haval(4, 128);
    PerformHash(haval);
}

// HAVAL-4-160
void CCheckmateDlg::OnHaval4160()
{
    CHaval haval(4, 160);
    PerformHash(haval);
}

// HAVAL-4-192
void CCheckmateDlg::OnHaval4192()
{
    CHaval haval(4, 192);
    PerformHash(haval);
}

// HAVAL-4-224
void CCheckmateDlg::OnHaval4224()
{
    CHaval haval(4, 224);
    PerformHash(haval);
}

// HAVAL-4-256
void CCheckmateDlg::OnHaval4256()
{
    CHaval haval(4, 256);
    PerformHash(haval);
}

// HAVAL-5-128
void CCheckmateDlg::OnHaval5128()
{
    CHaval haval(5, 128);
    PerformHash(haval);
}

// HAVAL-5-160
void CCheckmateDlg::OnHaval5160()
{
    CHaval haval(5, 160);
    PerformHash(haval);
}

// HAVAL-5-192
void CCheckmateDlg::OnHaval5192()
{
    CHaval haval(5, 192);
    PerformHash(haval);
}

// HAVAL-5-224
void CCheckmateDlg::OnHaval5224()
{
    CHaval haval(5, 224);
    PerformHash(haval);
}

// HAVAL-5-256
void CCheckmateDlg::OnHaval5256()
{
    CHaval haval(5, 256);
    PerformHash(haval);
}

// SHA-3-224
void CCheckmateDlg::OnSha3224()
{
    CKeccak224 sha3;
    PerformHash(sha3);
}

// SHA-3-256
void CCheckmateDlg::OnSha3256()
{
    CKeccak256 sha3;
    PerformHash(sha3);
}

// SHA-3-384
void CCheckmateDlg::OnSha3384()
{
    CKeccak384 sha3;
    PerformHash(sha3);
}

// SHA-3-512
void CCheckmateDlg::OnSha3512()
{
    CKeccak512 sha3;
    PerformHash(sha3);
}

// SHA-2-224
void CCheckmateDlg::OnSha2224()
{
    CSha224 sha2;
    PerformHash(sha2);
}

// SHA-2-384
void CCheckmateDlg::OnSha2384()
{
    CSha384 sha2;
    PerformHash(sha2);
}

// SHA-2-512/224
void CCheckmateDlg::OnSha2512224()
{
    CSha512224 sha2;
    PerformHash(sha2);
}

// SHA-2-512/256
void CCheckmateDlg::OnSha2512256()
{
    CSha512256 sha2;
    PerformHash(sha2);
}
void CCheckmateDlg::OnHashesWhirlpool()
{
    CWhirlpool wp;
    PerformHash(wp);
}
