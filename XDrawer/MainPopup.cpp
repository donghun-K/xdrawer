#include "stdafx.h"
#include "resource.h"

#include "MainPopup.h"
#include "XDrawerView.h"


MainPopup::MainPopup(CXDrawerView *view, CString title)
{	
	viewPtr = view;
	popupPtr = new CMenu();
	popupPtr->CreatePopupMenu();
	popupPtr->AppendMenuW(MF_STRING, 0, title);
	popupPtr->AppendMenuW(MF_SEPARATOR);
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_X, _T("����"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_BUBBLE, _T("����"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_BOX, _T("�簢��"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_LINE, _T("��"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_CIRCLE, _T("��"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_DIAMOND, _T("���̾Ƹ��"));
}


MainPopup::~MainPopup()
{
	if (popupPtr != NULL) delete popupPtr;
}

void MainPopup::popup(int x, int y) {
	popupPtr->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, x, y, viewPtr, NULL);
}
