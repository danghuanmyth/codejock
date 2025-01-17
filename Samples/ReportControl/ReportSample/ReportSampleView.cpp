// ReportSampleView.cpp : implementation of the CReportSampleView class
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
#include "ReportSample.h"

#include "MainFrm.h"
#include "ReportSampleDoc.h"
#include "ReportSampleView.h"
#include "ReportMultilinePaintManager.h"

#include "MessageRecord.h"
#include "TreeViewDlg.h"
#include "TreeEditDlg.h"
#include "FormulaDlg.h"
#include "PerfomanceTestDlg.h"
#include "SmoothScrollView.h"
#include "TaskListView.h"
#include "MergeView.h"
#include "SelectionView.h"
#include "PropertiesView.h"
#include "HeaderFooterView.h"

// Quality Assurance
#include "EmptyDlg.h"
#include "ConstraintsDlg.h"
#include "TestNotificationsDlg.h"
#include "TestPopupDlg.h"
#include "TestAlternateBackgroundDlg.h"
#include "TestDragDropDlg.h"
#include "TestHitTestDlg.h"
#include "TestHeaderAlignmentDlg.h"
#include "TestComboBoxDlg.h"
#include "TestItemTypesDlg.h"
#include "TestMarkupDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// Constants used to identify columns, this will be the column ItemIndex

// Constants used to identify icons used in the ReportControl
#define COLUMN_MAIL_ICON    0
#define COLUMN_CHECK_ICON   2

CString cstrMarkupLongSample(
	_T("<StackPanel Margin='5, 5, 5, 5' VerticalAlignment='Top'")
	_T("HorizontalAlignment='Center'>")
	_T("<TextBlock Padding='0,10,0,0' TextWrapping='Wrap'><Bold>Subject:</Bold> ")
	_T("<Bold>SuitePro</Bold> <Run Foreground='Red'>2009</Run> ")
	_T("Released!</TextBlock>")
	_T("<TextBlock Padding='0,10,0,0'><Bold>Body:</Bold></TextBlock>")
	_T("<TextBlock Padding='10,10,0,0' TextWrapping='Wrap'>")
	_T("<Bold><Run Foreground='Blue'>Codejock</Run> Software</Bold> released ")
	_T("<Bold>SuitePro</Bold> <Run Foreground='Red'>2009</Run> today.  All")
	_T(" development machines <Bold>must</Bold> be updated no later than ")
	_T("<Run Foreground='Red'>06/15/08</Run>.")
	_T("</TextBlock>")
	_T("<TextBlock Padding='10,10,0,0'>")
	_T("   - Management")
	_T("</TextBlock>")
	_T("</StackPanel>"));

CString cstrMarkupShortSample(
	 _T("<StackPanel VerticalAlignment='Top' HorizontalAlignment='Center'>")
	 _T("<TextBlock><Bold>Subject:</Bold> ")
	 _T("<Italic>SuitePro</Italic> <Run Foreground='Red'>2009</Run> ")
	 _T("Released!</TextBlock>")
	 _T("</StackPanel>"));

/////////////////////////////////////////////////////////////////////////////
// CReportSampleView

IMPLEMENT_DYNCREATE(CReportSampleView, CXTPReportView)

BEGIN_MESSAGE_MAP(CReportSampleView, CXTPReportView)
	//{{AFX_MSG_MAP(CReportSampleView)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()

	// Scrolling (Horizontal)
	ON_COMMAND(ID_SCROLLING_HORIZONTAL_BLOCK_COUNT, OnScrollingHorizontalBlockCount)
	ON_COMMAND(ID_SCROLLING_HORIZONTAL_BLOCK_SIZE,  OnScrollingHorizontalBlockSize)
	ON_COMMAND(ID_SCROLLING_HORIZONTAL_SMOOTH,      OnScrollingHorizontalSmooth)
	ON_UPDATE_COMMAND_UI(ID_SCROLLING_HORIZONTAL_BLOCK_COUNT, OnUpdateScrollingHorizontalBlockCount)
	ON_UPDATE_COMMAND_UI(ID_SCROLLING_HORIZONTAL_BLOCK_SIZE,  OnUpdateScrollingHorizontalBlockSize)
	ON_UPDATE_COMMAND_UI(ID_SCROLLING_HORIZONTAL_SMOOTH,      OnUpdateScrollingHorizontalSmooth)

	// Scrolling (Vertical)
	ON_COMMAND(ID_SCROLLING_VERTICAL_BLOCK_COUNT, OnScrollingVerticalBlockCount)
	ON_COMMAND(ID_SCROLLING_VERTICAL_SMOOTH,      OnScrollingVerticalSmooth)
	ON_UPDATE_COMMAND_UI(ID_SCROLLING_VERTICAL_BLOCK_COUNT, OnUpdateScrollingVerticalBlockCount)
	ON_UPDATE_COMMAND_UI(ID_SCROLLING_VERTICAL_SMOOTH,      OnUpdateScrollingVerticalSmooth)

	ON_COMMAND(ID_REPORTCONTROL_DOUBLEBUFFERING,  OnReportDoubleBuffering)
	ON_COMMAND(ID_REPORTCONTROL_LOCKEXPAND,       OnReportLockExpand)
	ON_COMMAND(ID_REPORTCONTROL_WATERMARK,        OnReportWatermark)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_DOUBLEBUFFERING,  OnUpdateReportDoubleBuffering)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_LOCKEXPAND,       OnUpdateReportLockExpand)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_WATERMARK,        OnUpdateReportWatermark)

	ON_COMMAND(ID_ENABLE_PREVIEW, OnEnablePreview)
	ON_UPDATE_COMMAND_UI(ID_ENABLE_PREVIEW, OnUpdateEnablePreview)
	ON_COMMAND(ID_TEST_AUTOGROUPING, OnAutoGrouping)
	ON_UPDATE_COMMAND_UI(ID_TEST_AUTOGROUPING, OnUpdateAutoGrouping)
	ON_COMMAND(ID_TEST_GROUPBY, OnGroupBy)
	ON_UPDATE_COMMAND_UI(ID_TEST_GROUPBY, OnUpdateGroupBy)
	ON_COMMAND(ID_REPORTCONTROL_MARKUP, OnReportMarkup)
	ON_UPDATE_COMMAND_UI(ID_TEST_MARKUP, OnUpdateTestMarkup)
	ON_COMMAND(ID_TEST_GROUPSHADE, OnGroupShade)
	ON_UPDATE_COMMAND_UI(ID_TEST_GROUPSHADE, OnUpdateGroupShade)
	ON_COMMAND(ID_TEST_GROUPSBOLD, OnGroupBold)	
	ON_UPDATE_COMMAND_UI(ID_TEST_GROUPSBOLD, OnUpdateGroupBold)
	ON_COMMAND(ID_REPORTCONTROL_AUTOMATICFORMATTINGSAMPLE, OnReportcontrolAutomaticformattingsample)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_AUTOMATICFORMATTINGSAMPLE, OnUpdateReportcontrolAutomaticformattingsample)
	ON_COMMAND(ID_OPTIONS_ALLOWCOLUMNRESIZE, OnOptionsAllowcolumnresize)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ALLOWCOLUMNRESIZE, OnUpdateOptionsAllowcolumnresize)
	ON_COMMAND(ID_OPTIONS_ALLOWCOLUMNSREMOVE, OnOptionsAllowcolumnsremove)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ALLOWCOLUMNSREMOVE, OnUpdateOptionsAllowcolumnsremove)
	ON_COMMAND(ID_OPTIONS_MULTIPLESELECTION, OnOptionsMultipleselection)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_MULTIPLESELECTION, OnUpdateOptionsMultipleselection)
	ON_COMMAND(ID_OPTIONS_SHOWITEMSINGROUPS, OnOptionsShowitemsingroups)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SHOWITEMSINGROUPS, OnUpdateOptionsShowitemsingroups)

	ON_COMMAND(ID_OPTIONS_SHOW_FOOTER, OnOptionsShowFooter)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SHOW_FOOTER, OnUpdateOptionsShowFooter)
	
	ON_COMMAND(ID_TEST_TREEVIEWDIALOG, OnTreeViewDlg)
	ON_COMMAND(ID_TEST_TREEEDITDIALOG, OnTreeEditDlg)
	ON_COMMAND(ID_TEST_FORMULADIALOG,  OnFormulaDlg)
	ON_COMMAND(ID_TEST_TASKLIST,       OnTestTasklist)
	ON_COMMAND(ID_TEST_MERGE,          OnTestMerge)
	ON_COMMAND(ID_TEST_SELECTION,      OnTestSelection)
	ON_COMMAND(ID_TEST_HEADERFOOTER,   OnTestHeaderFooter)
	ON_COMMAND(ID_TEST_PERFOMANCE,     OnTestPerfomance)
	ON_COMMAND(ID_TEST_PROPERTIES,     OnTestProperties)
	ON_COMMAND(ID_TEST_EMPTY,                OnTestEmpty)
	ON_COMMAND(ID_TEST_CONSTRAINTS,          OnTestConstraints)
	ON_COMMAND(ID_TEST_SMOOTH_SCROLL,        OnTestSmoothScroll)
	ON_COMMAND(ID_TEST_NOTIFICATIONS,        OnTestNotifications)
	ON_COMMAND(ID_TEST_POPUP,                OnTestPopup)
	ON_COMMAND(ID_TEST_ALTERNATE_BACKGROUND, OnTestAlternateBackground)
	ON_COMMAND(ID_TEST_DRAG_DROP,            OnTestDragDrop)
	ON_COMMAND(ID_TEST_HITTEST,              OnTestHitTest)
	ON_COMMAND(ID_TEST_HEADER_ALIGNMENT,     OnTestHeaderAlignment)
	ON_COMMAND(ID_TEST_COMBOBOX,             OnTestComboBox)
	ON_COMMAND(ID_TEST_ITEM_TYPES,           OnTestItemTypes)
	ON_COMMAND(ID_TEST_MARKUP,               OnTestMarkup)

	ON_COMMAND(ID_OPTIONS_AUTOMATICCOLUMNSIZING, OnOptionsAutomaticcolumnsizing)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_AUTOMATICCOLUMNSIZING, OnUpdateOptionsAutomaticcolumnsizing)
	ON_COMMAND(ID_REPORTCONTROL_MULTILINESAMPLE, OnReportcontrolMultilinesample)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_MULTILINESAMPLE, OnUpdateReportcontrolMultilinesample)
	ON_COMMAND(ID_REPORTHEADER_ALLOWCOLUMNREORDER, OnReportheaderAllowcolumnreorder)
	ON_UPDATE_COMMAND_UI(ID_REPORTHEADER_ALLOWCOLUMNREORDER, OnUpdateReportheaderAllowcolumnreorder)
	ON_COMMAND_RANGE(ID_COLUMNSTYLE_SHADED, ID_COLUMNSTYLE_OFFICE2007, OnColumnStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COLUMNSTYLE_SHADED, ID_COLUMNSTYLE_OFFICE2007, OnUpdateColumnStyle)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_0, OnUpdateOptionsFreezecolumns0)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_1, OnUpdateOptionsFreezecolumns1)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_2, OnUpdateOptionsFreezecolumns2)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_3, OnUpdateOptionsFreezecolumns3)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_0, OnOptionsFreezecolumns0)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_1, OnOptionsFreezecolumns1)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_2, OnOptionsFreezecolumns2)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_3, OnOptionsFreezecolumns3)
	ON_COMMAND(ID_REPORTCONTROL_RIGHTTOLEFT, OnReportcontrolRighttoleft)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_RIGHTTOLEFT, OnUpdateReportcontrolRighttoleft)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_1, OnOptionsFreezecolumnsDivider1)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_1, OnUpdateOptionsFreezecolumnsDivider1)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_2, OnOptionsFreezecolumnsDivider2)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_2, OnUpdateOptionsFreezecolumnsDivider2)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_HEADER, OnOptionsFreezecolumnsDividerHeader)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_HEADER, OnUpdateOptionsFreezecolumnsDividerHeader)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_NONE,   OnOptionsFreezecolumnsDividerNone)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_NONE,   OnUpdateOptionsFreezecolumnsDividerNone)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_SHADE,  OnOptionsFreezecolumnsDividerShade)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_SHADE,  OnUpdateOptionsFreezecolumnsDividerShade)
	//}}AFX_MSG_MAP

