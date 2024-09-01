// MainFrm.cpp : implementation of the CMainFrame class
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

#include "StdAfx.h"
#include "ReportSample.h"
#include "FolderView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND_EX(ID_TEST_FIELDCHOOSER, OnBarCheck)
	ON_COMMAND_EX(ID_TEST_FILTERWINDOW, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_TEST_FIELDCHOOSER, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(ID_TEST_FILTERWINDOW, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SKIN_NONE, OnUpdateViewSkinNone)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SKIN_OFFICE_2007, OnUpdateViewSkinOffice2007)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SKIN_OFFICE_2010, OnUpdateViewSkinOffice2010)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SKIN_VISTA, OnUpdateViewSkinVista)
	//}}AFX_MSG_MAP

#if defined(_XTP_INCLUDE_SKINFRAMEWORK) && !defined(_XTP_EXCLUDE_SKINFRAMEWORK)
	ON_COMMAND(ID_VIEW_SKIN_NONE,        OnViewSkinNone)
	ON_COMMAND(ID_VIEW_SKIN_OFFICE_2007, OnViewSkinOffice2007)
	ON_COMMAND(ID_VIEW_SKIN_OFFICE_2010, OnViewSkinOffice2010)
	ON_COMMAND(ID_VIEW_SKIN_VISTA,       OnViewSkinVista)
#endif

	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)

	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: m_skin(skinNone)
	, m_pFolderView(NULL)
{
#if defined(_XTP_INCLUDE_SKINFRAMEWORK) && !defined(_XTP_EXCLUDE_SKINFRAMEWORK)
	XTPSkinManager()->SetAutoApplyNewWindows(TRUE);
#endif
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndStatusBar.Create(this) ||
		 !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	CXTPPaintManager::SetTheme(xtpThemeRibbon);

	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);

	CXTPToolBar *pStandardBar = pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pStandardBar || !pStandardBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	EnableOffice2007Frame(pCommandBars);

	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));


	EnableDocking(CBRS_ALIGN_ANY);

	// Initialize dialog bar m_wndFieldChooser
	if (!m_wndFieldChooser.Create(this, IDD_FIELDCHOOSER,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE, ID_TEST_FIELDCHOOSER))
		return -1;      // fail to create

	// Initialize dialog bar m_wndFilterEdit
	if (!m_wndFilterEdit.Create(this, IDD_FILTEREDIT,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE, ID_TEST_FILTERWINDOW))
		return -1;      // fail to create

	// docking for field chooser
	m_wndFieldChooser.EnableDocking(0);
	m_wndFieldChooser.SetWindowText(_T("Field Chooser"));

	ShowControlBar(&m_wndFieldChooser, FALSE, FALSE);
	FloatControlBar(&m_wndFieldChooser, CPoint(100, GetSystemMetrics(SM_CYSCREEN) / 3));

	// docking for filter editing
	m_wndFilterEdit.EnableDocking(CBRS_ALIGN_TOP);
	m_wndFilterEdit.SetWindowText(_T("Filter text"));

	ShowControlBar(&m_wndFilterEdit, FALSE, FALSE);
	FloatControlBar(&m_wndFilterEdit, CPoint(400, GetSystemMetrics(SM_CYSCREEN) / 3));

#if defined(_XTP_INCLUDE_DOCKINGPANE) && 0
	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeOffice2007Outlook);

	m_paneManager.SetFloatingFrameCaption(_T("Panes"));
	m_paneManager.SetStickyFloatingFrames(TRUE);
	m_paneManager.SetThemedFloatingFrames(TRUE);

	m_paneManager.SetSideDockingMargin(CRect(2, 2, 2, 2));
	m_paneManager.EnableSideDocking();

	m_paneManager.EnableKeyboardNavigate();

	CXTPDockingPane *pPaneFolders = m_paneManager.CreatePane(IDR_PANE_FOLDER, CRect(0, 0, 200, 150), xtpPaneDockLeft);
#endif

	return 0;
}


void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instantiate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

		// Add the options page to the customize dialog.
		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		// Add the commands page to the customize dialog.
		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_MAINFRAME);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
		pCommands->InsertNewMenuCategory();

		// Display the dialog.
		dlg.DoModal();
	}
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	BOOL bHandled = FALSE;
#if 0
	if (XTP_DPN_SHOWWINDOW == wParam)
	{
		bHandled = TRUE;

		CXTPDockingPane *pPane = reinterpret_cast<CXTPDockingPane*>(lParam);

		if (!pPane->IsValid())
		{
			if (NULL == m_pFolderView)
			{
				m_pFolderView = DYNAMIC_DOWNCAST(CFolderView,
					pPane->AttachView(this, RUNTIME_CLASS(CFolderView)));
			}
			else
			{
				pPane->Attach(m_pFolderView->GetParent());
			}
		}
	}
#endif
	return bHandled;
}


#if defined(_XTP_INCLUDE_SKINFRAMEWORK) && !defined(_XTP_EXCLUDE_SKINFRAMEWORK)

void CMainFrame::OnViewSkinNone() 
{
	SetSkin(skinNone);
}

void CMainFrame::OnViewSkinOffice2007() 
{
	SetSkin(skinOffice2007);
}

void CMainFrame::OnViewSkinOffice2010() 
{
	SetSkin(skinOffice2010);
}

void CMainFrame::OnViewSkinVista() 
{
	SetSkin(skinVista);
}

void CMainFrame::SetSkin(Skin skin)
{
	m_skin = skin;

	switch(skin)
	{
	case skinNone:
		VERIFY(XTPSkinManager()->LoadSkin(NULL, NULL));
		break;
	case skinOffice2007:
		VERIFY(XTPSkinManager()->LoadSkin(_T(".\\Styles\\Office2007.cjstyles")));
		break;
	case skinOffice2010:
		VERIFY(XTPSkinManager()->LoadSkin(_T(".\\Styles\\Office2010.cjstyles")));
		break;
	case skinVista:
		VERIFY(XTPSkinManager()->LoadSkin(_T(".\\Styles\\Vista.cjstyles")));
		break;
	}
}

#endif

void CMainFrame::OnUpdateViewSkinNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(skinNone == m_skin ? 1 : 0);
}

void CMainFrame::OnUpdateViewSkinOffice2007(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(skinOffice2007 == m_skin ? 1 : 0);
}

void CMainFrame::OnUpdateViewSkinOffice2010(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(skinOffice2010 == m_skin ? 1 : 0);
}

void CMainFrame::OnUpdateViewSkinVista(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(skinVista == m_skin ? 1 : 0);
}
