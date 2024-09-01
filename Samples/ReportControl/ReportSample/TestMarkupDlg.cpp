// TestMarkupDlg.cpp : implementation of the CTestMarkupDlg class
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
#include "Resource.h"
#include "TestMarkupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestMarkupDlg dialog


CTestMarkupDlg::CTestMarkupDlg(CWnd *pParent)
	: CDialog(CTestMarkupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestMarkupDlg)
	//}}AFX_DATA_INIT
}


void CTestMarkupDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestMarkupDlg)
	DDX_Control(pDX, IDC_REPORT,  m_wndReport);
	DDX_Control(pDX, IDC_HITTEST, m_wndHitTest);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestMarkupDlg, CDialog)
	//{{AFX_MSG_MAP(CTestMarkupDlg)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMarkupDlg message handlers


BOOL CTestMarkupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	enum Constants
	{
		ColumnCount = 5,
		RecordCount = 3
	};

	// Initialize list control first
	m_wndHitTest.InsertColumn(0, _T("Event"),        LVCFMT_LEFT, 200);

	m_wndReport.EnableMarkup(TRUE);

#if defined(_XTP_INCLUDE_MARKUP)
	m_wndReport.GetMarkupContext()->AddHandler(CXTPMarkupHyperlink::m_pClickEvent, CreateMarkupClassDelegate(this, &CTestMarkupDlg::OnHyperlinkClick));
	m_wndReport.GetMarkupContext()->AddHandler(CXTPMarkupButton::m_pClickEvent, CreateMarkupClassDelegate(this, &CTestMarkupDlg::OnButtonClick));
#endif

	// Add columns
	m_wndReport.AddColumn(new CXTPReportColumn(0, _T("Hyperlink"), 100));
	m_wndReport.AddColumn(new CXTPReportColumn(1, _T("Button"),    100));

	CString sHyperlink = _T("<TextBlock><Hyperlink>Test link</Hyperlink></TextBlock>");
	CString sButton    = _T("<Button Margin='2' Cursor='Hand'><TextBlock HorizontalAlignment='Center'>System Button</TextBlock></Button>");

	// Add sample records
	for (int nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord;
		CXTPReportRecordItemText *pItem;

		// Body records
		pRecord = m_wndReport.GetRecords()->Add(new CXTPReportRecord());

		pItem = new CXTPReportRecordItemText();
		pRecord->AddItem(pItem);
		pItem->SetCaption(sHyperlink);

		pItem = new CXTPReportRecordItemText();
		pRecord->AddItem(pItem);
		pItem->SetCaption(sButton);
	}

	m_wndReport.GetPaintManager()->SetFixedRowHeight(FALSE);

	m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_wndReport.ShowGroupBy(FALSE);
	m_wndReport.ShowHeaderRows(TRUE);
	m_wndReport.ShowFooterRows(FALSE);
	m_wndReport.Populate();

	return FALSE;
}

void CTestMarkupDlg::OnOK()
{
	CDialog::OnOK();
}

int CTestMarkupDlg::AddEvent(LPCTSTR pszEvent)
{
	int nItem = m_wndHitTest.InsertItem(m_wndHitTest.GetItemCount(), pszEvent);

	m_wndHitTest.EnsureVisible(nItem, FALSE);

	return nItem;
}

#if defined(_XTP_INCLUDE_MARKUP)

void CTestMarkupDlg::OnHyperlinkClick(CXTPMarkupObject *pSender, CXTPMarkupRoutedEventArgs *pArgs)
{
	if (pSender->IsKindOf(MARKUP_TYPE(CXTPMarkupHyperlink)))
	{
		AddEvent(_T("OnHyperlinkClick"));
		pArgs->SetHandled();
	}
}

void CTestMarkupDlg::OnButtonClick(CXTPMarkupObject *pSender, CXTPMarkupRoutedEventArgs *pArgs)
{
	if (pSender->IsKindOf(MARKUP_TYPE(CXTPMarkupButton)))
	{
		AddEvent(_T("OnButtonClick"));
		pArgs->SetHandled();
	}
}

#endif