#if _XTPLIB_VERSION_PREFIX >= 1520
	// Grid color
	ON_COMMAND(ID_GRID_COLOR_RED,					OnGridColorRed)
	ON_COMMAND(ID_GRID_COLOR_GREEN,				OnGridColorGreen)
	ON_COMMAND(ID_GRID_COLOR_BLUE,				OnGridColorBlue)
	ON_UPDATE_COMMAND_UI(ID_GRID_COLOR_RED,	OnUpdateGridColorRed)
	ON_UPDATE_COMMAND_UI(ID_GRID_COLOR_GREEN,	OnUpdateGridColorGreen)
	ON_UPDATE_COMMAND_UI(ID_GRID_COLOR_BLUE,	OnUpdateGridColorBlue)
#endif

#if _XTPLIB_VERSION_PREFIX >= 1511
	// Report behavior
	ON_COMMAND(ID_BEHAVIOR_CODEJOCKDEFAULT, OnBehaviorCodejockDefault)
	ON_COMMAND(ID_BEHAVIOR_CODEJOCK1502,    OnBehaviorCodejock1502)
	ON_COMMAND(ID_BEHAVIOR_CODEJOCK1501,    OnBehaviorCodejock1501)
	ON_COMMAND(ID_BEHAVIOR_CODEJOCK1342,    OnBehaviorCodejock1342)
	ON_COMMAND(ID_BEHAVIOR_OUTLOOK2003,     OnBehaviorOutlook2003)
	ON_COMMAND(ID_BEHAVIOR_OUTLOOK2007,     OnBehaviorOutlook2007)
	ON_COMMAND(ID_BEHAVIOR_OUTLOOK2010,     OnBehaviorOutlook2010)
	ON_COMMAND(ID_BEHAVIOR_EXCEL2003,       OnBehaviorExcel2003)
	ON_COMMAND(ID_BEHAVIOR_EXCEL2007,       OnBehaviorExcel2007)
	ON_COMMAND(ID_BEHAVIOR_EXCEL2010,       OnBehaviorExcel2010)
	ON_COMMAND(ID_BEHAVIOR_CUSTOM,          OnBehaviorCustom)

	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_CODEJOCKDEFAULT, OnUpdateBehaviorCodejockDefault)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_CODEJOCK1502,    OnUpdateBehaviorCodejock1502)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_CODEJOCK1501,    OnUpdateBehaviorCodejock1501)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_CODEJOCK1342,    OnUpdateBehaviorCodejock1342)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_OUTLOOK2003,     OnUpdateBehaviorOutlook2003)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_OUTLOOK2007,     OnUpdateBehaviorOutlook2007)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_OUTLOOK2010,     OnUpdateBehaviorOutlook2010)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_EXCEL2003,       OnUpdateBehaviorExcel2003)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_EXCEL2007,       OnUpdateBehaviorExcel2007)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_EXCEL2010,       OnUpdateBehaviorExcel2010)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_CUSTOM,          OnUpdateBehaviorCustom)
#endif
	
	// Standard printing commands

	ON_COMMAND_RANGE(ID_GRID_HORIZONTAL_NOGRIDLINES, ID_GRID_HORIZONTAL_SOLID, OnGridHorizontal)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GRID_HORIZONTAL_NOGRIDLINES, ID_GRID_HORIZONTAL_SOLID, OnUpdateGridHorizontal)

	ON_COMMAND_RANGE(ID_GRID_VERTICAL_NOGRIDLINES, ID_GRID_VERTICAL_SOLID, OnGridVertical)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GRID_VERTICAL_NOGRIDLINES, ID_GRID_VERTICAL_SOLID, OnUpdateGridVertical)

	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CReportSampleView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PAGE_SETUP, CXTPReportView::OnFilePageSetup)

	ON_NOTIFY(NM_CLICK, XTP_ID_REPORT_CONTROL, OnReportItemClick)
	ON_NOTIFY(XTP_NM_REPORT_HYPERLINK , XTP_ID_REPORT_CONTROL, OnReportHyperlinkClick)
	ON_NOTIFY(NM_RCLICK, XTP_ID_REPORT_CONTROL, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, XTP_ID_REPORT_CONTROL, OnReportItemDblClick)
	ON_NOTIFY(XTP_NM_REPORT_HEADER_RCLICK, XTP_ID_REPORT_CONTROL, OnReportColumnRClick)
	ON_NOTIFY(NM_KEYDOWN, XTP_ID_REPORT_CONTROL, OnReportKeyDown)
	ON_NOTIFY(LVN_BEGINDRAG, XTP_ID_REPORT_CONTROL, OnReportBeginDrag)
	ON_NOTIFY(XTP_NM_REPORT_BEFORE_PASTE_FROMTEXT, XTP_ID_REPORT_CONTROL, OnReportBeforePasteFromText)
	ON_NOTIFY(XTP_NM_REPORT_BEFORE_PASTE, XTP_ID_REPORT_CONTROL, OnReportBeforePaste)

	ON_NOTIFY(XTP_NM_REPORT_GROUPORDERCHANGED, XTP_ID_REPORT_CONTROL, OnReportGroupOrderChanged)
	ON_NOTIFY(XTP_NM_REPORT_GIVEFEEDBACK,      XTP_ID_REPORT_CONTROL, OnReportGiveFeedback)

	ON_COMMAND(ID_REPORTCONTROL_DEVTEST, OnReportcontrolDevtest)

	ON_COMMAND(ID_REPORTCONTROL_WYSIWYG_PRINT, OnReportWYSIWYG)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_WYSIWYG_PRINT, OnUpdateReportWYSIWYG)

	ON_COMMAND(ID_REPORTCONTROL_ICONVIEW, OnReportIconview)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_ICONVIEW, OnUpdateReportIconview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportSampleView construction/destruction

CReportSampleView::CReportSampleView()
	: m_pWndMerge       (NULL)
	, m_pWndSelection   (NULL)
	, m_pWndSmoothScroll(NULL)
{
	m_bWatermark = FALSE;
	m_bAutomaticFormating = FALSE;
	m_pTaskFrame = 0;
	m_pHeaderFooterFrame = 0;
	m_pPropertiesFrame = 0;
	m_bMultilineSample = FALSE;
}

CReportSampleView::~CReportSampleView()
{
}

BOOL CReportSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CView::PreCreateWindow(cs))
		return FALSE;

	//cs.dwExStyle |= WS_EX_STATICEDGE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CReportSampleView diagnostics

#ifdef _DEBUG
void CReportSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CReportSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CReportSampleDoc* CReportSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReportSampleDoc)));
	return (CReportSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportSampleView message handlers

int CReportSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_ilIcons.Create(16,16, ILC_COLOR24|ILC_MASK, 0, 1));
	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(IDB_BMREPORT));
	m_ilIcons.Add(&bmp, RGB(255, 0, 255));

	CXTPReportControl& wndReport = GetReportCtrl();
	wndReport.SetImageList(&m_ilIcons);

	//
	//  Add sample columns
	//
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_IMPORTANCE, _T("Importance"), 18, FALSE, 1));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_ICON, _T("Message Class"), 18, FALSE, COLUMN_MAIL_ICON));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_ATTACHMENT, _T("Attachment"), 18, FALSE, 7));
	CXTPReportColumn* pNewPMCol =
		wndReport.AddColumn(new CXTPReportColumn(COLUMN_FROM, _T("From"), 100));
	pNewPMCol->SetPlusMinus(TRUE);
	pNewPMCol->SetExpanded(TRUE);
	pNewPMCol->SetNextVisualBlock(2);

	wndReport.AddColumn(new CXTPReportColumn(COLUMN_SUBJECT,      _T("Subject"), 180));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_RECEIVED,     _T("Received"), 80));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_SIZE,         _T("Size"), 55, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_CHECK,        _T("Checked"), 18, FALSE, COLUMN_CHECK_ICON));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_PRICE,        _T("Price"), 80, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_SENT,         _T("Sent"), 150, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_CREATED,      _T("Created"), 80, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_CONVERSATION, _T("Conversation"), 30, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_CONTACTS,     _T("Contacts"), 30, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_MESSAGE,      _T("Message"), 80, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_CC,           _T("CC"), 80, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_CATEGORIES,   _T("Categories"), 30, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_AUTOFORWARD,  _T("Auto Forward"), 30, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_AUTOARCHIVE,  _T("Do not autoarchive"), 30, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_DUE_BY,       _T("Due by"), 30, TRUE, XTP_REPORT_NOICON, TRUE, FALSE));
#if 1
	//  Add sample records
	OnAutoGrouping();		
	AddSampleRecords();

	wndReport.GetRecords()->GetAt(3)->GetItem(COLUMN_FROM)->AddHyperlink(new CXTPReportHyperlink(12, 26));
	((CXTPReportRecordItem*)(wndReport.GetRecords()->GetAt(3)->GetItemPreview()))->AddHyperlink(new CXTPReportHyperlink(27, 7));
	((CXTPReportRecordItem*)(wndReport.GetRecords()->GetAt(3)->GetItemPreview()))->AddHyperlink(new CXTPReportHyperlink(110, 13));
	((CXTPReportRecordItem*)(wndReport.GetRecords()->GetAt(5)->GetItemPreview()))->AddHyperlink(new CXTPReportHyperlink(21, 26));
	((CXTPReportRecordItem*)(wndReport.GetRecords()->GetAt(5)->GetItemPreview()))->AddHyperlink(new CXTPReportHyperlink(123, 26));
	wndReport.GetRecords()->GetAt(8)->GetItem(COLUMN_FROM)->AddHyperlink(new CXTPReportHyperlink(0, 28));
	wndReport.GetRecords()->GetAt(3)->SetEditable(FALSE);
#endif

#if _XTPLIB_VERSION_PREFIX >= 1511
	wndReport.GetToolTipContext()->SetStyle(xtpToolTipResource);
#else
	wndReport.GetToolTipContext()->SetStyle(xtpToolTipOffice2007);
#endif

	OnGroupBy();

	wndReport.Populate();

	wndReport.EnableDragDrop(_T("ReportSampleView"), xtpReportAllowDrag | xtpReportAllowDrop);

#if _XTPLIB_VERSION_PREFIX >= 1511
	wndReport.GetPaintManager()->SetColumnStyle(xtpReportColumnResource);
#else
	wndReport.GetPaintManager()->SetColumnStyle(xtpReportColumnOffice2007);
#endif
	
	m_wndVScrollBar.Create(WS_CHILD | WS_VISIBLE | SBS_VERT, CRect(0, 0, 0, 0), this, 100);
	m_wndVScrollBar.SetScrollBarStyle(xtpScrollStyleOffice2007Dark);
	SetScrollBarCtrl(&m_wndVScrollBar, FALSE);

	m_wndHScrollBar.Create(WS_CHILD | WS_VISIBLE | SBS_HORZ, CRect(0, 0, 0, 0), this, 100);
	m_wndHScrollBar.SetScrollBarStyle(xtpScrollStyleOffice2007Dark);
	SetScrollBarCtrl(&m_wndHScrollBar, TRUE);

	wndReport.FocusSubItems(TRUE);
	wndReport.m_bSortedDragDrop = TRUE;
	
	wndReport.GetImageManager()->SetImageList(IDB_ICONVIEWTEST, 32, 0,  RGB(255, 0, 255));

	wndReport.GetPaintManager()->ShowWYSIWYGMarkers(TRUE);
	wndReport.GetPaintManager()->SetDrawGridForEmptySpace(TRUE);

	// Set header/footer divider style
	wndReport.GetPaintManager()->SetHeaderRowsDividerStyle(xtpReportFixedRowsDividerBold);
	wndReport.GetPaintManager()->SetFooterRowsDividerStyle(xtpReportFixedRowsDividerBold);
	wndReport.GetPaintManager()->m_clrHeaderRowsDivider = RGB(255,0,0);
	wndReport.GetPaintManager()->m_clrFooterRowsDivider = RGB(0,0,255);

	// Set hyperlink style
