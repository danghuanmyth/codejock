// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C0CFFA34_B1A8_4881_98E6_C6D688115E73__INCLUDED_)
#define AFX_STDAFX_H__C0CFFA34_B1A8_4881_98E6_C6D688115E73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#if _MSC_VER > 1200 //MFC 7.0 or later

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER              // Allow use of features specific to Windows 95 and Windows NT 4 or later.
#if _MSC_VER > 1500
#define WINVER 0x0500
#else
#define WINVER 0x0400       // Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif
#endif

#ifndef _WIN32_WINNT        // Allow use of features specific to Windows NT 4 or later.
#if _MSC_VER > 1500
#define _WIN32_WINNT 0x0500
#else
#define _WIN32_WINNT 0x0400     // Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif
#endif

#ifndef _WIN32_WINDOWS      // Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE           // Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0400    // Change this to the appropriate value to target IE 5.0 or later.
#endif

#endif//_MSC_VER > 1200

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT




#include <XTToolkitPro.h>   // Codejock Software Components
#include <AboutDlg.h>       // Sample About Dialog

#include "ReportControl\XTPReportADO.h"
#include "ReportControl\XTPReportDataManager.h"
using namespace XTPREPORTADODB;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C0CFFA34_B1A8_4881_98E6_C6D688115E73__INCLUDED_)
