#include "stdafx.h"
#include "resource.h"

#include "FigurePopup.h"


FigurePopup::FigurePopup(CXDrawerView *view, CString title, BOOL fillButtonFlag)
	: Popup(view, title)
{	
	popupPtr->AppendMenuW(MF_STRING, ID_DELETE_FIGURE, _T("�����"));
	popupPtr->AppendMenu(MF_STRING,ID_COPY_FIGURE, _T("�����ϱ�"));

	colorPopup = new CMenu();
	colorPopup->CreatePopupMenu();
	colorPopup->AppendMenu(MF_STRING, ID_BLACK_COLOR, _T("����"));
	colorPopup->AppendMenu(MF_STRING, ID_RED_COLOR, _T("����"));
	colorPopup->AppendMenu(MF_STRING, ID_GREEN_COLOR, _T("�ʷ�"));
	colorPopup->AppendMenu(MF_STRING, ID_BLUE_COLOR, _T("�Ķ�"));
	popupPtr->AppendMenu(MF_POPUP, (unsigned int)colorPopup->m_hMenu, _T("�� ���ϱ�"));
	if (fillButtonFlag == TRUE)
		popupPtr->AppendMenu(MF_STRING,ID_FILL_FIGURE, _T("ä���"));
}

FigurePopup::~FigurePopup()
{
	if (popupPtr != NULL) delete popupPtr;
	if (colorPopup != NULL) delete colorPopup;
}