#if _XTPLIB_VERSION_PREFIX >= 1511
	wndReport.GetPaintManager()->m_pHyperlinkStyle->SetColor(RGB(0,0,255));
	wndReport.GetPaintManager()->m_pHyperlinkStyle->SetTextDecoration(xtpReportTextDecorationNone);
	wndReport.GetPaintManager()->m_pHyperlinkHoverStyle->SetColor(RGB(0,0,255));
	wndReport.GetPaintManager()->m_pHyperlinkHoverStyle->SetTextDecoration(xtpReportTextDecorationUnderline);
#endif

	// Enable smooth scrolling
#if _XTPLIB_VERSION_PREFIX >= 1511
	wndReport.SetScrollMode(xtpReportOrientationAll, xtpReportScrollModeSmooth);
#endif

#if _XTPLIB_VERSION_PREFIX >= 1511
	OnBehaviorCodejockDefault();
#endif
	OnReportWatermark();



	CXTPReportViewPrintOptions *pPrintOptions = GetPrintOptions();
	pPrintOptions->GetPageHeader()->m_strLeft   = _T("Left");
	pPrintOptions->GetPageHeader()->m_strCenter = _T("Center");
	pPrintOptions->GetPageHeader()->m_strRight  = _T("Right");

	pPrintOptions->GetPageFooter()->m_strLeft   = _T("Left");
	pPrintOptions->GetPageFooter()->m_strCenter = _T("Center");
	pPrintOptions->GetPageFooter()->m_strRight  = _T("Right");

	//wndReport.ShowFooter(TRUE);

	return 0;
}

// Before self destroying destroy all child forms 
void CReportSampleView::OnDestroy()
{
	SaveReportState();

	if (m_pTaskFrame)
		m_pTaskFrame->DestroyWindow();
	if (m_pPropertiesFrame)
		m_pPropertiesFrame->DestroyWindow();
	if (m_pHeaderFooterFrame)
		m_pHeaderFooterFrame->DestroyWindow();

	if (m_pWndMerge)
	{
		m_pWndMerge->DestroyWindow();
	}

	if (m_pWndSelection)
	{
		m_pWndSelection->DestroyWindow();
	}

	CView::OnDestroy();
}

// Preview is a text message which is shown for every row, 
// if ReportControl is in Preview mode.
// In this sample preview text is equal to Message text, 
// but it doesn't have to be always used in such way 
void CReportSampleView::OnEnablePreview()
{
	GetReportCtrl().EnablePreviewMode(!GetReportCtrl().IsPreviewMode());
	GetReportCtrl().Populate();
}

void CReportSampleView::OnUpdateEnablePreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsPreviewMode());
}

void CReportSampleView::OnGroupBy()
{
	GetReportCtrl().ShowGroupBy(!GetReportCtrl().IsGroupByVisible());
}

void CReportSampleView::OnUpdateGroupBy(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsGroupByVisible());
}

void CReportSampleView::OnReportMarkup()
{
	BOOL bEnabled = GetReportCtrl().GetMarkupContext() != NULL;
	
	bEnabled = !bEnabled; // enable ALL

	GetReportCtrl().EnableMarkup(bEnabled);

	if (GetReportCtrl().GetMarkupContext())
	{
		GetReportCtrl().GetColumns()->GetAt(COLUMN_SUBJECT)->SetCaption(cstrMarkupShortSample);
		GetReportCtrl().GetRecords()->GetAt(9)->GetItem(COLUMN_SUBJECT)->SetCaption(cstrMarkupShortSample);
		GetReportCtrl().GetRecords()->GetAt(9)->GetItemPreview()->SetCaption(cstrMarkupLongSample);		
		GetReportCtrl().RedrawControl();
	}
}

void CReportSampleView::OnUpdateTestMarkup(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetMarkupContext() != NULL);
}

// Toggles shady style for group heading
void CReportSampleView::OnGroupShade()
{
	GetReportCtrl().ShadeGroupHeadings(!GetReportCtrl().IsShadeGroupHeadingsEnabled());
}

void CReportSampleView::OnUpdateGroupShade(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsShadeGroupHeadingsEnabled());
}

// Toggles bold style for group heading
void CReportSampleView::OnGroupBold()
{
	GetReportCtrl().SetGroupRowsBold(!GetReportCtrl().IsGroupRowsBold());
	GetReportCtrl().RedrawControl();
}

void CReportSampleView::OnUpdateGroupBold(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsGroupRowsBold());
}

void CReportSampleView::OnAutoGrouping()
{
	if (GetReportCtrl().GetColumns()->GetGroupsOrder()->GetCount() == 0)
	{
		CXTPReportColumn* pColFrom = GetReportCtrl().GetColumns()->Find(COLUMN_FROM);

		GetReportCtrl().GetColumns()->GetGroupsOrder()->Clear();

		GetReportCtrl().GetColumns()->GetGroupsOrder()->Add(pColFrom);
	}
	else
	{
		GetReportCtrl().GetColumns()->GetGroupsOrder()->Clear();
	}
	GetReportCtrl().Populate();
}

void CReportSampleView::OnUpdateAutoGrouping(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetColumns()->GetGroupsOrder()->GetCount() > 0);
}

void CReportSampleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	if (m_wndSubList.GetSafeHwnd() == NULL)
	{
		m_wndSubList.SubclassDlgItem(IDC_COLUMNLIST, &pWnd->m_wndFieldChooser);
		GetReportCtrl().GetColumns()->GetReportHeader()->SetSubListCtrl(&m_wndSubList);
	}

	if (m_wndFilterEdit.GetSafeHwnd() == NULL)
	{
		m_wndFilterEdit.SubclassDlgItem(IDC_FILTEREDIT, &pWnd->m_wndFilterEdit);
		GetReportCtrl().GetColumns()->GetReportHeader()->SetFilterEditCtrl(&m_wndFilterEdit);
	}

	GetReportCtrl().GetPaintManager()->m_bShowLockIcon = TRUE;
	//GetReportCtrl().GetPaintManager()->m_bUseShellIcon = TRUE;
}

void CReportSampleView::LoadReportState()
{
#ifdef XML_STATE
	CXTPPropExchangeXMLNode px(TRUE, 0, _T("ReportControl"));
	if (!px.LoadFromFile(_T("c:\\ReportControl.xml")))
		return;
	
	GetReportCtrl().DoPropExchange(&px);

	CXTPPropExchangeSection secOthers(px.GetSection(_T("Others")));	
	BOOL bMultilineSample = FALSE;
	PX_Bool(&secOthers, _T("MultilineSample"), bMultilineSample, FALSE);
	
	m_bMultilineSample = !bMultilineSample;
	OnReportcontrolMultilinesample();

#else	
	UINT nBytes = 0;
	LPBYTE pData = 0;

	if (!AfxGetApp()->GetProfileBinary(_T("ReportControl"), _T("State"), &pData, &nBytes))
		return;

	CMemFile memFile(pData, nBytes);
	CArchive ar (&memFile,CArchive::load);

	try
	{
		GetReportCtrl().SerializeState(ar);

	}
	catch (COleException* pEx)
	{
		pEx->Delete ();
	}
	catch (CArchiveException* pEx)
	{
		pEx->Delete ();
	}

	ar.Close();
	memFile.Close();
	delete[] pData;

	// others
	m_bMultilineSample = !AfxGetApp()->GetProfileInt(_T("ReportControl"), _T("MultilineSample"), 0);
	OnReportcontrolMultilinesample();
#endif
}

void CReportSampleView::SaveReportState()
{
#ifdef XML_STATE
	
	CXTPPropExchangeXMLNode px(FALSE, 0, _T("ReportControl"));
	GetReportCtrl().DoPropExchange(&px);

	CXTPPropExchangeSection secOthers(px.GetSection(_T("Others")));	
	BOOL bMultilineSample = m_bMultilineSample;
	PX_Bool(&secOthers, _T("MultilineSample"), bMultilineSample, FALSE);
		
	// Save All Records
	//CXTPPropExchangeSection secRecords(px.GetSection(_T("Records")));
	//GetReportCtrl().GetRecords()->DoPropExchange(&secRecords);

	px.SaveToFile(_T("c:\\ReportControl.xml"));

#else
	CMemFile memFile;
	CArchive ar (&memFile,CArchive::store);

	GetReportCtrl().SerializeState(ar);

	ar.Flush();

	DWORD nBytes = (DWORD)memFile.GetPosition();
	LPBYTE pData = memFile.Detach();

	AfxGetApp()->WriteProfileBinary(_T("ReportControl"), _T("State"), pData, nBytes);

	ar.Close();
	memFile.Close();
	free(pData);

	AfxGetApp()->WriteProfileInt(_T("ReportControl"), _T("MultilineSample"), m_bMultilineSample);
#endif

}


#define ID_REMOVE_ITEM  1
#define ID_SORT_ASC     2
#define ID_SORT_DESC        3
#define ID_SORT_NO      99
#define ID_GROUP_BYTHIS 4
#define ID_SHOW_GROUPBOX        5
#define ID_SHOW_FIELDCHOOSER 6
#define ID_COLUMN_BESTFIT       7
#define ID_COLUMN_ARRANGEBY 100
#define ID_COLUMN_ALIGMENT  200
#define ID_COLUMN_ALIGMENT_TEXT  210
#define ID_COLUMN_ALIGMENT_LEFT   211
#define ID_COLUMN_ALIGMENT_RIGHT  212
#define ID_COLUMN_ALIGMENT_CENTER 213
#define ID_COLUMN_ALIGMENT_ICON  220
#define ID_COLUMN_ICON_ALIGMENT_LEFT   221
#define ID_COLUMN_ICON_ALIGMENT_RIGHT  222
#define ID_COLUMN_ICON_ALIGMENT_CENTER 223
#define ID_COLUMN_SHOW      500


CString LoadResourceString(UINT nID)
{
	CString str;
	VERIFY(str.LoadString(nID));
	return str;
}

