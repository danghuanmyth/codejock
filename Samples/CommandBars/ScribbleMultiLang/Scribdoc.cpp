// ScribDoc.cpp : implementation of the CScribbleDoc class
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
#include "ScribItm.h"
#include "PenDlg.h"
#include "ScribVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CScribbleDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CScribbleDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(ID_PEN_THICK_OR_THIN, OnPenThickOrThin)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_PEN_THICK_OR_THIN, OnUpdatePenThickOrThin)
	ON_COMMAND(ID_PEN_WIDTHS, OnPenWidths)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc construction/destruction

CScribbleDoc::CScribbleDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	m_sizeDoc = CSize(200, 200);
}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;
	InitDocument();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc serialization

void CScribbleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_sizeDoc;
	}
	else
	{
		ar >> m_sizeDoc;
	}
	m_strokeList.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc diagnostics

#ifdef _DEBUG
void CScribbleDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CScribbleDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc commands

BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!COleServerDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	InitDocument();
	return TRUE;
}

void CScribbleDoc::DeleteContents()
{
	while (!m_strokeList.IsEmpty())
	{
		delete m_strokeList.RemoveHead();
	}
	COleServerDoc::DeleteContents();
}

void CScribbleDoc::InitDocument()
{
	m_bThickPen = FALSE;
	m_nThinWidth = 2;   // default thin pen is 2 pixels wide
	m_nThickWidth = 5;  // default thick pen is 5 pixels wide
	ReplacePen();       // initialize pen according to current width

	// default document size is 2 x 2 inches
	m_sizeDoc = CSize(200,200);
}

CStroke* CScribbleDoc::NewStroke()
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_strokeList.AddTail(pStrokeItem);
	SetModifiedFlag();  // Mark the document as having been modified, for
	                    // purposes of confirming File Close.
	return pStrokeItem;
}




/////////////////////////////////////////////////////////////////////////////
// CStroke

IMPLEMENT_SERIAL(CStroke, CObject, 2)
CStroke::CStroke()
{
	// This empty constructor should be used by serialization only
}

CStroke::CStroke(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
	m_rectBounding.SetRectEmpty();
}

void CStroke::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_rectBounding;
		ar << (WORD)m_nPenWidth;
		m_pointArray.Serialize(ar);
	}
	else
	{
		ar >> m_rectBounding;
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		m_pointArray.Serialize(ar);
	}
}

BOOL CStroke::DrawStroke(CDC* pDC)
{
	CPen penStroke;
	if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject(&penStroke);
	pDC->MoveTo(m_pointArray[0]);
	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		pDC->LineTo(m_pointArray[i]);
	}

	pDC->SelectObject(pOldPen);
	return TRUE;
}
void CScribbleDoc::OnEditClearAll()
{
	DeleteContents();
	SetModifiedFlag();  // Mark the document as having been modified, for
	                    // purposes of confirming File Close.
	UpdateAllViews(NULL);
}

void CScribbleDoc::OnPenThickOrThin()
{
	// Toggle the state of the pen between thin or thick.
	m_bThickPen = !m_bThickPen;

	// Change the current pen to reflect the new user-specified width.
	ReplacePen();
}

void CScribbleDoc::ReplacePen()
{
	m_nPenWidth = m_bThickPen? m_nThickWidth : m_nThinWidth;

	// Change the current pen to reflect the new user-specified width.
	m_penCur.DeleteObject();
	m_penCur.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)); // solid black
}

void CScribbleDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI)
{
	// Enable the command user interface object (menu item or tool bar
	// button) if the document is non-empty, i.e., has at least one stroke.
	pCmdUI->Enable(!m_strokeList.IsEmpty());
}

void CScribbleDoc::OnUpdatePenThickOrThin(CCmdUI* pCmdUI)
{
	// Add check mark to Draw Thick Line menu item, if the current
	// pen width is "thick".
	pCmdUI->SetCheck(m_bThickPen);
}

void CScribbleDoc::OnPenWidths()
{
	CPenWidthsDlg dlg;

	// Initialize dialog data
	dlg.m_nThinWidth = m_nThinWidth;
	dlg.m_nThickWidth = m_nThickWidth;

	// Invoke the dialog box
	if (dlg.DoModal() == IDOK)
	{
		// retrieve the dialog data
		m_nThinWidth = dlg.m_nThinWidth;
		m_nThickWidth = dlg.m_nThickWidth;

		// Update the pen that is used by views when drawing new strokes,
		// to reflect the new pen width definitions for "thick" and "thin".
		ReplacePen();
	}
}

void CStroke::FinishStroke()
{
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.

	if (m_pointArray.GetSize()==0)
	{
		m_rectBounding.SetRectEmpty();
		return;
	}
	CPoint pt = m_pointArray[0];
	m_rectBounding = CRect(pt.x, pt.y, pt.x, pt.y);

	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		pt = m_pointArray[i];
		m_rectBounding.left     = min(m_rectBounding.left, pt.x);
		m_rectBounding.right    = max(m_rectBounding.right, pt.x);
		m_rectBounding.top      = max(m_rectBounding.top, pt.y);
		m_rectBounding.bottom   = min(m_rectBounding.bottom, pt.y);
	}

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the stroke when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));
	return;
}

COleServerItem* CScribbleDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CScribbleItem* pItem = new CScribbleItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

void CScribbleDoc::OnSetItemRects(LPCRECT lpPosRect, LPCRECT lpClipRect)
{
	// call base class to change the size of the window
	COleServerDoc::OnSetItemRects(lpPosRect, lpClipRect);

	// notify first view that scroll info should change
	POSITION pos = GetFirstViewPosition();
	CScribbleView* pView = (CScribbleView*)GetNextView(pos);
	pView->ResyncScrollSizes();
}

void CScribbleDoc::OnEditCopy()
{
	CScribbleItem* pItem = GetEmbeddedItem();
	pItem->CopyToClipboard(TRUE);
}
