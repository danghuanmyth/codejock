// CustomizeTreeCtrl.cpp: implementation of the CCustomizeTreeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "customizetree.h"
#include "CustomizeTreeCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomizeTreeCtrl::CCustomizeTreeCtrl()
{
	m_bItemsTree = FALSE;
}

CCustomizeTreeCtrl::~CCustomizeTreeCtrl()
{

}

int CCustomizeTreeCtrl::GetItemLevel(CXTPCoreTreeItem* pItem) const
{
	int nLevel = 0;
	while (pItem->GetParentItem() != NULL)
	{
		nLevel++;
		pItem = pItem->GetParentItem();
	}
	
	return nLevel;	
}

void CCustomizeTreeCtrl::StartDragItem(CXTPCoreTreeItem* pItem)
{
	ASSERT(pItem);
	
	if (!m_bItemsTree)
	{
		if (GetItemLevel(pItem) != 2)
			return;
	}

	if (!pItem->IsEnabled())
		return;

	DragItem(pItem, m_bItemsTree ? DROPEFFECT_COPY : DROPEFFECT_MOVE | DROPEFFECT_COPY);
}

BOOL CCustomizeTreeCtrl::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	return CXTPCoreTreeControl::OnDrop(pDataObject, dropEffect, point);
}


DROPEFFECT CCustomizeTreeCtrl::OnDragOver(COleDataObject* /*pDataObject*/, DWORD dwKeyState, CPoint point)
{
	if (m_bItemsTree)
		return DROPEFFECT_NONE;


	CXTPCoreTreeItem* pDragOverItem = HitTest(point);
	if (!pDragOverItem)
	{
		SetDragOverItem(NULL);

		return DROPEFFECT_NONE;
	}

	int nLevel = GetItemLevel(pDragOverItem);

	if (nLevel == 2)		
	{
		CRect rcItem = pDragOverItem->GetScreenRect();

		XTPCoreTreeDropPosition nDropPosition = rcItem.CenterPoint().y > point.y ? xtpCoreTreeDropBefore : xtpCoreTreeDropAfter;		

		SetDragOverItem(pDragOverItem, nDropPosition);
	}
	else if (nLevel == 1)
	{
		SetDragOverItem(pDragOverItem, xtpCoreTreeDropChild);
	}
	else
	{
		SetDragOverItem(NULL);
	}

	DROPEFFECT dropEffect = DROPEFFECT_MOVE;

	if ((dwKeyState & MK_CONTROL) == MK_CONTROL)
	{
		dropEffect = DROPEFFECT_COPY;
	}	
	
	return m_pDragOverItem != NULL ? dropEffect : DROPEFFECT_NONE;
}