// When user does a right click on column header, generate popup menu
// Procedure contains handlers of pressing all buttons in popup menu
void CReportSampleView::OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify->pColumn);
	CPoint ptClick = pItemNotify->pt;

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	// create main menu items
	menu.AppendMenu(MF_STRING, ID_SORT_ASC, LoadResourceString(IDS_SORTASC));
	menu.AppendMenu(MF_STRING, ID_SORT_DESC, LoadResourceString(IDS_SORTDESC));

	menu.AppendMenu(MF_STRING, ID_SORT_NO, LoadResourceString(IDS_SORT_NO));

	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
	menu.AppendMenu(MF_STRING, ID_GROUP_BYTHIS, LoadResourceString(IDS_GROUPBYFIELD));
	menu.AppendMenu(MF_STRING, ID_SHOW_GROUPBOX, LoadResourceString(IDS_GROUPBYBOX));
	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
	menu.AppendMenu(MF_STRING, ID_REMOVE_ITEM, LoadResourceString(IDS_REMOVECOL));
	menu.AppendMenu(MF_STRING, ID_SHOW_FIELDCHOOSER, LoadResourceString(IDS_FIELDCHOOSER));
	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
	menu.AppendMenu(MF_STRING, ID_COLUMN_BESTFIT, LoadResourceString(IDS_BESTFIT));

	if (GetReportCtrl().IsGroupByVisible())
	{
		menu.CheckMenuItem(ID_SHOW_GROUPBOX, MF_BYCOMMAND|MF_CHECKED);
	}
	if (GetReportCtrl().GetReportHeader()->IsShowItemsInGroups())
	{
		menu.EnableMenuItem(ID_GROUP_BYTHIS, MF_BYCOMMAND|MF_DISABLED);
	}


	CXTPReportColumns* pColumns = GetReportCtrl().GetColumns();
	CXTPReportColumn* pColumn = pItemNotify->pColumn;

	// create arrange by items
	CMenu menuArrange;
	VERIFY(menuArrange.CreatePopupMenu());
	int nColumnCount = pColumns->GetCount();
	int nColumn;
	for (nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPReportColumn* pCol = pColumns->GetAt(nColumn);
		if (pCol && pCol->IsVisible())
		{
			CString sCaption = pCol->GetCaption();
			if (!sCaption.IsEmpty())
				menuArrange.AppendMenu(MF_STRING, ID_COLUMN_ARRANGEBY + nColumn, sCaption);
		}
	}

	menuArrange.AppendMenu(MF_SEPARATOR, 60, (LPCTSTR)NULL);

	menuArrange.AppendMenu(MF_STRING, ID_COLUMN_ARRANGEBY + nColumnCount,
		LoadResourceString(IDS_SHOWINGROUPS));
	menuArrange.CheckMenuItem(ID_COLUMN_ARRANGEBY + nColumnCount,
		MF_BYCOMMAND | ((GetReportCtrl().GetReportHeader()->IsShowItemsInGroups()) ? MF_CHECKED : MF_UNCHECKED)  );
	menu.InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuArrange.m_hMenu,
		LoadResourceString(IDS_ARRANGEBY));

	// create columns items
	CMenu menuColumns;
	VERIFY(menuColumns.CreatePopupMenu());
	for (nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPReportColumn* pCol = pColumns->GetAt(nColumn);
		CString sCaption = pCol->GetCaption();
		//if (!sCaption.IsEmpty())
		menuColumns.AppendMenu(MF_STRING, ID_COLUMN_SHOW + nColumn, sCaption);
		menuColumns.CheckMenuItem(ID_COLUMN_SHOW + nColumn,
				MF_BYCOMMAND | (pCol->IsVisible() ? MF_CHECKED : MF_UNCHECKED) );
	}

	menu.InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuColumns.m_hMenu,
		LoadResourceString(IDS_COLUMNS));

	// create alignment submenu
	CMenu menuAlign;
	VERIFY(menuAlign.CreatePopupMenu());

	////  create Text alignment menu
	CMenu menuAlignText;
	VERIFY(menuAlignText.CreatePopupMenu());

	menuAlignText.AppendMenu(MF_STRING, ID_COLUMN_ALIGMENT_LEFT,
		LoadResourceString(IDS_ALIGNLEFT));
	menuAlignText.AppendMenu(MF_STRING, ID_COLUMN_ALIGMENT_RIGHT,
		LoadResourceString(IDS_ALIGNRIGHT));
	menuAlignText.AppendMenu(MF_STRING, ID_COLUMN_ALIGMENT_CENTER,
		LoadResourceString(IDS_ALIGNCENTER));

	int nAlignOption = 0;
	switch (pColumn->GetAlignment() & xtpColumnTextMask)
	{
	case xtpColumnTextLeft:
		nAlignOption = ID_COLUMN_ALIGMENT_LEFT;
		break;
	case xtpColumnTextRight:
		nAlignOption = ID_COLUMN_ALIGMENT_RIGHT;
		break;
	case xtpColumnTextCenter:
		nAlignOption = ID_COLUMN_ALIGMENT_CENTER;
		break;
	}

	menuAlignText.CheckMenuItem(nAlignOption, MF_BYCOMMAND | MF_CHECKED);

	menuAlign.InsertMenu(1, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuAlignText.m_hMenu,
		LoadResourceString(IDS_TEXT));

	////  create Icon alignment menu
	CMenu menuAlignIcon;
	VERIFY(menuAlignIcon.CreatePopupMenu());
	
	menuAlignIcon.AppendMenu(MF_STRING, ID_COLUMN_ICON_ALIGMENT_LEFT,
		LoadResourceString(IDS_ALIGNLEFT));
	menuAlignIcon.AppendMenu(MF_STRING, ID_COLUMN_ICON_ALIGMENT_RIGHT,
		LoadResourceString(IDS_ALIGNRIGHT));
	menuAlignIcon.AppendMenu(MF_STRING, ID_COLUMN_ICON_ALIGMENT_CENTER,
		LoadResourceString(IDS_ALIGNCENTER));
	
	nAlignOption = 0;
	switch (pColumn->GetAlignment() & xtpColumnIconMask)
	{
	case xtpColumnIconLeft:
		nAlignOption = ID_COLUMN_ICON_ALIGMENT_LEFT;
		break;
	case xtpColumnIconRight:
		nAlignOption = ID_COLUMN_ICON_ALIGMENT_RIGHT;
		break;
	case xtpColumnIconCenter:
		nAlignOption = ID_COLUMN_ICON_ALIGMENT_CENTER;
		break;
	}
	
	menuAlignIcon.CheckMenuItem(nAlignOption, MF_BYCOMMAND | MF_CHECKED);
	
	menuAlign.InsertMenu(2, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuAlignIcon.m_hMenu,
		LoadResourceString(IDS_ICON));

	///	
	menu.InsertMenu(11, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuAlign.m_hMenu,
		LoadResourceString(IDS_ALIGNMENT));

	// track menu
	int nMenuResult = CXTPCommandBars::TrackPopupMenu(&menu, TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, ptClick.x, ptClick.y, this, NULL);


	// arrange by items
	if (nMenuResult >= ID_COLUMN_ARRANGEBY && nMenuResult < ID_COLUMN_ALIGMENT)
	{
		for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
		{
			CXTPReportColumn* pCol = pColumns->GetAt(nColumn);
			if (pCol && pCol->IsVisible())
			{
				if (nMenuResult == ID_COLUMN_ARRANGEBY + nColumn)
				{
					nMenuResult = ID_SORT_ASC;
					pColumn = pCol;
					break;
				}
			}
		}
		// group by item
		if (ID_COLUMN_ARRANGEBY + nColumnCount == nMenuResult)
		{
			GetReportCtrl().GetReportHeader()->ShowItemsInGroups(
				!GetReportCtrl().GetReportHeader()->IsShowItemsInGroups());
		}
	}

	// process Alignment options
	if (nMenuResult > ID_COLUMN_ALIGMENT_TEXT && nMenuResult < ID_COLUMN_ALIGMENT_ICON)
	{
		int nAlign = pColumn->GetAlignment();
		nAlign &= ~(xtpColumnTextLeft | xtpColumnTextCenter | xtpColumnTextRight);
		
		switch (nMenuResult)
		{
			case ID_COLUMN_ALIGMENT_LEFT :
				pColumn->SetAlignment(nAlign | xtpColumnTextLeft);
				break;
			case ID_COLUMN_ALIGMENT_RIGHT :
				pColumn->SetAlignment(nAlign | xtpColumnTextRight);
				break;
			case ID_COLUMN_ALIGMENT_CENTER  :
				pColumn->SetAlignment(nAlign | xtpColumnTextCenter);
				break;
		}
	}

	// process Alignment options
	if (nMenuResult > ID_COLUMN_ALIGMENT_ICON && nMenuResult < ID_COLUMN_SHOW)
	{
		int nAlign = pColumn->GetAlignment();
		nAlign &= ~(xtpColumnIconLeft | xtpColumnIconCenter | xtpColumnIconRight);
		
		switch (nMenuResult)
		{
		case ID_COLUMN_ICON_ALIGMENT_LEFT:
			pColumn->SetAlignment(nAlign | xtpColumnIconLeft);
			break;
		case ID_COLUMN_ICON_ALIGMENT_RIGHT:
			pColumn->SetAlignment(nAlign | xtpColumnIconRight);
			break;
		case ID_COLUMN_ICON_ALIGMENT_CENTER:
			pColumn->SetAlignment(nAlign | xtpColumnIconCenter);
				break;
		}
	}

	// process column selection item
	if (nMenuResult >= ID_COLUMN_SHOW)
	{
		CXTPReportColumn* pCol = pColumns->GetAt(nMenuResult - ID_COLUMN_SHOW);
		if (pCol)
		{
			pCol->SetVisible(!pCol->IsVisible());
		}
	}

	// other general items
	switch (nMenuResult)
	{
		case ID_REMOVE_ITEM:
			pColumn->SetVisible(FALSE);
			GetReportCtrl().Populate();
			break;
		case ID_SORT_ASC:
		case ID_SORT_DESC:
			if (pColumn && pColumn->IsSortable())
			{
				pColumns->SetSortColumn(pColumn, nMenuResult == ID_SORT_ASC);
				GetReportCtrl().Populate();
			}
			break;
		case ID_SORT_NO:
			pColumns->GetSortOrder()->Clear();
			break;
		case ID_GROUP_BYTHIS:
			if (pColumns->GetGroupsOrder()->IndexOf(pColumn) < 0)
			{
				pColumns->GetGroupsOrder()->Add(pColumn);
			}
			GetReportCtrl().ShowGroupBy(TRUE);
			GetReportCtrl().Populate();
			break;
		case ID_SHOW_GROUPBOX:
			GetReportCtrl().ShowGroupBy(!GetReportCtrl().IsGroupByVisible());
			break;
		case ID_SHOW_FIELDCHOOSER:
			OnShowFieldChooser();
			break;
		case ID_COLUMN_BESTFIT:
			GetReportCtrl().GetColumns()->GetReportHeader()->BestFit(pColumn);
			break;
	}

}

BOOL IsSet(int nReason, int nFlag)
{
	return (nFlag == (nFlag & nReason));
}

void CReportSampleView::OnReportGroupOrderChanged(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTCOLUMNORDERCHANGED *pItemNotify =
		reinterpret_cast<XTP_NM_REPORTCOLUMNORDERCHANGED*>(pNotifyStruct);

	BOOL bColumnGroupOrderChanged  = IsSet(pItemNotify->nReason, xtpReportColumnGroupOrderChanged);
	BOOL bColumnRemovedFromGroupby = IsSet(pItemNotify->nReason, xtpReportColumnRemovedFromGroupby);
}

void CReportSampleView::OnReportGiveFeedback(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTGIVEFEEDBACK *pItemNotify = reinterpret_cast<XTP_NM_REPORTGIVEFEEDBACK*>(pNotifyStruct);

	switch(pItemNotify->dropEffect)
	{
	case DROPEFFECT_NONE:
		break;

	case DROPEFFECT_COPY:
		break;

	case DROPEFFECT_MOVE:
		//SetCursor(LoadCursor(NULL,IDC_CROSS));
		*pResult = 1;
		break;

	case DROPEFFECT_LINK:
		break;
	}
}


void CReportSampleView::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
}

// When user does a right click on row with a group name, generate popup menu
// Procedure contains handlers of pressing all buttons in popup menu
void CReportSampleView::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow)
		return;

	CMenu menu;
	if (pItemNotify->pRow->IsGroupRow())
	{
		VERIFY(menu.LoadMenu(IDR_MENU_CONTEXT_GROUP));
	}
	else
	{
		VERIFY(menu.LoadMenu(IDR_MENU_CONTEXT_ROW));
	}

	// track menu
	int nMenuResult = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(0), TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, pItemNotify->pt.x, pItemNotify->pt.y, this, NULL);

	// general items processing
	switch (nMenuResult)
	{
	case ID_POPUP_COLLAPSEALLGROUPS:
	{
		pItemNotify->pRow->GetControl()->CollapseAll();
		break;
	}
	case ID_POPUP_EXPANDALLGROUPS:
	{
		pItemNotify->pRow->GetControl()->ExpandAll();
		break;
	}

	case ID_POPUP_MARK_READ:
	{
		CMessageRecord *pRecord = DYNAMIC_DOWNCAST(CMessageRecord, pItemNotify->pRow->GetRecord());
		if (pRecord->SetRead(TRUE))
		{
			GetReportCtrl().Populate();
		}
		break;
	}

	case ID_POPUP_MARK_UNREAD:
	{
		CMessageRecord *pRecord = DYNAMIC_DOWNCAST(CMessageRecord, pItemNotify->pRow->GetRecord());
		if (pRecord->SetRead(FALSE))
		{
			GetReportCtrl().Populate();
		}
		break;
	}

	}
}

// Set reaction on clicking hyperlink in some of ReportControl cells
void CReportSampleView::OnReportHyperlinkClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;
	// if click on Hyperlink in Item
	if (pItemNotify->nHyperlink >= 0)
		TRACE(_T("Hyperlink Click : \n row %d \n col %d \n Hyperlink %d\n"),
				pItemNotify->pRow->GetIndex(), pItemNotify->pColumn->GetItemIndex(), pItemNotify->nHyperlink);
}

// Handles clicking ReportControl row.
// If "Checked" item is clicked, change "Checked" attribute for current record
void CReportSampleView::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	TRACE(_T("Click on row %d, col %d\n"),
			pItemNotify->pRow->GetIndex(), pItemNotify->pColumn->GetItemIndex());

//MD - another way to fix wrong reaction on column checkbox click - comment line GetReportCtrl().Populate();
//	instead of 	adding condition if (!bCheckBoxClicked)in function CXTPReportRecordItem::OnClick
	if (pItemNotify->pColumn->GetItemIndex() == COLUMN_CHECK)
	{
//		GetReportCtrl().Populate();
//Here we can have more reasonable reaction on Checked / Unchecked field state changed
	}
}

