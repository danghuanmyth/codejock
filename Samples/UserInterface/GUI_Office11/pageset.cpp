// pageset.cpp : implementation file
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
#include "wordpad.h"
#include "resource.h"
#include "pageset.h"
#include "ruler.h"
#include "ddxm.h"
#include "helpids.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSetupDlg dialog

const DWORD CPageSetupDlg::m_nHelpIDs[] =
{
	IDC_EDIT_TM, IDH_WORDPAD_TOPMARGIN,
	IDC_EDIT_BM, IDH_WORDPAD_BOTTOMMARGIN,
	IDC_EDIT_LM, IDH_WORDPAD_LEFTMARGIN,
	IDC_EDIT_RM, IDH_WORDPAD_RIGHTMARGIN,
	IDC_BOX, IDH_COMM_GROUPBOX,
	0, 0
};

CPageSetupDlg::CPageSetupDlg(CWnd* pParent /*=NULL*/)
	: CCSDialog(CPageSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageSetupDlg)
	m_nTopMargin = 0;
	m_nRightMargin = 0;
	m_nLeftMargin = 0;
	m_nBottomMargin = 0;
	//}}AFX_DATA_INIT
}

void CPageSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSetupDlg)
	DDX_Twips(pDX, IDC_EDIT_TM, m_nTopMargin);
	DDV_MinMaxTwips(pDX, m_nTopMargin, -31680, 31680);
	DDX_Twips(pDX, IDC_EDIT_RM, m_nRightMargin);
	DDV_MinMaxTwips(pDX, m_nRightMargin, -31680, 31680);
	DDX_Twips(pDX, IDC_EDIT_LM, m_nLeftMargin);
	DDV_MinMaxTwips(pDX, m_nLeftMargin, -31680, 31680);
	DDX_Twips(pDX, IDC_EDIT_BM, m_nBottomMargin);
	DDV_MinMaxTwips(pDX, m_nBottomMargin, -31680, 31680);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageSetupDlg, CCSDialog)
	//{{AFX_MSG_MAP(CPageSetupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSetupDlg message handlers
