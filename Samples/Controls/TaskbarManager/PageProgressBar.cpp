// PageProgressBar.cpp : implementation file
//

#include "stdafx.h"
#include "TaskbarManager.h"
#include "PageProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar property page

IMPLEMENT_DYNCREATE(CPageProgressBar, CPropertyPage)

CPageProgressBar::CPageProgressBar() : CPropertyPage(CPageProgressBar::IDD)
{
	//{{AFX_DATA_INIT(CPageProgressBar)
	m_nStatus = 0;
	m_nValue = 0;
	//}}AFX_DATA_INIT
}

CPageProgressBar::~CPageProgressBar()
{
}

void CPageProgressBar::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageProgressBar)
	DDX_CBIndex(pDX, IDC_COMBO_STATUS, m_nStatus);
	DDX_Slider(pDX, IDC_SLIDER_PROGRESS, m_nValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageProgressBar, CPropertyPage)
	//{{AFX_MSG_MAP(CPageProgressBar)
	ON_CBN_SELCHANGE(IDC_COMBO_STATUS, OnSelChangeComboStatus)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_PROGRESS, OnReleasedCaptureSliderProgress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int nProgressData[] = 
{
	xtpProgressFlagNormal,
	xtpProgressFlagError,
	xtpProgressFlagPaused,
	xtpProgressFlagIndeterminate,
	xtpProgressFlagNoProgress
};

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar message handlers

void CPageProgressBar::OnSelChangeComboStatus() 
{
	UpdateData();

	m_mgrTaskBar.SetProgressBarState(AfxGetMainWnd()->GetSafeHwnd(), nProgressData[m_nStatus]);

	GetDlgItem(IDC_SLIDER_PROGRESS)->EnableWindow(m_nStatus < 3);
	
}

void CPageProgressBar::OnReleasedCaptureSliderProgress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();

	m_mgrTaskBar.SetProgressBarPosition(AfxGetMainWnd()->GetSafeHwnd(), m_nValue);
	
	*pResult = 0;
}
