// ScribVw.cpp : implementation of the CScribbleView class
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
#include "Scribble.h"

#include "ScribDoc.h"
#include "ScribVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleView

IMPLEMENT_DYNCREATE(CScribbleView, CScrollView)

BEGIN_MESSAGE_MAP(CScribbleView, CScrollView)
	//{{AFX_MSG_MAP(CScribbleView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribbleView construction/destruction

CScribbleView::CScribbleView()
{
	SetScrollSizes(MM_TEXT, CSize(0, 0));
}

CScribbleView::~CScribbleView()
{
}

BOOL CScribbleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView drawing

void CScribbleView::OnDraw(CDC* pDC)
{
	CScribbleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CTypedPtrList<CObList,CStroke*>& strokeList = pDoc->m_strokeList;
	POSITION pos = strokeList.GetHeadPosition();
	while (pos != NULL)
	{
		CStroke* pStroke = strokeList.GetNext(pos);
		pStroke->DrawStroke(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView printing

BOOL CScribbleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(2);   // the document is two pages long:
	                        // the first page is the title page
	                        // the second is the drawing
	BOOL bRet = DoPreparePrinting(pInfo);   // default preparation
	pInfo->m_nNumPreviewPages = 2;  // Preview 2 pages at a time
	// Set this value after calling DoPreparePrinting to override
	// value read from .INI file
	return bRet;
}

void CScribbleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CScribbleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView diagnostics

#ifdef _DEBUG
void CScribbleView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CScribbleView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CScribbleDoc* CScribbleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScribbleDoc)));
	return (CScribbleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribbleView message handlers

void CScribbleView::OnLButtonDown(UINT, CPoint point)
{
	// Pressing the mouse button in the view window starts a new stroke

	// CScrollView changes the viewport origin and mapping mode.
	// It's necessary to convert the point from device coordinates
	// to logical coordinates, such as are stored in the document.
	CClientDC dc(this);
	OnPrepareDC(&dc);
	DPtoLP(dc, &point);

	m_pStrokeCur = GetDocument()->NewStroke();
	// Add first point to the new stroke
	m_pStrokeCur->m_pointArray.Add(point);

	SetCapture();       // Capture the mouse until button up.
	m_ptPrev = point;   // Serves as the MoveTo() anchor point for the
	                    // LineTo() the next point, as the user drags the
	                    // mouse.

	return;
}

void CScribbleView::Line(CDC& dc, CPoint pt1, CPoint pt2)
{
	dc.MoveTo(pt1);
	dc.LineTo(pt2);
}
void CScribbleView::DPtoLP(CDC& dc, CPoint* lpPoint)
{
	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		lpPoint->x = CXTPClientRect(this).Width() - lpPoint->x;
	}

	dc.DPtoLP(lpPoint);
}

void CScribbleView::OnLButtonUp(UINT, CPoint point)
{
	// Mouse button up is interesting in the Scribble application
	// only if the user is currently drawing a new stroke by dragging
	// the captured mouse.

	if (GetCapture() != this)
		return; // If this window (view) didn't capture the mouse,
		        // then the user isn't drawing in this window.

	CScribbleDoc* pDoc = GetDocument();

	CClientDC dc(this);

	// CScrollView changes the viewport origin and mapping mode.
	// It's necessary to convert the point from device coordinates
	// to logical coordinates, such as are stored in the document.
	OnPrepareDC(&dc);  // set up mapping mode and viewport origin
	DPtoLP(dc, &point);

	CPen* pOldPen = dc.SelectObject(pDoc->GetCurrentPen());
	Line(dc, m_ptPrev, point);
	dc.SelectObject(pOldPen);
	m_pStrokeCur->m_pointArray.Add(point);

	// Tell the stroke item that we're done adding points to it.
	// This is so it can finish computing its bounding rectangle.
	m_pStrokeCur->FinishStroke();

	// Tell the other views that this stroke has been added
	// so that they can invalidate this stroke's area in their
	// client area.
	pDoc->UpdateAllViews(this, 0L, m_pStrokeCur);

	ReleaseCapture();   // Release the mouse capture established at
	                    // the beginning of the mouse drag.
	pDoc->NotifyChanged();
	return;
}

void CScribbleView::OnMouseMove(UINT, CPoint point)
{
	// Mouse movement is interesting in the Scribble application
	// only if the user is currently drawing a new stroke by dragging
	// the captured mouse.

	if (GetCapture() != this)
		return; // If this window (view) didn't capture the mouse,
		        // then the user isn't drawing in this window.


	CClientDC dc(this);
	// CScrollView changes the viewport origin and mapping mode.
	// It's necessary to convert the point from device coordinates
	// to logical coordinates, such as are stored in the document.
	OnPrepareDC(&dc);
	DPtoLP(dc, &point);

	m_pStrokeCur->m_pointArray.Add(point);

	// Draw a line from the previous detected point in the mouse
	// drag to the current point.
	CPen* pOldPen = dc.SelectObject(GetDocument()->GetCurrentPen());
	Line(dc, m_ptPrev, point);
	dc.SelectObject(pOldPen);
	m_ptPrev = point;
	return;
}

