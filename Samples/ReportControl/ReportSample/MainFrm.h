// MainFrm.h : interface of the CMainFrame class
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2012 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1889C309_E868_436B_B21D_B8A8DCED019D__INCLUDED_)
#define AFX_MAINFRM_H__1889C309_E868_436B_B21D_B8A8DCED019D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CMainFrameBase CXTPFrameWnd, CXTPOffice2007FrameHook

class CFolderView;

class CMainFrame : public CMainFrameBase
{
	enum Skin
	{
		skinNone,
		skinOffice2007,
		skinOffice2010,
		skinVista
	};

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CDialogBar m_wndFieldChooser;   // Sample Field chooser window
	CDialogBar m_wndFilterEdit;     // Sample Filter editing window

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewSkinNone();
	afx_msg void OnUpdateViewSkinNone(CCmdUI* pCmdUI);
	afx_msg void OnViewSkinOffice2007();
	afx_msg void OnUpdateViewSkinOffice2007(CCmdUI* pCmdUI);
	afx_msg void OnViewSkinOffice2010();
	afx_msg void OnUpdateViewSkinOffice2010(CCmdUI* pCmdUI);
	afx_msg void OnViewSkinVista();
	afx_msg void OnUpdateViewSkinVista(CCmdUI* pCmdUI);
	//}}AFX_MSG

	afx_msg void OnCustomize();
	DECLARE_MESSAGE_MAP()

protected:
	LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	CXTPDockingPaneManager m_paneManager;
	CFolderView *m_pFolderView;

private:

	void SetSkin(Skin skin);

	Skin m_skin;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1889C309_E868_436B_B21D_B8A8DCED019D__INCLUDED_)