// Handles key pressing. If pressed key is RETURN, then change "Read" attribute
// of current record to True.
// Keys like Up/Down are handled by the control itself with the
// default behavior.
void CReportSampleView::OnReportKeyDown(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	LPNMKEY lpNMKey = (LPNMKEY)pNotifyStruct;

	if (!GetReportCtrl().GetFocusedRow())
		return;

	if (lpNMKey->nVKey == VK_RETURN)
	{
		CMessageRecord* pRecord = DYNAMIC_DOWNCAST(CMessageRecord, GetReportCtrl().GetFocusedRow()->GetRecord());
		if (pRecord)
		{
			if (pRecord->SetRead(TRUE))
			{
				GetReportCtrl().Populate();
			}
		}
	}
}

// Handles double clicking ReportControl item.
// If "Read" attribute is False, changes it to True
void CReportSampleView::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (pItemNotify->pRow)
	{
		TRACE(_T("Double Click on row %d\n"),
			pItemNotify->pRow->GetIndex());

		CMessageRecord* pRecord = DYNAMIC_DOWNCAST(CMessageRecord, pItemNotify->pRow->GetRecord());
		if (pRecord)
		{
			if (pRecord->SetRead(TRUE))
			{
				GetReportCtrl().Populate();
			}
		}
	}
}

// FieldChooser is used to add or remove fields (i.e. columns) using drag-and-drop. 
// FieldChooser is an analog of a pool with column headers of none-used columns
void CReportSampleView::OnShowFieldChooser()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	if (pMainFrm)
	{
		BOOL bShow = !pMainFrm->m_wndFieldChooser.IsVisible();
		pMainFrm->ShowControlBar(&pMainFrm->m_wndFieldChooser, bShow, FALSE);
	}
}

// Tree View form demonstrates how hierarchy of ReportControl rows is shown in "tree" style
void CReportSampleView::OnTreeViewDlg()
{
	CTreeViewDlg dlgTreeView;
	dlgTreeView.DoModal();
}

// Tree Edit form demonstrates how hierarchy of ReportControl rows is edited in "tree" style
void CReportSampleView::OnTreeEditDlg()
{
	CTreeEditDlg dlgTreeEdit;
	dlgTreeEdit.DoModal();
}


// Formula form demonstrates how grouprow and formulas work
void CReportSampleView::OnFormulaDlg()
{
	CFormulaDlg dlgFormula;
	dlgFormula.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// Quality assurance
/////////////////////////////////////////////////////////////////////////////

void CReportSampleView::OnTestEmpty()
{
	CEmptyDlg dlgEmpty;
	dlgEmpty.DoModal();
}

void CReportSampleView::OnTestConstraints()
{
	CConstraintsDlg dlgConstraints;
	dlgConstraints.DoModal();
}

void CReportSampleView::OnTestNotifications()
{
	CTestNotificationsDlg dlgNotifications;
	dlgNotifications.DoModal();
}

void CReportSampleView::OnTestPopup()
{
	CTestPopupDlg dlgPopup;
	dlgPopup.DoModal();
}

void CReportSampleView::OnTestAlternateBackground()
{
	CTestAlternateBackgroundDlg dlgAlternateBackground;
	dlgAlternateBackground.DoModal();
}

void CReportSampleView::OnTestDragDrop()
{
	CTestDragDropDlg dlgDragDrop;
	dlgDragDrop.DoModal();
}

void CReportSampleView::OnTestHitTest()
{
	CTestHitTestDlg dlgHitTest;
	dlgHitTest.DoModal();
}

void CReportSampleView::OnTestHeaderAlignment()
{
	CTestHeaderAlignmentDlg dlgHeaderAlignment;
	dlgHeaderAlignment.DoModal();
}

void CReportSampleView::OnTestComboBox()
{
	CTestComboBoxDlg dlgComboBox;
	dlgComboBox.DoModal();
}

void CReportSampleView::OnTestItemTypes()
{
	CTestItemTypesDlg dlgItemTypes;
	dlgItemTypes.DoModal();
}

void CReportSampleView::OnTestMarkup()
{
	CTestMarkupDlg dlgMarkup;
	dlgMarkup.DoModal();
}

// If enabled -- allows automatic formating. 
void CReportSampleView::OnReportcontrolAutomaticformattingsample()
{
	m_bAutomaticFormating = !m_bAutomaticFormating;
	GetReportCtrl().RedrawControl();

}

void CReportSampleView::OnUpdateReportcontrolAutomaticformattingsample(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bAutomaticFormating);

}

// Adds a few sample Records to ReportControl. 
void CReportSampleView::AddSampleRecords()
{
	COleDateTime odtSent(COleDateTime::GetCurrentTime());
	COleDateTime odtCreated(COleDateTime::GetCurrentTime());
	COleDateTime odtReceived(COleDateTime::GetCurrentTime());
	CString strFrom;
	CString strMessage;
	CString strSubject;
	CString strEmpty(_T(" "));

	CString strForumLink = _T(" ([url]http://www.codejock.com[/url])");

	CXTPReportControl& wndReport = GetReportCtrl();

	
	strFrom    = _T("postmaster@mail.codejock.com");
	strMessage = _T("Simple Preview Text");
	strSubject = _T("Undeliverable Mail");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 7, TRUE, 5,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8; odtReceived-= 0.8;

	strMessage = _T("Breaks words. Lines are automatically broken between words if a word would extend past the edge of the rectangle specified by the lpRect parameter. A carriage return-linefeed sequence also breaks the line.");
	strSubject = _T("Hi Mary Jane");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("Peter Parker"), _T("RE: ") + strSubject, odtSent, 14, FALSE, 4.3,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;odtReceived-= 0.8;

	strSubject = _T("");
	strMessage = _T("If you have several conditions to be tested together, and you know that one is more likely to pass or fail than the others, you can use a feature called 'short circuit evaluation' to speed the execution of your script. When JScript evaluates a logical expression, it only evaluates as many sub-expressions as required to get a result.");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("James Howlett"), _T("RE:") + strSubject, odtSent, 24, FALSE, 56,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;odtReceived-= 0.8;

	strFrom = _T("Bruce Banner [bbanner@codetoolbox.com]");
	strMessage = _T("The MSDN Visual Studio 6.0 Library also provides information on the tools and technologies available with the Visual Studio suite.");
	strSubject = _T("error C2039: 'Serialize' : is not a member of 'CString'");
	wndReport.AddRecord(new CMessageRecord(msgImportanceLow, TRUE, TRUE, strFrom, _T("Re: ") + strSubject, odtSent, 14, TRUE, 12.2,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;odtReceived-= 0.8;

	strMessage = _T("The Visual Studio Enterprise Edition includes all of the features available with the Visual Studio development tools. When installing the Visual Studio Enterprise Edition, you can elect to install enterprise features for use with these tools. In addition, Visual Basic and Visual C++ are available in separate enterprise editions.");
	strSubject = _T("Download GDI+ version 1.1");
	wndReport.AddRecord(new CMessageRecord(msgImportanceHigh, FALSE, FALSE, _T("QueryReply"), _T("Re: ") + strSubject, odtSent, 13, FALSE, 1.345,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;odtReceived-= 0.8;

	strMessage = _T("The following table (email_example1@address.com) indicates whether a given feature is available with a given tool. If you (email_example2@address.com) acquired a separate enterprise edition of Visual Basic or Visual C++, you can use this table also to identify which of the Visual Studio enterprise features you received with your purchase. (Visual J++ and Visual InterDev are not offered as separate enterprise editions.) In addition, some of these features are available in professional editions with a subset of their enterprise edition functionality.");
	strSubject = _T("I don't understand:");
	wndReport.AddRecord(new CMessageRecord(msgImportanceLow, TRUE, FALSE, _T("James Howlett"), strSubject, odtSent, 24, FALSE, 5.4321,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;odtReceived-= 0.8;

	strMessage = _T("Visual Studio contains many development tools for building your application.");
	strSubject = _T("Re: WIN32_FIND_DATA help ");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, TRUE, _T("Matthew Murdock"), strSubject, odtSent, 14, TRUE, 45,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;odtReceived-= 0.8;

	strMessage = _T("To learn more about how each development tool implements data access, see the following documentation topics.");
	strSubject = _T("Re: Licensing ");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, TRUE, FALSE, _T("Louis Lane"), strSubject, odtSent, 13, TRUE, 0.5,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 8;odtReceived-= 0.8;

	strMessage = _T("Introduces the Data Access Guide, which discusses data access and provides links to information on related tools and technologies.");
	strSubject = _T("Undeliverable Mail");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), strSubject, odtSent, 7, TRUE, 10,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;odtReceived-= 0.8;

	strFrom = _T("CodeToolBox");
	strSubject = _T("[CodeToolBox] Newsletter (10 May 2004)");
	strMessage = _T("An in-between week here at CodeToolBox. VSLive was last week, TechEd is in a couple of weeks; Last month's article winners have been awarded and this month's voting is just starting; Last week was Winter and this week is forecast to be Summer. It makes a developer want to just kick back and crank some code right? Right?");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 7, TRUE, 10,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));
	odtSent -= 7;

	strFrom = _T("Codejock Exchange") + strForumLink;
	strSubject = _T("Good Answer! Capture message send from Net Send");
	strMessage = _T("Congratulations! Your answer has been accepted by SuperMan! You've earned 720 Expert Points and have been rewarded with a grade of A. These points will be added to your overall Expert Point total and to your Expert Point total in the Programming Topic Area.");
	CXTPReportRecord *pRecord = wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 8, FALSE, 720,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));
	odtSent -= 7; odtReceived -= 14;

	strFrom = _T("CodeToolBox.com Team");
	strSubject = _T("CodeToolBox.com Sitewide update April 22nd, 2004");
	strMessage = _T("You have acquired this CodeToolBox.com update because you requested to be on the list. Honest! An explanation is at the bottom of this email, and also info on how to be extracted from the list.");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 46, FALSE, 28,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));
	odtSent -= 7;

	strFrom = _T("Codejock Exchange");
	strSubject = _T("Comment Added: returning a <ma> from a dll");
	strMessage = _T("A comment has been added to this question by: somebody. Click the following URL to read the new comment:");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 5, FALSE, 30,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));
	odtSent -= 7; odtReceived -= 14;

	strFrom = _T("Bruce Wayne");
	strSubject = _T("Comment Added: memory leak in OnEndEdit()?\r\nThis is very bad!");
	strMessage = _T("A comment has been added to this question by: Robin. Click the following URL to read the new comment:");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 5, FALSE, 20,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));
	odtSent -= 7;

	strFrom = _T("Codejock Exchange");
	strSubject = _T("Good Answer!: stl containers");
	strMessage = _T("Congratulations! Your proposed answer has been accepted by TheBeast! You've earned 300 Expert points and have been rewarded with a grade of B.");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 4, FALSE, 2,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));
	odtSent -= 7; odtReceived -= 14;

	strFrom = _T("Codejock Exchange");
	strSubject = _T("Codejock Exchange:  Lost Member Name or Password");
	strMessage = _T("You are receiving this email because you reported that you could not remember your Codejock Exchange Member Name or password.");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 7, FALSE, 1,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));
	odtSent -= 7;

	strFrom = _T("CodejockDirect");
	strSubject = _T("New volume/issues available on CodejockDirect");
	strMessage = _T("New volume/issues are now available for the following on CodejockDirect! * Mathematical and Computer Modelling");
	wndReport.AddRecord(new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 9, FALSE, 12,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));
	odtSent -= 7;

	//for(int i=0; i<10000; i++)
	{
	strFrom = _T("Kyle Rayner");
	strSubject = _T("info");
	strMessage = _T("OR-Library is a collection of test data sets for a variety of problem areas. These test data sets can be accessed via emailing to CodeToolBox.com a message containing the name of the required file, or via ftp/WWW using the addresses given at the bottom of this file.");
	CMessageRecord *pMessage = new CMessageRecord(msgImportanceNormal, FALSE, FALSE, strFrom, strSubject, odtSent, 67, FALSE, 10,
		odtReceived, odtCreated, strSubject, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage);
	wndReport.AddRecord(pMessage);
	odtSent -= 7; odtReceived -= 14;
	}
}

