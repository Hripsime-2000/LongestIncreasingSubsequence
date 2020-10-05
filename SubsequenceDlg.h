
// SubsequenceDlg.h : header file
//

#pragma once


// CSubsequenceDlg dialog
class CSubsequenceDlg : public CDialogEx
{
// Construction
public:
	CSubsequenceDlg(CWnd* pParent = nullptr);	// standard constructor
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUBSEQUENCE_DIALOG };
#endif

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

public:
	afx_msg void OnClickedEnterButton();
	afx_msg void OnClickedExitButton();
	CString m_enter;
	CString m_result;
	afx_msg void OnEnChangeResultEdit();

	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnEnChangeEnterEdit();
};
