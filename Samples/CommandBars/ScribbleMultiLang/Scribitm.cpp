// ScribItm.cpp : implementation of the CScribbleItem class
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

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleItem implementation

IMPLEMENT_DYNAMIC(CScribbleItem, COleServerItem)

CScribbleItem::CScribbleItem(CScribbleDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// TODO: add one-time construction code here
	//  (eg, adding additional clipboard formats to the item's data source)
}

CScribbleItem::~CScribbleItem()
{
	// TODO: add cleanup code here
}

void CScribbleItem::Serialize(CArchive& ar)
{
	// CScribbleItem::Serialize will be called by the framework if
	//  the item is copied to the clipboard.  This can happen automatically
	//  through the OLE callback OnGetClipboardData.  A good default for
	//  the embedded item is simply to delegate to the document's Serialize
	//  function.  If you support links, then you will want to serialize
	//  just a portion of the document.

	if (!IsLinkedItem())
	{
		CScribbleDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->Serialize(ar);
	}
}

BOOL CScribbleItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// Most applications, like this one, only handle drawing the content
	//  aspect of the item.  If you wish to support other aspects, such
	//  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
	//  implementation of OnGetExtent should be modified to handle the
	//  additional aspect(s).

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CScribbleItem::OnGetExtent is called to get the extent in
	//  HIMETRIC units of the entire item.  The default implementation
	//  here simply returns a hard-coded number of units.

	CScribbleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	rSize = pDoc->GetDocSize();
	CClientDC dc(NULL);

		// use a mapping mode based on logical units
	//  (we can't use MM_LOENGLISH because MM_LOENGLISH uses physical inches)
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetViewportExt(dc.GetDeviceCaps(LOGPIXELSX), dc.GetDeviceCaps(LOGPIXELSY));
	dc.SetWindowExt(100, -100);
	dc.LPtoHIMETRIC(&rSize);

	return TRUE;
}

BOOL CScribbleItem::OnDraw(CDC* pDC, CSize& /* rSize */)
{
	CScribbleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->SetMapMode(MM_ANISOTROPIC);
	CSize sizeDoc = pDoc->GetDocSize();
	sizeDoc.cy = -sizeDoc.cy;
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(sizeDoc);

	CTypedPtrList<CObList,CStroke*>& strokeList = pDoc->m_strokeList;
	POSITION pos = strokeList.GetHeadPosition();
	while (pos != NULL)
	{
		strokeList.GetNext(pos)->DrawStroke(pDC);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleItem diagnostics

#ifdef _DEBUG
void CScribbleItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CScribbleItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