// Set horizontal grid lines style.
// Following styles are available:
//  No Grid lines;
//  Small dots
//  Large Dots
//  Dashes
//  Solid
void CReportSampleView::OnGridHorizontal(UINT nID)
{
	GetReportCtrl().SetGridStyle(FALSE, (XTPReportGridStyle)(nID - ID_GRID_HORIZONTAL_NOGRIDLINES));
}

void CReportSampleView::OnUpdateGridHorizontal(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(((int)pCmdUI->m_nID - ID_GRID_HORIZONTAL_NOGRIDLINES) == GetReportCtrl().GetGridStyle(FALSE));

}

// Set vertical grid lines style.
// Following styles are available:
//  No Grid lines;
//  Small dots
//  Large Dots
//  Dashes
//  Solid
void CReportSampleView::OnGridVertical(UINT nID)
{
	GetReportCtrl().SetGridStyle(TRUE, (XTPReportGridStyle)(nID - ID_GRID_VERTICAL_NOGRIDLINES));

}

void CReportSampleView::OnUpdateGridVertical(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(((int)pCmdUI->m_nID - ID_GRID_VERTICAL_NOGRIDLINES) == GetReportCtrl().GetGridStyle(TRUE));

}

// Allow or forbid column resize  
void CReportSampleView::OnOptionsAllowcolumnresize()
{
	GetReportCtrl().GetReportHeader()->AllowColumnResize(!GetReportCtrl().GetReportHeader()->IsAllowColumnResize());
}

void CReportSampleView::OnUpdateOptionsAllowcolumnresize(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsAllowColumnResize());

}

// Allow or forbid columns removal 
void CReportSampleView::OnOptionsAllowcolumnsremove()
{
	GetReportCtrl().GetReportHeader()->AllowColumnRemove(!GetReportCtrl().GetReportHeader()->IsAllowColumnRemove());

}

void CReportSampleView::OnUpdateOptionsAllowcolumnsremove(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsAllowColumnRemove());
}

// Allow or forbid columns reordering
void CReportSampleView::OnReportheaderAllowcolumnreorder() 
{
	GetReportCtrl().GetReportHeader()->AllowColumnReorder(!GetReportCtrl().GetReportHeader()->IsAllowColumnReorder());
	
}

void CReportSampleView::OnUpdateReportheaderAllowcolumnreorder(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsAllowColumnReorder());
	
}

// Allow or forbid simultaneous selection of several records
void CReportSampleView::OnOptionsMultipleselection()
{
	GetReportCtrl().SetMultipleSelection(!GetReportCtrl().IsMultipleSelection());

}

void CReportSampleView::OnUpdateOptionsMultipleselection(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsMultipleSelection());

}
// Allow or forbid records grouping
void CReportSampleView::OnOptionsShowitemsingroups()
{
	GetReportCtrl().GetReportHeader()->ShowItemsInGroups(!GetReportCtrl().GetReportHeader()->IsShowItemsInGroups());

	if (!GetReportCtrl().GetReportHeader()->IsShowItemsInGroups())
	{
		GetReportCtrl().GetColumns()->GetGroupsOrder()->Clear();
		GetReportCtrl().Populate();
	}
}

void CReportSampleView::OnUpdateOptionsShowitemsingroups(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsShowItemsInGroups());	
}


void CReportSampleView::OnOptionsShowFooter()
{
	GetReportCtrl().ShowFooter(!GetReportCtrl().IsFooterVisible());
}

void CReportSampleView::OnUpdateOptionsShowFooter(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsFooterVisible() ? 1 : 0);
}

// Allow or forbid automatic columns resizing
void CReportSampleView::OnOptionsAutomaticcolumnsizing()
{
	GetReportCtrl().GetReportHeader()->SetAutoColumnSizing(!GetReportCtrl().GetReportHeader()->IsAutoColumnSizing());

	if (GetReportCtrl().GetReportHeader()->IsAutoColumnSizing())
	{

		SetScrollBarCtrl(NULL, TRUE);
		m_wndHScrollBar.ShowWindow(SW_HIDE);
		
	}
	else
	{
		m_wndHScrollBar.ShowWindow(SW_SHOW);
		SetScrollBarCtrl(&m_wndHScrollBar, TRUE);
	}

}

void CReportSampleView::OnUpdateOptionsAutomaticcolumnsizing(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsAutoColumnSizing());

}

void CReportSampleView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	GetReportCtrl().SetFocus();

}


void CReportSampleView::OnTestSmoothScroll()
{
	if (m_pWndSmoothScroll)
	{
		m_pWndSmoothScroll->ActivateFrame();
		return;
	}
	CCreateContext contextT;
	// if no context specified, generate one from the
	// currently selected client if possible.
	contextT.m_pLastView       = NULL;
	contextT.m_pCurrentFrame   = NULL;
	contextT.m_pNewDocTemplate = NULL;
	contextT.m_pCurrentDoc     = NULL;
	contextT.m_pNewViewClass   = RUNTIME_CLASS(CSmoothScrollView);


	m_pWndSmoothScroll = new CSmoothScrollFrame(this);

	DWORD dwStyle = WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE;

	m_pWndSmoothScroll->LoadFrame(IDR_SMOOTHSCROLL, dwStyle, 0, &contextT);
	m_pWndSmoothScroll->InitialUpdateFrame(NULL, FALSE);

	m_pWndSmoothScroll->ShowWindow(SW_SHOW);
}


void CReportSampleView::OnTestTasklist()
{
	if (m_pTaskFrame)
	{
		m_pTaskFrame->ActivateFrame();
		return;
	}
	CCreateContext contextT;
	// if no context specified, generate one from the
	// currently selected client if possible.
	contextT.m_pLastView       = NULL;
	contextT.m_pCurrentFrame   = NULL;
	contextT.m_pNewDocTemplate = NULL;
	contextT.m_pCurrentDoc     = NULL;
	contextT.m_pNewViewClass   = RUNTIME_CLASS(CTaskListView);


	m_pTaskFrame = new CTaskListFrame(this);

	DWORD dwStyle = WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE;

	m_pTaskFrame->LoadFrame(IDR_TASKLIST, dwStyle, 0, &contextT);
	m_pTaskFrame->InitialUpdateFrame(NULL, FALSE);

	m_pTaskFrame->ShowWindow(SW_SHOW);
}


void CReportSampleView::OnTestMerge()
{
	if (m_pWndMerge)
	{
		m_pWndMerge->ActivateFrame();
	}
	else
	{
		CCreateContext context;
		context.m_pLastView       = NULL;
		context.m_pCurrentFrame   = NULL;
		context.m_pNewDocTemplate = NULL;
		context.m_pCurrentDoc     = NULL;
		context.m_pNewViewClass   = RUNTIME_CLASS(CMergeView);

		m_pWndMerge = new CMergeFrame(this);
		m_pWndMerge->LoadFrame(IDR_MERGE, WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE, 0, &context);
		m_pWndMerge->InitialUpdateFrame(NULL, FALSE);
		m_pWndMerge->ShowWindow(SW_SHOW);
	}
}

void CReportSampleView::OnTestSelection()
{
	if (m_pWndSelection)
	{
		m_pWndSelection->ActivateFrame();
	}
	else
	{
		CCreateContext context;
		context.m_pLastView       = NULL;
		context.m_pCurrentFrame   = NULL;
		context.m_pNewDocTemplate = NULL;
		context.m_pCurrentDoc     = NULL;
		context.m_pNewViewClass   = RUNTIME_CLASS(CSelectionView);

		m_pWndSelection = new CSelectionFrame(this);
		m_pWndSelection->LoadFrame(IDR_TASKLIST, WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE, 0, &context);
		m_pWndSelection->InitialUpdateFrame(NULL, FALSE);
		m_pWndSelection->ShowWindow(SW_SHOW);
	}
}


void CReportSampleView::OnTestProperties()
{
	if (m_pPropertiesFrame)
	{
		m_pPropertiesFrame->ActivateFrame();
		return;
	}
	CCreateContext contextT;
	// if no context specified, generate one from the
	// currently selected client if possible.
	contextT.m_pLastView       = NULL;
	contextT.m_pCurrentFrame   = NULL;
	contextT.m_pNewDocTemplate = NULL;
	contextT.m_pCurrentDoc     = NULL;
	contextT.m_pNewViewClass   = RUNTIME_CLASS(CPropertiesView);


	m_pPropertiesFrame = new CPropertiesFrame(this);

	DWORD dwStyle = WS_OVERLAPPEDWINDOW|MFS_SYNCACTIVE;

	if (!m_pPropertiesFrame->Create(0, _T("Properties"), dwStyle, CRect(0, 0, 400, 350),
		this, 0, 0L, &contextT))
	{
		return ;   // will self destruct on failure normally
	}

	m_pPropertiesFrame->InitialUpdateFrame(NULL, FALSE);

	m_pPropertiesFrame->CenterWindow(this);
	m_pPropertiesFrame->ShowWindow(SW_SHOW);
}

void CReportSampleView::OnTestPerfomance()
{
	CPerfomanceTestDlg dlg;
	dlg.DoModal();
}


void CReportSampleView::OnReportcontrolMultilinesample()
{
	m_bMultilineSample = !m_bMultilineSample;

//	Custom implementation (from old version).	
//	For new versions of the ReportControl this feature is built-in.
//-----------------------------------------------------------------------------
//	if (m_bMultilineSample)
//	{
//		GetReportCtrl().SetPaintManager(new CReportMultilinePaintManager());
//		GetReportCtrl().EnableToolTips(FALSE);
//	}
//	else
//	{
//		GetReportCtrl().SetPaintManager(new CXTPReportPaintManager());
//		GetReportCtrl().EnableToolTips(TRUE);
//	}
//-----------------------------------------------------------------------------

	int nCount = GetReportCtrl().GetColumns()->GetCount();
	for( int i = 0; i < nCount; i++) 
	{
		CXTPReportColumn* pColumn = GetReportCtrl().GetColumns()->GetAt(i);
		if (pColumn) 
		{
			int nAlign = pColumn->GetAlignment();
			nAlign = m_bMultilineSample ? (nAlign | DT_WORDBREAK) : (nAlign & (~DT_WORDBREAK));
			pColumn->SetAlignment(nAlign);
		}
	}
	GetReportCtrl().GetPaintManager()->SetFixedRowHeight(!m_bMultilineSample);
	GetReportCtrl().GetPaintManager()->m_bUseColumnTextAlignment = TRUE;

	//
	GetReportCtrl().AdjustScrollBars();
}

void CReportSampleView::OnUpdateReportcontrolMultilinesample(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bMultilineSample);
}

// Set column header draw style.
// Following styles are available:
//   Shaded
//   Flat
//   Explorer
//   Office2003
//   Office2007
void CReportSampleView::OnColumnStyle(UINT nID) 
{
	GetReportCtrl().GetPaintManager()->SetColumnStyle(XTPReportColumnStyle(nID - ID_COLUMNSTYLE_SHADED));
	GetReportCtrl().RedrawControl();
}

void CReportSampleView::OnUpdateColumnStyle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetPaintManager()->GetColumnStyle() == XTPReportColumnStyle(pCmdUI->m_nID - ID_COLUMNSTYLE_SHADED)? TRUE: FALSE);
}

void CReportSampleView::OnReportBeforePaste(NMHDR * pNotifyStruct, LRESULT * result)
{
	*result = 1;//this result prevent report changes
	//*result = 0; //this result allows to change Report

	ASSERT(pNotifyStruct);

	XTP_NM_REPORT_BEFORE_COPYPASTE* pnmCopyPaste = (XTP_NM_REPORT_BEFORE_COPYPASTE*)pNotifyStruct;
	ASSERT(pnmCopyPaste);
	//
	CMessageRecord* pRecord = (CMessageRecord* ) *pnmCopyPaste->ppRecord;
	
	CXTPReportColumns* pColumns = GetReportCtrl().GetColumns();
	if (pColumns == NULL) 
		return;

	const int nColumnCount = pColumns->GetVisibleColumnsCount();
	for (int nCol = 0; nCol < nColumnCount; nCol++)
	{
		CXTPReportColumn* pColumn = pColumns->GetVisibleAt(nCol);
		CXTPReportRecordItem* pItem = pRecord->GetItem(pColumn);
		if (pItem == NULL)
			continue;

//MD - test how to change text in already copied internal report row
		CString strItem = pItem->GetCaption(pColumn);
//		strItem += "ABC";//UNCOMMENT TO TRY
		pItem->SetCaption(strItem);
//MD - test passed if Paste going outside (like copy from Excel)
	}
	*result = 0; //this result allows to change Report
}

