#if !defined(AFX_BarAndLineView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
#define AFX_BarAndLineView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BarAndLineView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBarAndLineView form view

#include "BaseView.h"

class CBarAndLineView : public CBaseView
{
public:
	CBarAndLineView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBarAndLineView)

// Form Data
public:
	//{{AFX_DATA(CBarAndLineView)
	enum { IDD = IDD_VIEW_BAR_AND_LINE };
	//CXTPComboBox	m_cboPosition;
	//CXTPButton	m_chkShowLabels;
	BOOL	m_bShowLabels;
	BOOL	m_bRotated;
	//}}AFX_DATA

	void CreateChart();

// Attributes
public:
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBarAndLineView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBarAndLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CBarAndLineView)
	afx_msg void OnCheckShowLabels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckRotated();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BarAndLineView_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
