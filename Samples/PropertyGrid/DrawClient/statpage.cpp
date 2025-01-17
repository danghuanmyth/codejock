// statpage.cpp : implementation file
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
#include "drawcli.h"
#include "statpage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatPage property page

IMPLEMENT_DYNCREATE(CStatPage, CPropertyPage)

CStatPage::CStatPage() : CPropertyPage(CStatPage::IDD)
{
		//{{AFX_DATA_INIT(CStatPage)
	m_strCreateDate = _T("");
	m_strEditTime = _T("");
	m_strLastPrint = _T("");
	m_strLastSave = _T("");
	m_strNumChars = _T("");
	m_strNumPages = _T("");
	m_strNumWords = _T("");
	m_strRevNum = _T("");
	m_strSavedBy = _T("");
	m_strSecurity = _T("");
	//}}AFX_DATA_INIT
}

CStatPage::~CStatPage()
{
}

void CStatPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CStatPage)
	DDX_Text(pDX, IDC_CREATEDATE, m_strCreateDate);
	DDX_Text(pDX, IDC_EDITTIME, m_strEditTime);
	DDX_Text(pDX, IDC_LASTPRINT, m_strLastPrint);
	DDX_Text(pDX, IDC_LASTSAVE, m_strLastSave);
	DDX_Text(pDX, IDC_NUMCHARS, m_strNumChars);
	DDX_Text(pDX, IDC_NUMPAGES, m_strNumPages);
	DDX_Text(pDX, IDC_NUMWORDS, m_strNumWords);
	DDX_Text(pDX, IDC_REVNUM, m_strRevNum);
	DDX_Text(pDX, IDC_SAVEDBY, m_strSavedBy);
	DDX_Text(pDX, IDC_SECURITY, m_strSecurity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatPage, CPropertyPage)
		//{{AFX_MSG_MAP(CStatPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatPage message handlers
