#if !defined(AFX_PAGEOVERLAYICONS_H__D71EE683_D83E_46EE_9892_81BB9C7DA0F0__INCLUDED_)
#define AFX_PAGEOVERLAYICONS_H__D71EE683_D83E_46EE_9892_81BB9C7DA0F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageOverlayIcons.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageOverlayIcons dialog

class CPageOverlayIcons : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageOverlayIcons)

// Construction
public:
	CPageOverlayIcons();
	~CPageOverlayIcons();

// Dialog Data
	//{{AFX_DATA(CPageOverlayIcons)
	enum { IDD = IDD_PAGE_OVERLAY_ICONS };
	CXTPButton	m_btnQuestion;
	CXTPButton	m_btnNoVolume;
	CXTPButton	m_tnNoIcon;
	CXTPButton	m_btnInfo;
	//}}AFX_DATA

	CXTPTaskbarManager m_mgrTaskBar;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageOverlayIcons)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageOverlayIcons)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonInfo();
	afx_msg void OnButtonQuestion();
	afx_msg void OnButtonNoVolume();
	afx_msg void OnButtonNoIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEOVERLAYICONS_H__D71EE683_D83E_46EE_9892_81BB9C7DA0F0__INCLUDED_)
