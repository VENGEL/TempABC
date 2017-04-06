
// SmcutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Smcut.h"
#include "SmcutDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSmcutDlg dialog


const vk_t m_vkMap[] = { 
	{ L"LBUTTON", 0x01 },
	{ L"RBUTTON", 0x02 },
	{ L"CANCEL", 0x03 },
	{ L"MBUTTON", 0x04 },
	{ L"BACK", 0x08 },
	{ L"TAB", 0x09 },
	{ L"CLEAR", 0x0C },
	{ L"RETURN", 0x0D },
	{ L"SHIFT", 0x10 },
	{ L"CONTROL", 0x11 },
	{ L"MENU", 0x12 },
	{ L"PAUSE", 0x13 },
	{ L"CAPITAL", 0x14 },
	{ L"ESCAPE", 0x1B },
	{ L"SPACE", 0x20 },
	{ L"PRIOR", 0x21 },
	{ L"NEXT", 0x22 },
	{ L"END", 0x23 },
	{ L"HOME", 0x24 },
	{ L"LEFT", 0x25 },
	{ L"UP", 0x26 },
	{ L"RIGHT", 0x27 },
	{ L"DOWN", 0x28 },
	{ L"SELECT", 0x29 },
	{ L"EXECUTE", 0x2B },
	{ L"SNAPSHOT", 0x2C },
	{ L"INSERT", 0x2D },
	{ L"DELETE", 0x2E },
	{ L"HELP", 0x2F },
	{ L"LWIN", 0x5B },
	{ L"RWIN", 0x5C },
	{ L"APPS", 0x5D },
	{ L"NUMPAD0", 0x60 },
	{ L"NUMPAD1", 0x61 },
	{ L"NUMPAD2", 0x62 },
	{ L"NUMPAD3", 0x63 },
	{ L"NUMPAD4", 0x64 },
	{ L"NUMPAD5", 0x65 },
	{ L"NUMPAD6", 0x66 },
	{ L"NUMPAD7", 0x67 },
	{ L"NUMPAD8", 0x68 },
	{ L"NUMPAD9", 0x69 },
	{ L"MULTIPLY", 0x6A },
	{ L"ADD", 0x6B },
	{ L"SEPARATOR", 0x6C },
	{ L"SUBTRACT", 0x6D },
	{ L"DECIMAL", 0x6E },
	{ L"DIVIDE", 0x6F },
	{ L"F1", 0x70 },
	{ L"F2", 0x71 },
	{ L"F3", 0x72 },
	{ L"F4", 0x73 },
	{ L"F5", 0x74 },
	{ L"F6", 0x75 },
	{ L"F7", 0x76 },
	{ L"F8", 0x77 },
	{ L"F9", 0x78 },
	{ L"F10", 0x79 },
	{ L"F11", 0x7A },
	{ L"F12", 0x7B },
	{ L"F13", 0x7C },
	{ L"F14", 0x7D },
	{ L"F15", 0x7E },
	{ L"F16", 0x7F },
	{ L"F17", 0x80 },
	{ L"F18", 0x81 },
	{ L"F19", 0x82 },
	{ L"F20", 0x83 },
	{ L"F21", 0x84 },
	{ L"F22", 0x85 },
	{ L"F23", 0x86 },
	{ L"F24", 0x87 },
	{ L"NUMLOCK", 0x90 },
	{ L"SCROLL", 0x91 },
	{ L"ATTN", 0xF6 },
	{ L"CRSEL", 0xF7 },
	{ L"EXSEL", 0xF8 },
	{ L"EREOF", 0xF9 },
	{ L"PLAY", 0xFA },
	{ L"ZOOM", 0xFB },
	{ L"OEM_CLEAR", 0xFE } 
};

CSmcutDlg::CSmcutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmcutDlg::IDD, pParent)
	, m_TimeOut(0)
	, m_Start(FALSE)
	, m_TimerCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmcutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_TimeOut);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_TimerCount);
}

BEGIN_MESSAGE_MAP(CSmcutDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_TIMEOUT, &CSmcutDlg::OnEnChangeEditTimeout)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CSmcutDlg::OnBnClickedButtonRun)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSmcutDlg message handlers

BOOL CSmcutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSmcutDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSmcutDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSmcutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSmcutDlg::OnEnChangeEditTimeout()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	if (!(m_TimeOut < INT_MAX))
	{
		MessageBox(L"超出最大值！");
		m_TimeOut = 0;
		UpdateData(FALSE);
	}
}


void CSmcutDlg::OnBnClickedButtonRun()
{
	// TODO: Add your control notification handler code here
	if (!m_Start)
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SHORTCUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RUN)->SetWindowText(L"停止");
		m_Start = TRUE;
		SetTimer(TIMERID, m_TimeOut, 0);
	}
	else
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SHORTCUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RUN)->SetWindowText(L"启动");
		KillTimer(TIMERID);
		m_Start = FALSE;
	}
}


void CSmcutDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == TIMERID)
	{
		// TODO: 执行shortcut
		keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

		m_TimerCount++;
		UpdateData(FALSE);
	}

	CDialogEx::OnTimer(nIDEvent);
}

std::wstring CSmcutDlg::GetKeyNameByValue(const UINT8 val)
{
	INT iSize = sizeof(m_vkMap) / sizeof(m_vkMap[0]);

	for (INT i = 0; i < iSize; i++)
	{
		if (m_vkMap[i].vk_value == val) return m_vkMap[i].vk_name;
	}

	return L"";
}

UINT8 CSmcutDlg::GetKeyValueByName(const std::wstring name)
{
	INT iSize = sizeof(m_vkMap) / sizeof(m_vkMap[0]);

	for (INT i = 0; i < iSize; i++)
	{
		if (m_vkMap[i].vk_name == name) return m_vkMap[i].vk_value;
	}

	return 0;
}