void CReportSampleView::OnReportBeforePasteFromText(NMHDR * pNotifyStruct, LRESULT *result)
{
	*result = 1;//this result prevent report changes
	//*result = 0; //this result allows to change Report
	ASSERT(pNotifyStruct);
	
	XTP_NM_REPORT_BEFORE_COPYPASTE* pnmCopyPaste = (XTP_NM_REPORT_BEFORE_COPYPASTE*)pNotifyStruct; 
	
	if(!pnmCopyPaste || !pnmCopyPaste->ppRecord || !pnmCopyPaste->parStrings) 
	{
		ASSERT(FALSE);
		return;		
	}

	CMessageRecord* pRecord = new CMessageRecord();
	if (pRecord == NULL) 
		return;
	*pnmCopyPaste->ppRecord = pRecord;

	CXTPReportColumns* pColumns = GetReportCtrl().GetColumns();
	if (pColumns == NULL) 
	{
		return;
	}

	int nDataCount = (int)pnmCopyPaste->parStrings->GetSize();

	const int nColumnCount = pColumns->GetVisibleColumnsCount();
	for (int nCol = 0; nCol < nColumnCount; nCol++)
	{
		CXTPReportColumn* pColumn = pColumns->GetVisibleAt(nCol);
		CXTPReportRecordItem* pItem = pRecord->GetItem(pColumn);
		if (pItem == NULL)
			continue;

		if (nCol < nDataCount) 
		{
			CString strItem = pnmCopyPaste->parStrings->GetAt(nCol);
//MD - test
//			strItem += "-123"; //UNCOMMENT TO TRY
//MD - test passed if Paste going outside (like copy from Excel)
			pItem->SetCaption(strItem);
		}
	}
	*result = 0; //this result allows to change Report
}

void CReportSampleView::OnOptionsFreezecolumns0() 
{
	GetReportCtrl().SetFreezeColumnsCount(0);
	GetReportCtrl().RedrawControl();
}

void CReportSampleView::OnUpdateOptionsFreezecolumns0(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetFreezeColumnsCount() == 0 ? 1 : 0);
}

void CReportSampleView::OnOptionsFreezecolumns1() 
{
	GetReportCtrl().SetFreezeColumnsCount(1);	
	GetReportCtrl().RedrawControl();
}

void CReportSampleView::OnUpdateOptionsFreezecolumns1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetFreezeColumnsCount() == 1 ? 1 : 0);	
}

void CReportSampleView::OnOptionsFreezecolumns2() 
{
	GetReportCtrl().SetFreezeColumnsCount(2);
	GetReportCtrl().RedrawControl();
}

void CReportSampleView::OnUpdateOptionsFreezecolumns2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetFreezeColumnsCount() == 2 ? 1 : 0);	
}

void CReportSampleView::OnOptionsFreezecolumns3() 
{
	GetReportCtrl().SetFreezeColumnsCount(3);
	GetReportCtrl().RedrawControl();
}

void CReportSampleView::OnUpdateOptionsFreezecolumns3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetFreezeColumnsCount() == 3 ? 1 : 0);
}


void CReportSampleView::OnReportcontrolRighttoleft() 
{
	GetReportCtrl().SetLayoutRTL(GetReportCtrl().GetExStyle() & WS_EX_LAYOUTRTL ? FALSE : TRUE);
	
}

void CReportSampleView::OnUpdateReportcontrolRighttoleft(CCmdUI* pCmdUI) 
{
	if (!XTPSystemVersion()->IsLayoutRTLSupported())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->SetCheck(GetReportCtrl().GetExStyle() & WS_EX_LAYOUTRTL ? TRUE : FALSE);
	}	
}

void CReportSampleView::OnOptionsFreezecolumnsDivider1() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle &= ~(xtpReportFreezeColsDividerBold | xtpReportFreezeColsDividerThin);
	nStyle |= xtpReportFreezeColsDividerThin;
	
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();	
}

void CReportSampleView::OnOptionsFreezecolumnsDivider2() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle &= ~(xtpReportFreezeColsDividerBold | xtpReportFreezeColsDividerThin);
	nStyle |= xtpReportFreezeColsDividerBold;
	
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();	
	
}

void CReportSampleView::OnUpdateOptionsFreezecolumnsDivider1(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & xtpReportFreezeColsDividerThin) != 0);
}

void CReportSampleView::OnUpdateOptionsFreezecolumnsDivider2(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & xtpReportFreezeColsDividerBold) != 0);
}

void CReportSampleView::OnOptionsFreezecolumnsDividerHeader() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle ^= xtpReportFreezeColsDividerHeader;
		
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();		
}

void CReportSampleView::OnUpdateOptionsFreezecolumnsDividerHeader(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & xtpReportFreezeColsDividerHeader) != 0);
}

void CReportSampleView::OnOptionsFreezecolumnsDividerNone() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle = (nStyle & (xtpReportFreezeColsDividerHeader));
		
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();
}

void CReportSampleView::OnUpdateOptionsFreezecolumnsDividerNone(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & ~xtpReportFreezeColsDividerHeader) == 0);
}

void CReportSampleView::OnOptionsFreezecolumnsDividerShade() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle ^= xtpReportFreezeColsDividerShade;
		
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();	
}

void CReportSampleView::OnUpdateOptionsFreezecolumnsDividerShade(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & xtpReportFreezeColsDividerShade) != 0);
	
}

void CReportSampleView::OnTestHeaderFooter()
{
	if (m_pHeaderFooterFrame)
	{
		m_pHeaderFooterFrame->ActivateFrame();
		return;
	}
	CCreateContext contextT;
	// if no context specified, generate one from the
	// currently selected client if possible.
	contextT.m_pLastView       = NULL;
	contextT.m_pCurrentFrame   = NULL;
	contextT.m_pNewDocTemplate = NULL;
	contextT.m_pCurrentDoc     = NULL;
	contextT.m_pNewViewClass   = RUNTIME_CLASS(CHeaderFooterView);


	m_pHeaderFooterFrame = new CHeaderFooterFrame(this);

	DWORD dwStyle = WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE;

	m_pHeaderFooterFrame->LoadFrame(IDR_HEADERFOOTER, dwStyle, 0, &contextT);
	m_pHeaderFooterFrame->InitialUpdateFrame(NULL, FALSE);

	m_pHeaderFooterFrame->ShowWindow(SW_SHOW);
}

BOOL CReportSampleView::OnFindInReport()
{
	//CString sIn(_T("James HOWLETT"));
	//CString sIn(_T("james howlett"));
	//CString sIn(_T("James "));
	CString sIn(_T("ames "));
	//CString sIn(_T("JaMes hOWlETT"));
	CString sOut;
	int iR, iC;
	CXTPReportControl& wndReport = GetReportCtrl();
	int iCols = wndReport.GetColumns()->GetCount();
	int iRows = wndReport.GetRows()->GetCount();
	iR = iRows - 1;
	iC = iCols - 1;
	CXTPReportRecordItem* 
	pItem = wndReport.GetRecords()->FindRecordItem(0, iRows - 1, 0, iCols - 1, 0, 0, 
		sIn, 
		//xtpReportTextSearchExactPhrase 
		//| xtpReportTextSearchMatchCase
		//| 
		xtpReportTextSearchExactStart
		);// was == 3 - now 11

	if (pItem)
	{
		AfxMessageBox(sIn + _T(" <- xtpReportTextSearchExactStart -> ") + pItem->GetCaption(NULL));
		pItem->SetTextColor(RGB(255,0,0));
	}
	else
		AfxMessageBox(sIn + _T(" <- xtpReportTextSearchExactStart -> Not Found for ames"));

	sIn = _T("James ");
	pItem = wndReport.GetRows()->FindRecordItemByRows(0, iRows - 1, 0, iCols - 1, 0, 0, 
		sIn, 
		//xtpReportTextSearchExactPhrase 
		//| xtpReportTextSearchMatchCase
		//| 
		xtpReportTextSearchExactStart
		);// was == 3 - now 11

	if (pItem)
	{
		AfxMessageBox(sIn + _T(" <- FindRecordItemByRows|xtpReportTextSearchExactStart -> ") + pItem->GetCaption(NULL));
		pItem->SetTextColor(RGB(255,0,0));
	}
	else
		AfxMessageBox(sIn + _T(" <- FindRecordItemByRows|xtpReportTextSearchExactStart -> Not Found for James"));

	pItem = wndReport.GetRecords()->FindRecordItem(0, iRows - 1, 0, iCols - 1, 0, 0, 
		sIn, 
		//xtpReportTextSearchExactPhrase 
		//| xtpReportTextSearchMatchCase
		//| 
		xtpReportTextSearchExactStart
		);// was == 3 - now 11

	if (pItem)
	{
		AfxMessageBox(sIn + _T(" <- ExactStart -> ") + pItem->GetCaption(NULL));
		pItem->SetTextColor(RGB(255,0,0));
	}
	else
		AfxMessageBox(sIn + _T(" <- ExactStart -> Not Found for How"));

	pItem = wndReport.GetRecords()->FindRecordItem(0, iRows - 1, 0, iCols - 1, 0, 0, 
		sIn, xtpReportTextSearchMatchCase); // == 2

	if (pItem)
	{
		AfxMessageBox(sIn + _T(" <- M -> ") + pItem->GetCaption(NULL));
		pItem->SetTextColor(RGB(255,0,0));
	}
	else
		AfxMessageBox(sIn + _T(" <- M -> Not Found"));

	pItem =  wndReport.GetRecords()->FindRecordItem(0, iRows - 1, 0, iCols - 1, 0, 0, 
		sIn, xtpReportTextSearchExactPhrase); // == 1

	if (pItem)
	{
		iR = pItem->GetRecord()->GetIndex();
		iC = pItem->GetIndex();
		sOut.Format(_T("R=%d C=%d %s"), iR, iC, pItem->GetCaption(NULL));
		AfxMessageBox(sIn + _T(" <- E -> ") + sOut);
		pItem->SetTextColor(RGB(255,0,0));
	}
	else
		AfxMessageBox(sIn + _T(" <- E -> Not Found"));

	pItem = wndReport.GetRecords()->FindRecordItem(0, iRows - 1, 0, iCols - 1, iR, iC, 
		sIn, 0);

	if (pItem)
	{
		iR = pItem->GetRecord()->GetIndex();
		iC = pItem->GetIndex();
		sOut.Format(_T("R=%d C=%d %s"), iR, iC, pItem->GetCaption(NULL));
		AfxMessageBox(sIn + _T(" <- S (FindNext)-> ") + sOut);
		pItem->SetTextColor(RGB(255,0,0));
	}
	else
		AfxMessageBox(sIn + _T(" <- S (FindNext)-> Not Found"));

	pItem = wndReport.GetRecords()->FindRecordItem(0, iRows - 1, 0, iCols - 1, iR, iC, 
		sIn, xtpReportTextSearchBackward);

	if (pItem)
	{
		iR = pItem->GetRecord()->GetIndex();
		iC = pItem->GetIndex();
		sOut.Format(_T("R=%d C=%d %s"), iR, iC, pItem->GetCaption(NULL));
		AfxMessageBox(sIn + _T(" <- Backward (FindNext)-> ") + sOut);
		pItem->SetTextColor(RGB(255,0,0));
	}
	else
		AfxMessageBox(sIn + _T(" <- Backward (FindNext)-> Not Found"));

	return TRUE;
}
void CReportSampleView::OnReportcontrolDevtest()
{
	OnFindInReport();
}

void CReportSampleView::OnFilePrintPreview()
{
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
	
	if ( !DoPrintPreview( XTP_IDD_PREVIEW_DIALOGBAR, this,
		RUNTIME_CLASS( CXTPPreviewView ), pState ))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		TRACE0( "Error: DoPrintPreview failed.\n" );
		AfxMessageBox( AFX_IDP_COMMAND_FAILURE );
		delete pState;      // preview failed to initialize, delete State now
		
	}
}

