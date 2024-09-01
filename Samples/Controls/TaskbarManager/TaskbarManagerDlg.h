// TaskbarManagerDlg.h : header file
//

#if !defined(AFX_TASKBARMANAGERDLG_H__0CA4C4B5_D3E7_4C2E_8D0A_225362631D09__INCLUDED_)
#define AFX_TASKBARMANAGERDLG_H__0CA4C4B5_D3E7_4C2E_8D0A_225362631D09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PageOverlayIcons.h"
#include "PageProgressBar.h"
#include "PageJumpList.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskbarManagerDlg dialog

class CTaskbarManagerDlg : public CPropertySheet
{
// Construction
public:
	CTaskbarManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTaskbarManagerDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaskbarManagerDlg)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CPageOverlayIcons m_pageOverlayIcons;
	CPageProgressBar m_pageProgressBar;
	CPageJumpList m_pageJumpList;

	// Generated message map functions
	//{{AFX_MSG(CTaskbarManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKBARMANAGERDLG_H__0CA4C4B5_D3E7_4C2E_8D0A_225362631D09__INCLUDED_)
