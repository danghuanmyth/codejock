// CustomizeTree.h : main header file for the CUSTOMIZETREE application
//

#if !defined(AFX_CUSTOMIZETREE_H__6CD95356_512F_47D0_89BA_E7BC643DBEFA__INCLUDED_)
#define AFX_CUSTOMIZETREE_H__6CD95356_512F_47D0_89BA_E7BC643DBEFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCustomizeTreeApp:
// See CustomizeTree.cpp for the implementation of this class
//

class CCustomizeTreeApp : public CWinApp
{
public:
	CCustomizeTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCustomizeTreeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZETREE_H__6CD95356_512F_47D0_89BA_E7BC643DBEFA__INCLUDED_)
