
// SmcutDlg.h : header file
//

#pragma once
#include <string>

#define TIMERID 0x10
typedef struct
{
	std::wstring vk_name;
	UINT8 vk_value;
}vk_t;

// CSmcutDlg dialog
class CSmcutDlg : public CDialogEx
{
// Construction
public:
	CSmcutDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SMCUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	UINT m_TimeOut;
	UINT m_TimerCount;
	BOOL m_Start;

	const vk_t m_vkMap[];

	afx_msg void OnEnChangeEditTimeout();
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	std::wstring GetKeyNameByValue(const UINT8 val);
	UINT8 GetKeyValueByName(const std::wstring name);
};
