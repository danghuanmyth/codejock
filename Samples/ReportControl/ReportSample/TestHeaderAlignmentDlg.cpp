// TestHeaderAlignmentDlg.cpp : implementation of the CTestHeaderAlignmentDlg class
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
#include "TestHeaderAlignmentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestHeaderAlignmentDlg dialog

CTestHeaderAlignmentDlg::CTestHeaderAlignmentDlg(CWnd *pParent)
	: CDialog(CTestHeaderAlignmentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestHeaderAlignmentDlg)
	m_bFixedRowHeight = FALSE;
	m_nHeaderHeight = 0;
	//}}AFX_DATA_INIT
}

void CTestHeaderAlignmentDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestHeaderAlignmentDlg)
	DDX_Check(pDX, IDC_FIXED_ROW_HEIGHT, m_bFixedRowHeight);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Text(pDX, IDC_HEADER_HEIGHT, m_nHeaderHeight);
	DDV_MinMaxInt(pDX, m_nHeaderHeight, 0, 99);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestHeaderAlignmentDlg, CDialog)
	//{{AFX_MSG_MAP(CTestHeaderAlignmentDlg)
	ON_BN_CLICKED(IDC_FIXED_ROW_HEIGHT, OnFixedRowHeight)
	ON_EN_UPDATE(IDC_HEADER_HEIGHT, OnUpdateHeaderHeight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestHeaderAlignmentDlg message handlers

BOOL CTestHeaderAlignmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	enum
	{
		RecordCount = 10,
	};

	struct Alignment 
	{
		int nAlignment;
		LPCTSTR lpszAlignment;
		int nWidth;
	};

	const Alignment alignment[] =
	{
		{DT_LEFT,                  _T("DT_LEFT"),   80},
		{DT_CENTER,                _T("DT_CENTER"), 80},
		{DT_RIGHT,                 _T("DT_RIGHT"),  80},
		{DT_LEFT   | DT_WORDBREAK, _T("DT_LEFT | DT_WORDBREAK"),   140},
		{DT_CENTER | DT_WORDBREAK, _T("DT_CENTER | DT_WORDBREAK"), 140},
		{DT_RIGHT  | DT_WORDBREAK, _T("DT_RIGHT | DT_WORDBREAK"),  140}
	};

	// Add columns
	for (int nColumn=0; nColumn<_countof(alignment); nColumn++)
	{
		CXTPReportColumn *pColumn = new CXTPReportColumn(nColumn,
			alignment[nColumn].lpszAlignment, alignment[nColumn].nWidth);
		m_wndReport.AddColumn(pColumn);

		pColumn->SetHeaderAlignment(alignment[nColumn].nAlignment);
	}

	// Add records
	for (int nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord = m_wndReport.AddRecord(new CXTPReportRecord());

		for (int nColumn=0; nColumn<_countof(alignment); nColumn++)
		{
			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(_T("Test"));
			pRecord->AddItem(pItem);
		}
	}

	// Populate
	m_wndReport.Populate();

	// Initialize
	m_bFixedRowHeight = m_wndReport.GetPaintManager()->IsFixedRowHeight();
	m_nHeaderHeight = m_wndReport.GetPaintManager()->GetHeaderHeight();
	UpdateData(FALSE);

	return FALSE;
}

void CTestHeaderAlignmentDlg::OnOK()
{
	CDialog::OnOK();
}

void CTestHeaderAlignmentDlg::OnFixedRowHeight()
{
	UpdateData();
	m_wndReport.GetPaintManager()->SetFixedRowHeight(m_bFixedRowHeight);
	m_wndReport.AdjustLayout();
	m_wndReport.RedrawControl();
}

void CTestHeaderAlignmentDlg::OnUpdateHeaderHeight() 
{
	UpdateData();
}
