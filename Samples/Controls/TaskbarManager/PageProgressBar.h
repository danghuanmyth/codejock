#if !defined(AFX_PAGEPROGRESSBAR_H__27CD5A09_EFEF_41CA_BD0F_35268CA3F3C3__INCLUDED_)
#define AFX_PAGEPROGRESSBAR_H__27CD5A09_EFEF_41CA_BD0F_35268CA3F3C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageProgressBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar dialog

class CPageProgressBar : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageProgressBar)

// Construction
public:
	CPageProgressBar();
	~CPageProgressBar();

// Dialog Data
	//{{AFX_DATA(CPageProgressBar)
	enum { IDD = IDD_PAGE_PROGRESS_BAR };
	int		m_nStatus;
	int		m_nValue;
	//}}AFX_DATA

	CXTPTaskbarManager m_mgrTaskBar;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageProgressBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageProgressBar)
	afx_msg void OnSelChangeComboStatus();
	afx_msg void OnReleasedCaptureSliderProgress(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEPROGRESSBAR_H__27CD5A09_EFEF_41CA_BD0F_35268CA3F3C3__INCLUDED_)
