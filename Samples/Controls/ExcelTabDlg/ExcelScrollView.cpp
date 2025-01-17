// ExcelScrollView.cpp : implementation file
//
// This file is a part of the XTREME CONTROLS MFC class library.
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
#include "ExcelTab.h"
#include "ExcelScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExcelScrollView

IMPLEMENT_DYNCREATE(CExcelScrollView, CScrollView)

BEGIN_MESSAGE_MAP(CExcelScrollView, CScrollView)
	//{{AFX_MSG_MAP(CExcelScrollView)
	ON_WM_HSCROLL()
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelScrollView construction/destruction

CExcelScrollView::CExcelScrollView()
{
	// TODO: add construction code here

}

CExcelScrollView::~CExcelScrollView()
{
}

BOOL CExcelScrollView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExcelScrollView drawing

void CExcelScrollView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here
	CRect rc;
	CString strTemp;

	GetClientRect( &rc );

	int nPosX = GetScrollPos(SB_HORZ);
	int nPosY = GetScrollPos(SB_VERT);

	pDC->SetBkMode( TRANSPARENT );

	strTemp.Format( _T("nPosX: %d  nPosY: %d"), nPosX , nPosY   );

	pDC->TextOut( nPosX+ (rc.Width()/3) , nPosY + (rc.Height() /2 )  , strTemp);
}

#ifndef MM_NONE
#define MM_NONE 0
#endif//MM_NONE

void CExcelScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizes( MM_TEXT, CSize( 16400, 16400 ));
	ResizeParentToFit( );
	SyncScrollBar();
}

/////////////////////////////////////////////////////////////////////////////
// CExcelScrollView printing

BOOL CExcelScrollView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExcelScrollView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExcelScrollView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExcelScrollView diagnostics

#ifdef _DEBUG
void CExcelScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CExcelScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
/*
CTestScrollDoc* CExcelScrollView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestScrollDoc)));
	return (CTestScrollDoc*)m_pDocument;
}*/
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExcelScrollView message handlers

BOOL CExcelScrollView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll)
{
	/////////////////////////////////
	// 32K H/V Scroll Limit Bug Fix
	CXTPExcelTabCtrl *pParent = (CXTPExcelTabCtrl *)GetParent();
	if( pParent && ::IsWindow( pParent->m_hWnd ) )
	{
		if( pParent->IsKindOf( RUNTIME_CLASS( CXTPExcelTabCtrl ) ) )
		{
			ASSERT_KINDOF(CXTPExcelTabCtrl, pParent);

			SCROLLINFO siFlat;
			ZeroMemory(&siFlat, sizeof(siFlat));
			siFlat.cbSize = sizeof(siFlat);
			siFlat.fMask = SIF_TRACKPOS;

			if (LOBYTE(nScrollCode) == SB_THUMBTRACK)
			{
				GetScrollInfo(SB_HORZ, &siFlat);
				nPos = siFlat.nTrackPos;
			}
			if (HIBYTE(nScrollCode) == SB_THUMBTRACK)
			{
				GetScrollInfo(SB_VERT, &siFlat);
				nPos = siFlat.nTrackPos;
			}
		}
	}

	Invalidate( TRUE );

	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}

void CExcelScrollView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	TRACE1("CExcelScrollView::OnHScroll( %d ) \n",nPos);
	if (m_ScrollBarH.m_hWnd   &&
		pScrollBar->GetSafeHwnd() == m_ScrollBarH.m_hWnd )
	{
		SCROLLINFO si;
		ZeroMemory(&si, sizeof(si));
		si.cbSize = sizeof(si);
		si.fMask = SIF_PAGE;
		m_ScrollBarH.GetScrollInfo(&si);

		int x = m_ScrollBarH.GetScrollPos();
		switch (nSBCode)
		{
			case SB_TOP:
				x = 0;
				break;
			case SB_BOTTOM:
				x = INT_MAX;
				break;
			case SB_LINEUP:
				x--;
				break;
			case SB_LINEDOWN:
				x++;
				break;
			case SB_PAGEUP:
				x -= si.nPage;
				break;
			case SB_PAGEDOWN:
				x += si.nPage;
				break;
			case SB_THUMBTRACK:
				x = nPos;
				break;
		}
		si.nPos = x;
		si.fMask = SIF_POS;
		m_ScrollBarH.SetScrollInfo(&si);
		TRACE1("OnHScroll( #1 si.nPos : %x\n", si.nPos);
	}

	TRACE1("OnHScroll( #2 nPos : %x\n", nPos);
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}



CScrollBar* CExcelScrollView::GetScrollBarCtrl(int nBar)const
{
	TRACE1("CExcelScrollView::GetScrollBarCtrl( %d )\n", nBar);

	if (nBar == SB_HORZ)  {
		return (CScrollBar *)&m_ScrollBarH;
	}
	return CScrollView::GetScrollBarCtrl(nBar);
}

int CExcelScrollView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ScrollBarH.Create(WS_CHILD, CRect(0, 0, 0, 0), this, 0);

	return 0;
}

