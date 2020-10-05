
// SubsequenceDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Subsequence.h"
#include "SubsequenceDlg.h"
#include "afxdialogex.h"
#include<string>
#include<cstring>
#include<sstream>
#include <stdio.h> 
#include <stdlib.h> 
#include<stack>
#include<cstdio>


#ifdef _DEBUG
#define new DEBUG_NEW
#define BLUE       RGB(  0,  0,127)
#endif
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;
void find_lis(vector<int>& a, vector<int>& b)
{
	vector<int> p(a.size());
	int u, v;

	if (a.empty()) return;

	b.push_back(0);

	for (size_t i = 1; i < a.size(); i++)
	{
		// If next element a[i] is greater than last element of
		// current longest subsequence a[b.back()], just push it at back of "b" and continue
		if (a[b.back()] < a[i])
		{
			p[i] = b.back();
			b.push_back(i);
			continue;
		}

		// Binary search to find the smallest element referenced by b which is just bigger than a[i]
		// Note : Binary search is performed on b (and not a).
		// Size of b is always <=k and hence contributes O(log k) to complexity.    
		for (u = 0, v = b.size() - 1; u < v;)
		{
			int c = (u + v) / 2;
			if (a[b[c]] < a[i]) u = c + 1; else v = c;
		}

		// Update b if new value is smaller then previously referenced value 
		if (a[i] < a[b[u]])
		{
			if (u > 0) p[i] = b[u - 1];
			b[u] = i;
		}
	}

	for (u = b.size(), v = b.back(); u--; v = p[v]) b[u] = v;
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSubsequenceDlg dialog



CSubsequenceDlg::CSubsequenceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUBSEQUENCE_DIALOG, pParent)
	, m_enter(_T(""))
	, m_result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSubsequenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ENTER_EDIT, m_enter);
	DDX_Text(pDX, IDC_RESULT_EDIT, m_result);
}

BEGIN_MESSAGE_MAP(CSubsequenceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENTER_BUTTON, &CSubsequenceDlg::OnClickedEnterButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CSubsequenceDlg::OnClickedExitButton)
	ON_EN_CHANGE(IDC_RESULT_EDIT, &CSubsequenceDlg::OnEnChangeResultEdit)
	ON_EN_CHANGE(IDC_ENTER_EDIT, &CSubsequenceDlg::OnEnChangeEnterEdit)
END_MESSAGE_MAP()


// CSubsequenceDlg message handlers

BOOL CSubsequenceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

void CSubsequenceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSubsequenceDlg::OnPaint()
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
HCURSOR CSubsequenceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CSubsequenceDlg::OnClickedEnterButton()
{
	// TODO: Add your control notification handler code h
	CString cstring;

	GetDlgItemText(IDC_ENTER_EDIT, cstring);
	CT2CA  pszName(cstring);//MFC CString to a std::string
	std::string s(pszName);
	std::stringstream iss(s);//string to int array
	int number;
	std::vector<int>arrNum;
	while (iss >> number) {//read  from the stringstream object,
		arrNum.push_back(number);
	}
	/*int c = sizeof(arrNum) / sizeof(arrNum[0]);
	vector<int> seq(arrNum, arrNum+c);*/ // seq : Input Vector
	vector<int> lis;                              // lis : Vector containing indexes of longest subsequence 
	find_lis(arrNum, lis);
	vector<int>a;
	//Printing actual output 
	for (size_t i = 0; i < lis.size(); i++) {
		a.push_back(arrNum[lis[i]]);
		printf("\n");
	}
	
  
	
	std::stringstream ss1;
	copy(a.begin(), a.end(), ostream_iterator<int>(ss1, " "));
	std::string s1=ss1.str();
	CString cstring1(CA2T(s1.c_str()));

	

		
	SetDlgItemText(IDC_RESULT_EDIT, cstring1);

}


void CSubsequenceDlg::OnClickedExitButton()
{
	// TODO: Add your control notification handler code here
	OnOK();

}




void CSubsequenceDlg::OnEnChangeResultEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

HBRUSH CSubsequenceDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (pWnd->GetDlgCtrlID() == IDC_RESULT_EDIT)
	{
	
		
			pDC->SetTextColor(RGB(0, 0, 127));
			//hBrush = m_result;
		
	}
	return hBrush;
}



void CSubsequenceDlg::OnEnChangeEnterEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
