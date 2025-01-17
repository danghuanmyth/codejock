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

#include "stdafx.h"
#include "MDIPanes.h"

#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_THEME_DEFAULT, OnThemeDefault)
	ON_UPDATE_COMMAND_UI(ID_THEME_DEFAULT, OnUpdateThemeDefault)
	ON_COMMAND(ID_THEME_OFFICEXP, OnThemeOfficexp)
	ON_UPDATE_COMMAND_UI(ID_THEME_OFFICEXP, OnUpdateThemeOfficexp)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
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
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	XTPPaintManager()->SetTheme(xtpThemeOfficeXP);

	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MDIPANTYPE);

	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	// Load the previous state for command bars.
	LoadCommandBars(_T("CommandBars"));


	//CXTPDockingPanePaintManager::SetTheme(xtpPaneThemeVisualStudio2003);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::RedrawAll()
{

	RecalcLayout(FALSE);
	GetCommandBars()->RedrawCommandBars();
	RedrawWindow();

	CWnd* pWndClient = CWnd::FromHandle(m_hWndMDIClient);

	CChildFrame* pWndChild = (CChildFrame*)pWndClient->GetWindow(GW_CHILD);
	while (pWndChild)
	{

		pWndChild->RecalcLayout(FALSE);
		pWndChild->GetCommandBars()->RedrawCommandBars();
		pWndChild->RedrawWindow();
		pWndChild->m_paneManager.SetTheme(CChildFrame::m_themeCurrent);


		pWndChild = (CChildFrame*)pWndChild->GetWindow(GW_HWNDNEXT);
	}





}

void CMainFrame::OnThemeDefault()
{
	CXTPPaintManager::SetTheme(xtpThemeOffice2000);

	CChildFrame::m_themeCurrent = xtpPaneThemeDefault;
	RedrawAll();

}

void CMainFrame::OnUpdateThemeDefault(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(CChildFrame::m_themeCurrent == xtpPaneThemeDefault);

}

void CMainFrame::OnThemeOfficexp()
{
	CXTPPaintManager::SetTheme(xtpThemeOfficeXP);

	CChildFrame::m_themeCurrent = xtpPaneThemeVisualStudio2003;
	RedrawAll();

}

void CMainFrame::OnUpdateThemeOfficexp(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(CChildFrame::m_themeCurrent == xtpPaneThemeVisualStudio2003);
}


void CMainFrame::OnClose()
{
	// Save the current state for command bars.
	SaveCommandBars(_T("CommandBars"));
	// TODO: Add your message handler code here and/or call default

	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnCustomize()
{
	// get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return;

	// instanciate the customize dialog
	CXTPCustomizeSheet dlg(pCommandBars);

	// add the options page to the customize dialog.
	CXTPCustomizeOptionsPage pageOptions(&dlg);
	dlg.AddPage(&pageOptions);

	// add the commands page to the customize dialog.
	CXTPCustomizeCommandsPage* pPageCommands = dlg.GetCommandsPage();
	pPageCommands->AddCategories(IDR_MDIPANTYPE);

	// initialize the commands page page.
	pPageCommands->InsertAllCommandsCategory();
	pPageCommands->InsertBuiltInMenus(IDR_MDIPANTYPE);
	pPageCommands->InsertNewMenuCategory();

	// display the customize dialog.
	dlg.DoModal();
}

