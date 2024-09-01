// PageOverlayIcons.cpp : implementation file
//

#include "stdafx.h"
#include "TaskbarManager.h"
#include "PageOverlayIcons.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageOverlayIcons property page

IMPLEMENT_DYNCREATE(CPageOverlayIcons, CPropertyPage)

CPageOverlayIcons::CPageOverlayIcons() : CPropertyPage(CPageOverlayIcons::IDD)
{
	//{{AFX_DATA_INIT(CPageOverlayIcons)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageOverlayIcons::~CPageOverlayIcons()
{
}

void CPageOverlayIcons::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageOverlayIcons)
	DDX_Control(pDX, IDC_BUTTON_QUESTION, m_btnQuestion);
	DDX_Control(pDX, IDC_BUTTON_NOVOLUME, m_btnNoVolume);
	DDX_Control(pDX, IDC_BUTTON_NOICON, m_tnNoIcon);
	DDX_Control(pDX, IDC_BUTTON_INFO, m_btnInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageOverlayIcons, CPropertyPage)
	//{{AFX_MSG_MAP(CPageOverlayIcons)
	ON_BN_CLICKED(IDC_BUTTON_INFO, OnButtonInfo)
	ON_BN_CLICKED(IDC_BUTTON_QUESTION, OnButtonQuestion)
	ON_BN_CLICKED(IDC_BUTTON_NOVOLUME, OnButtonNoVolume)
	ON_BN_CLICKED(IDC_BUTTON_NOICON, OnButtonNoIcon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageOverlayIcons message handlers

BOOL CPageOverlayIcons::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_btnInfo.SetIcon(CSize(48, 48), MAKEINTRESOURCE(IDC_BUTTON_INFO));
	m_btnNoVolume.SetIcon(CSize(48, 48), MAKEINTRESOURCE(IDC_BUTTON_NOVOLUME));
	m_btnQuestion.SetIcon(CSize(48, 48), MAKEINTRESOURCE(IDC_BUTTON_QUESTION));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageOverlayIcons::OnButtonInfo() 
{
	m_mgrTaskBar.SetOverlayIcon(AfxGetMainWnd()->GetSafeHwnd(), IDC_BUTTON_INFO, _T("Info"));
	
}

void CPageOverlayIcons::OnButtonQuestion() 
{
	m_mgrTaskBar.SetOverlayIcon(AfxGetMainWnd()->GetSafeHwnd(), IDC_BUTTON_QUESTION, _T("Question"));
}

void CPageOverlayIcons::OnButtonNoVolume() 
{
	m_mgrTaskBar.SetOverlayIcon(AfxGetMainWnd()->GetSafeHwnd(), IDC_BUTTON_NOVOLUME, _T("No Volume"));
	
}

void CPageOverlayIcons::OnButtonNoIcon() 
{
	m_mgrTaskBar.SetOverlayIcon(AfxGetMainWnd()->GetSafeHwnd(), (HICON)NULL, _T(""));
	
}
