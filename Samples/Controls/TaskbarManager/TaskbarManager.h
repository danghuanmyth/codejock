// TaskbarManager.h : main header file for the TASKBARMANAGER application
//

#if !defined(AFX_TASKBARMANAGER_H__EC1EAF35_E013_4576_ADBE_3A5F6C7623A6__INCLUDED_)
#define AFX_TASKBARMANAGER_H__EC1EAF35_E013_4576_ADBE_3A5F6C7623A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTaskbarManagerApp:
// See TaskbarManager.cpp for the implementation of this class
//

class CTaskbarManagerApp : public CWinApp
{
public:
	CTaskbarManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaskbarManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTaskbarManagerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKBARMANAGER_H__EC1EAF35_E013_4576_ADBE_3A5F6C7623A6__INCLUDED_)
