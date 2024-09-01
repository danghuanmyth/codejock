// CustomizeTreeDlg.h : header file
//

#if !defined(AFX_CUSTOMIZETREEDLG_H__B4660B45_07B1_4444_8269_15E65E26F2BD__INCLUDED_)
#define AFX_CUSTOMIZETREEDLG_H__B4660B45_07B1_4444_8269_15E65E26F2BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "CustomizeTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomizeTreeDlg dialog

class CCustomizeTreeDlg : public CDialog
{
// Construction
public:
	CCustomizeTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeTreeDlg)
	enum { IDD = IDD_CUSTOMIZETREE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CCustomizeTreeCtrl m_wndTreeCustomize;
	CCustomizeTreeCtrl m_wndTreeItems;


	// Generated message map functions
	//{{AFX_MSG(CCustomizeTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZETREEDLG_H__B4660B45_07B1_4444_8269_15E65E26F2BD__INCLUDED_)