void CReportSampleView::OnReportWYSIWYG()
{

	CXTPReportControl& wndReport = GetReportCtrl();

	BOOL bWYSIWYG = !wndReport.GetPaintManager()->IsColumnWidthWYSIWYG();
	wndReport.GetPaintManager()->SetColumnWidthWYSIWYG(bWYSIWYG);

	m_pPrintOptions->m_bRepeatFooterRows = TRUE;
	m_pPrintOptions->m_bRepeatHeaderRows = TRUE;

	wndReport.RedrawControl(); // Make WYSIWYG marker visible
}

void CReportSampleView::OnUpdateReportWYSIWYG(CCmdUI *pCmdUI)
{
	CXTPReportControl &wndReport = GetReportCtrl();
	pCmdUI->SetCheck(wndReport.GetPaintManager()->IsColumnWidthWYSIWYG());
}

void CReportSampleView::OnReportIconview()
{
	CXTPReportControl& wndReport = GetReportCtrl();

	wndReport.AssignIconViewPropNumAndIconNum(3, 3, TRUE, 25);

	wndReport.SetIconView(!wndReport.IsIconView());
}

void CReportSampleView::OnUpdateReportIconview(CCmdUI *pCmdUI)
{
	CXTPReportControl& wndReport = GetReportCtrl();
	pCmdUI->SetCheck(wndReport.IsIconView());
}


/////////////////////////////////////////////////////////////////////////////
// Report behavior
/////////////////////////////////////////////////////////////////////////////

#if _XTPLIB_VERSION_PREFIX >= 1511

void CReportSampleView::OnBehaviorCodejockDefault()
{
	m_behavior = xtpReportBehaviorCodejockDefault;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorCodejockDefault);
}

void CReportSampleView::OnBehaviorCodejock1502()
{
	m_behavior = xtpReportBehaviorCodejock1502;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorCodejock1502);
}

void CReportSampleView::OnBehaviorCodejock1501()
{
	m_behavior = xtpReportBehaviorCodejock1501;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorCodejock1501);
}

void CReportSampleView::OnBehaviorCodejock1342()
{
	m_behavior = xtpReportBehaviorCodejock1342;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorCodejock1342);
}

void CReportSampleView::OnBehaviorOutlook2003()
{
	m_behavior = xtpReportBehaviorOutlook2003;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorOutlook2003);
}

void CReportSampleView::OnBehaviorOutlook2007()
{
	m_behavior = xtpReportBehaviorOutlook2007;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorOutlook2007);
}

void CReportSampleView::OnBehaviorOutlook2010()
{
	m_behavior = xtpReportBehaviorOutlook2010;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorOutlook2010);
}

void CReportSampleView::OnBehaviorExcel2003()
{
	m_behavior = xtpReportBehaviorExcel2003;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorExcel2003);
}

void CReportSampleView::OnBehaviorExcel2007()
{
	m_behavior = xtpReportBehaviorExcel2007;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorExcel2007);
}

void CReportSampleView::OnBehaviorExcel2010()
{
	m_behavior = xtpReportBehaviorExcel2010;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorExcel2010);
}

void CReportSampleView::OnBehaviorCustom()
{
	m_behavior = 100;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorOutlook2003);
#if _XTPLIB_VERSION_PREFIX >= 1520
	GetReportCtrl().GetBehavior()->Row->MouseUp->Right->None->bFocusRowTemporarily = FALSE;
#else
	GetReportCtrl().GetBehavior()->Row->MouseUp->Right->bFocusRowTemporarily = FALSE;
#endif
}


void CReportSampleView::OnUpdateBehaviorCodejockDefault(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorCodejockDefault == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorCodejock1502(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorCodejock1502 == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorCodejock1501(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorCodejock1501 == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorCodejock1342(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorCodejock1342 == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorOutlook2003(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorOutlook2003 == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorOutlook2007(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorOutlook2007 == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorOutlook2010(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorOutlook2010 == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorExcel2003(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorExcel2003 == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorExcel2007(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorExcel2007 == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorExcel2010(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorExcel2010 == m_behavior ? 1 : 0);
}

void CReportSampleView::OnUpdateBehaviorCustom(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(100 == m_behavior ? 1 : 0);
}

#endif


/////////////////////////////////////////////////////////////////////////////

void CReportSampleView::OnReportLockExpand()
{
#if _XTPLIB_VERSION_PREFIX >= 1511
	GetReportCtrl().LockExpand(!GetReportCtrl().IsLockExpand());
	GetReportCtrl().RedrawControl();
#endif
}

void CReportSampleView::OnUpdateReportLockExpand(CCmdUI *pCmdUI)
{
#if _XTPLIB_VERSION_PREFIX >= 1511
	pCmdUI->SetCheck(GetReportCtrl().IsLockExpand() ? 1 : 0);
#else
	pCmdUI->Enable(FALSE); // Not supported
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Watermark
/////////////////////////////////////////////////////////////////////////////

void CReportSampleView::OnReportWatermark()
{
	CXTPReportControl &wndReport = GetReportCtrl();

	m_bWatermark = !m_bWatermark;

	if (m_bWatermark)
	{
		CBitmap bmpWatermark;

		if (bmpWatermark.LoadBitmap(IDB_CODEJOCKGEAR))
		{
			wndReport.SetWatermarkBitmap(bmpWatermark, 64);
			wndReport.SetWatermarkAlignment(xtpReportWatermarkCenter | xtpReportWatermarkVCenter);
			wndReport.GetPaintManager()->m_bPrintWatermark = TRUE;
		}
	}
	else
	{
		wndReport.SetWatermarkBitmap(HBITMAP(NULL), 0);
		wndReport.GetPaintManager()->m_bPrintWatermark = FALSE;
	}

	wndReport.RedrawControl();
}

void CReportSampleView::OnUpdateReportWatermark(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m_bWatermark ? 1 : 0);
}

/////////////////////////////////////////////////////////////////////////////
// Double buffering
/////////////////////////////////////////////////////////////////////////////

void CReportSampleView::OnReportDoubleBuffering()
{
#if _XTPLIB_VERSION_PREFIX >= 1511
	CXTPReportControl &wndReport = GetReportCtrl();
	wndReport.EnableDoubleBuffering(!wndReport.IsDoubleBuffering());
	wndReport.RedrawControl();
#endif
}

void CReportSampleView::OnUpdateReportDoubleBuffering(CCmdUI *pCmdUI)
{
#if _XTPLIB_VERSION_PREFIX >= 1511
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(GetReportCtrl().IsDoubleBuffering() ? 1 : 0);
#else
	// Not supported
	pCmdUI->Enable(FALSE); // Can not be changed
	pCmdUI->SetCheck(1);   // Always on
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Scrolling (Horizontal)
/////////////////////////////////////////////////////////////////////////////

void CReportSampleView::OnScrollingHorizontalBlockCount()
{
#if _XTPLIB_VERSION_PREFIX >= 1521
	GetReportCtrl().SetScrollMode(xtpReportOrientationHorizontal, xtpReportScrollModeBlockCount);
#endif
}

void CReportSampleView::OnScrollingHorizontalBlockSize()
{
#if _XTPLIB_VERSION_PREFIX >= 1521
	GetReportCtrl().SetScrollMode(xtpReportOrientationHorizontal, xtpReportScrollModeBlockSize);
#endif
}

void CReportSampleView::OnScrollingHorizontalSmooth()
{
#if _XTPLIB_VERSION_PREFIX >= 1511
	GetReportCtrl().SetScrollMode(xtpReportOrientationHorizontal, xtpReportScrollModeSmooth);
#endif
}

void CReportSampleView::OnUpdateScrollingHorizontalBlockCount(CCmdUI *pCmdUI)
{
#if _XTPLIB_VERSION_PREFIX >= 1521
	CXTPReportControl &wndReport = GetReportCtrl();

	BOOL bSmooth = xtpReportScrollModeBlockCount == wndReport.GetScrollMode(xtpReportOrientationHorizontal);
	
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(bSmooth ? 1 : 0);
#else
	// Not supported
	pCmdUI->Enable(FALSE);
	pCmdUI->SetCheck(0);
#endif
}

void CReportSampleView::OnUpdateScrollingHorizontalBlockSize(CCmdUI *pCmdUI)
{
#if _XTPLIB_VERSION_PREFIX >= 1521
	CXTPReportControl &wndReport = GetReportCtrl();

	BOOL bSmooth = xtpReportScrollModeBlockSize == wndReport.GetScrollMode(xtpReportOrientationHorizontal);
	
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(bSmooth ? 1 : 0);
#else
	// Not supported
	pCmdUI->Enable(FALSE);
	pCmdUI->SetCheck(0);
#endif
}

void CReportSampleView::OnUpdateScrollingHorizontalSmooth(CCmdUI *pCmdUI)
{
#if _XTPLIB_VERSION_PREFIX >= 1511
	CXTPReportControl &wndReport = GetReportCtrl();

	BOOL bSmooth = xtpReportScrollModeSmooth == wndReport.GetScrollMode(xtpReportOrientationHorizontal);
	
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(bSmooth ? 1 : 0);
#else
	// Not supported
	pCmdUI->Enable(FALSE);
	pCmdUI->SetCheck(0);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Scrolling (Vertical)
/////////////////////////////////////////////////////////////////////////////

void CReportSampleView::OnScrollingVerticalBlockCount()
{
#if _XTPLIB_VERSION_PREFIX >= 1521
	GetReportCtrl().SetScrollMode(xtpReportOrientationVertical, xtpReportScrollModeBlockCount);
#endif
}

void CReportSampleView::OnScrollingVerticalSmooth()
{
#if _XTPLIB_VERSION_PREFIX >= 1511
	GetReportCtrl().SetScrollMode(xtpReportOrientationVertical, xtpReportScrollModeSmooth);
#endif
}

void CReportSampleView::OnUpdateScrollingVerticalBlockCount(CCmdUI *pCmdUI)
{
#if _XTPLIB_VERSION_PREFIX >= 1521
	CXTPReportControl &wndReport = GetReportCtrl();

	BOOL bSmooth = xtpReportScrollModeBlockCount == wndReport.GetScrollMode(xtpReportOrientationVertical);
	
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(bSmooth ? 1 : 0);
#else
	// Not supported
	pCmdUI->Enable(FALSE);
	pCmdUI->SetCheck(0);
#endif
}

void CReportSampleView::OnUpdateScrollingVerticalSmooth(CCmdUI *pCmdUI)
{
#if _XTPLIB_VERSION_PREFIX >= 1511
	CXTPReportControl &wndReport = GetReportCtrl();

	BOOL bSmooth = xtpReportScrollModeSmooth == wndReport.GetScrollMode(xtpReportOrientationVertical);
	
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(bSmooth ? 1 : 0);
#else
	// Not supported
	pCmdUI->Enable(FALSE);
	pCmdUI->SetCheck(0);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Grid Color
/////////////////////////////////////////////////////////////////////////////

#if _XTPLIB_VERSION_PREFIX >= 1520

void CReportSampleView::OnGridColorRed() 
{
	m_wndReport.GetPaintManager()->SetGridColor(RGB(255,0,0));
	m_wndReport.RedrawControl();
}

void CReportSampleView::OnGridColorGreen() 
{
	m_wndReport.GetPaintManager()->SetGridColor(RGB(0,255,0));
	m_wndReport.RedrawControl();
}

void CReportSampleView::OnGridColorBlue() 
{
	m_wndReport.GetPaintManager()->SetGridColor(RGB(0,0,255));
	m_wndReport.RedrawControl();
}

void CReportSampleView::OnUpdateGridColorRed(CCmdUI *pCmdUI) 
{
	pCmdUI->SetCheck(RGB(255,0,0) == m_wndReport.GetPaintManager()->GetGridColor() ? 1 : 0);
}

void CReportSampleView::OnUpdateGridColorGreen(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(RGB(0,255,0) == m_wndReport.GetPaintManager()->GetGridColor() ? 1 : 0);
}

void CReportSampleView::OnUpdateGridColorBlue(CCmdUI *pCmdUI) 
{
	pCmdUI->SetCheck(RGB(0,0,255) == m_wndReport.GetPaintManager()->GetGridColor() ? 1 : 0);
}

#endif
