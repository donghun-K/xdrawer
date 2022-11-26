#include "stdafx.h"
#include "resource.h"

#include "MainPopup.h"


MainPopup::MainPopup(CXDrawerView *view, CString title)
	: Popup(view, title)
{	
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_X, _T("����"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_BUBBLE, _T("����"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_BOX, _T("�簢��"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_LINE, _T("��"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_CIRCLE, _T("��"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_DIAMOND, _T("���̾Ƹ��"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_KITE1, _T("��1"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_KITE2, _T("��2"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_KITE3, _T("��3"));
	popupPtr->AppendMenuW(MF_STRING, ID_OBJECT_UFO, _T("UFO"));
}


MainPopup::~MainPopup()
{
	if (popupPtr != NULL) delete popupPtr;
}
