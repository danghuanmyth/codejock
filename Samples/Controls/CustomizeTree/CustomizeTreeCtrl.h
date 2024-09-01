// CustomizeTreeCtrl.h: interface for the CCustomizeTreeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMIZETREECTRL_H__3A7ACA47_586C_4AF0_ACB5_AF785AE1B360__INCLUDED_)
#define AFX_CUSTOMIZETREECTRL_H__3A7ACA47_586C_4AF0_ACB5_AF785AE1B360__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCustomizeTreeCtrl : public CXTPCoreTreeControl  
{
public:
	CCustomizeTreeCtrl();
	virtual ~CCustomizeTreeCtrl();

protected:
	virtual void StartDragItem(CXTPCoreTreeItem* pItem);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);

	int GetItemLevel(CXTPCoreTreeItem* pItem) const;

public:
	BOOL m_bItemsTree;

};

#endif // !defined(AFX_CUSTOMIZETREECTRL_H__3A7ACA47_586C_4AF0_ACB5_AF785AE1B360__INCLUDED_)