BOOL CExcelScrollView::SyncScrollBar()
{
	CXTPExcelTabCtrl *pParent = DYNAMIC_DOWNCAST(CXTPExcelTabCtrl, GetParent());
	if ( ::IsWindow( pParent->GetSafeHwnd( )))
	{
		pParent->SyncScrollBar( );
		return TRUE;
	}
	return FALSE;
}

void CExcelScrollView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	SyncScrollBar();
}

BOOL CExcelScrollView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
	int xOrig, x;
	int yOrig, y;

	// don't scroll if there is no valid scroll range (ie. no scroll bar)
	CScrollBar* pBar;
	DWORD dwStyle = GetStyle();
	pBar = GetScrollBarCtrl(SB_VERT);
	if ((pBar != NULL && !pBar->IsWindowEnabled()) ||
		(pBar == NULL && !(dwStyle & WS_VSCROLL)))
	{
		// vertical scroll bar not enabled
		sizeScroll.cy = 0;
	}
	pBar = GetScrollBarCtrl(SB_HORZ);
	if ((pBar != NULL && !pBar->IsWindowEnabled()) ||
		(pBar == NULL && !(dwStyle & WS_HSCROLL)))
	{
		// horizontal scroll bar not enabled
		sizeScroll.cx = 0;
	}

	// adjust current x position
	xOrig = x = GetScrollPos(SB_HORZ);
	int xMax = GetScrollLimit(SB_HORZ);
	x += sizeScroll.cx;
	if (x < 0)
		x = 0;
	else if (x > xMax)
		x = xMax;

	// adjust current y position
	yOrig = y = GetScrollPos(SB_VERT);
	int yMax = GetScrollLimit(SB_VERT);
	y += sizeScroll.cy;
	if (y < 0)
		y = 0;
	else if (y > yMax)
		y = yMax;

	// did anything change?
	if (x == xOrig && y == yOrig)
		return FALSE;

	if (bDoScroll)
	{
		// do scroll and update scroll positions
		ScrollWindow(-(x-xOrig), -(y-yOrig));
		if (x != xOrig)
			SetScrollPos(SB_HORZ, x);
		if (y != yOrig)
			SetScrollPos(SB_VERT, y);
	}
	return TRUE;
}

void CExcelScrollView::OnPaint() 
{
	if (m_nMapMode == MM_NONE)
	{
		SetScrollSizes( MM_TEXT, CSize( 16400, 16400 ));
		ResizeParentToFit( );
		SyncScrollBar();
	}

	// standard paint routine
	CPaintDC dc(this);
	OnPrepareDC(&dc);
	OnDraw(&dc);
}

void CExcelScrollView::ResizeParentToFit(BOOL bShrinkOnly/* = TRUE*/)
{
	// adjust parent rect so client rect is appropriate size
	ASSERT(m_nMapMode != MM_NONE);  // mapping mode must be known

	// determine current size of the client area as if no scrollbars present
	CRect rectClient;
	GetWindowRect(rectClient);
	CRect rect = rectClient;
	CalcWindowRect(rect);
	rectClient.left += rectClient.left - rect.left;
	rectClient.top += rectClient.top - rect.top;
	rectClient.right -= rect.right - rectClient.right;
	rectClient.bottom -= rect.bottom - rectClient.bottom;
	rectClient.OffsetRect(-rectClient.left, -rectClient.top);
	ASSERT(rectClient.left == 0 && rectClient.top == 0);

	// determine desired size of the view
	CRect rectView(0, 0, m_totalDev.cx, m_totalDev.cy);
	if (bShrinkOnly)
	{
		if (rectClient.right <= m_totalDev.cx)
			rectView.right = rectClient.right;
		if (rectClient.bottom <= m_totalDev.cy)
			rectView.bottom = rectClient.bottom;
	}
	CalcWindowRect(rectView, CWnd::adjustOutside);
	rectView.OffsetRect(-rectView.left, -rectView.top);
	ASSERT(rectView.left == 0 && rectView.top == 0);
	if (bShrinkOnly)
	{
		if (rectClient.right <= m_totalDev.cx)
			rectView.right = rectClient.right;
		if (rectClient.bottom <= m_totalDev.cy)
			rectView.bottom = rectClient.bottom;
	}

	// determine and set size of frame based on desired size of view
	CRect rectFrame;
	CWnd* pParentWnd = AfxGetMainWnd();
	if (::IsWindow(pParentWnd->GetSafeHwnd()))
	{
		CXTPWindowRect rWindow(pParentWnd);
		pParentWnd->SetRedraw(FALSE);
		pParentWnd->SetWindowPos(NULL, 0, 0, rWindow.Width()+1, rWindow.Height(),
			SWP_NOMOVE|SWP_FRAMECHANGED);
		pParentWnd->SetRedraw(TRUE);
		pParentWnd->SetWindowPos(NULL, 0, 0, rWindow.Width()-1, rWindow.Height(),
			SWP_NOMOVE|SWP_FRAMECHANGED);
	}
}