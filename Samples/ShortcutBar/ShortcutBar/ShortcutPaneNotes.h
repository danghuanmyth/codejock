// ShortcutPaneNotes.h: interface for the CShortcutPaneNotes class.
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

#if !defined(AFX_SHORTCUTPANENotes_H__03BA0B52_DDD8_4E32_BFBA_CC2F6B7CDCEB__INCLUDED_)
#define AFX_SHORTCUTPANENotes_H__03BA0B52_DDD8_4E32_BFBA_CC2F6B7CDCEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShortcutPaneNotes : public CXTPShortcutBarPane
{
public:
	CShortcutPaneNotes();
	virtual ~CShortcutPaneNotes();

	BOOL Create(LPCTSTR lpszCaption, CXTPShortcutBar* pParent);

	void SetFlatStyle(BOOL bFlatStyle);

protected:
	CXTPTreeCtrl m_wndTreeNotes;
	CImageList m_ilTreeIcons;
	
};

#endif // !defined(AFX_SHORTCUTPANENotes_H__03BA0B52_DDD8_4E32_BFBA_CC2F6B7CDCEB__INCLUDED_)