void CScribbleView::OnUpdate(CView* /* pSender */, LPARAM /* lHint */,
	CObject* pHint)
{
	// The document has informed this view that some data has changed.

	if (pHint != NULL)
	{
		if (pHint->IsKindOf(RUNTIME_CLASS(CStroke)))
		{
			// The hint is that a stroke as been added (or changed).
			// So, invalidate its rectangle.
			CStroke* pStroke = (CStroke*)pHint;
			CClientDC dc(this);
			OnPrepareDC(&dc);
			CRect rectInvalid = pStroke->GetBoundingRect();
			dc.LPtoDP(&rectInvalid);
			InvalidateRect(&rectInvalid);
			return;
		}
	}
	// We can't interpret the hint, so assume that anything might
	// have been updated.
	Invalidate(TRUE);
	return;
}

void CScribbleView::OnInitialUpdate()
{
		ResyncScrollSizes();
	CScrollView::OnInitialUpdate();
}

void CScribbleView::ResyncScrollSizes()
{
	CClientDC dc(NULL);
	OnPrepareDC(&dc);
	CSize sizeDoc = GetDocument()->GetDocSize();
	dc.LPtoDP(&sizeDoc);
	SetScrollSizes(MM_TEXT, sizeDoc);
}

void CScribbleView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if (pInfo->m_nCurPage == 1)  // page no. 1 is the title page
	{
		PrintTitlePage(pDC, pInfo);
		return; // nothing else to print on page 1 but the page title
	}
	CString strHeader = GetDocument()->GetTitle();

	PrintPageHeader(pDC, pInfo, strHeader);
	// PrintPageHeader() subtracts out from the pInfo->m_rectDraw the
	// amount of the page used for the header.

	pDC->SetWindowOrg(pInfo->m_rectDraw.left,-pInfo->m_rectDraw.top);

	// Now print the rest of the page
	OnDraw(pDC);
}

void CScribbleView::PrintTitlePage(CDC* pDC, CPrintInfo* pInfo)
{
	// Prepare a font size for displaying the file name
	LOGFONT logFont;
	memset(&logFont, 0, sizeof(LOGFONT));
	logFont.lfHeight = 75;  //  3/4th inch high in MM_LOENGLISH
	                        // (1/100th inch)
	CFont font;
	CFont* pOldFont = NULL;
	if (font.CreateFontIndirect(&logFont))
		pOldFont = pDC->SelectObject(&font);

	// Get the file name, to be displayed on title page
	CString strPageTitle = GetDocument()->GetTitle();

	// Display the file name 1 inch below top of the page,
	// centered horizontally
	pDC->SetTextAlign(TA_CENTER);
	pDC->TextOut(pInfo->m_rectDraw.right/2, -100, strPageTitle);

	if (pOldFont != NULL)
		pDC->SelectObject(pOldFont);
}

void CScribbleView::PrintPageHeader(CDC* pDC, CPrintInfo* pInfo,
	CString& strHeader)
{
	// Print a page header consisting of the name of
	// the document and a horizontal line
	pDC->SetTextAlign(TA_LEFT);
	pDC->TextOut(0,-25, strHeader);  // 1/4 inch down

	// Draw a line across the page, below the header
	TEXTMETRIC textMetric;
	pDC->GetTextMetrics(&textMetric);
	int y = -35 - textMetric.tmHeight;          // line 1/10th inch below text
	pDC->MoveTo(0, y);                          // from left margin
	pDC->LineTo(pInfo->m_rectDraw.right, y);    // to right margin

	// Subtract out from the drawing rectange the space used by the header.
	y -= 25;    // space 1/4 inch below (top of) line
	pInfo->m_rectDraw.top += y;
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CScribbleView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

void CScribbleView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CScribbleDoc* pDoc = GetDocument();
	CScrollView::OnPrepareDC(pDC, pInfo);

	pDC->SetMapMode(MM_ANISOTROPIC);
	CSize sizeDoc = pDoc->GetDocSize();
	sizeDoc.cy = -sizeDoc.cy;
	pDC->SetWindowExt(sizeDoc);

	CSize sizeNum, sizeDenom;
	pDoc->GetZoomFactor(&sizeNum, &sizeDenom);

	int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);

	long xExt = (long)sizeDoc.cx * xLogPixPerInch * sizeNum.cx;
	xExt /= 100 * (long)sizeDenom.cx;
	long yExt = (long)sizeDoc.cy * yLogPixPerInch * sizeNum.cy;
	yExt /= 100 * (long)sizeDenom.cy;
	pDC->SetViewportExt((int)xExt, (int)-yExt);
}

void CScribbleView::OnSize(UINT nType, int cx, int cy)
{
		ResyncScrollSizes();        // ensure that scroll info is up-to-date
	CScrollView::OnSize(nType, cx, cy);
}

void CScribbleView::OnFilePrintPreview() 
{
	// replace the default print preview with ours!

	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.
	
	// must not create this on the frame.  Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;
	
	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.
	
	if (!DoPrintPreview(XTP_IDD_PREVIEW_DIALOGBAR, this, RUNTIME_CLASS(CXTPPreviewView), pState))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		
		TRACE0("Error: DoPrintPreview failed.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;      // preview failed to initialize, delete State now
		pState = NULL;
	}
}

