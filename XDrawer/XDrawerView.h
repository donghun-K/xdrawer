
// XDrawerView.h : CXDrawerView Ŭ������ �������̽�
//

#pragma once

class Figure;
class CXDrawerDoc;
class ModalDialog;


class CXDrawerView : public CView
{
protected: // serialization������ ��������ϴ�.
	CXDrawerView();
	DECLARE_DYNCREATE(CXDrawerView)

private:
	int whatToDraw;
	ModalDialog *pDlg;
// Ư���Դϴ�.
public:
	CXDrawerDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	Figure *currentFigure;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CXDrawerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnObjectBox();
	afx_msg void OnObjectLine();
	afx_msg void OnObjectCircle();
	afx_msg void OnObjectDiamond();
	afx_msg void OnObjectX();
	afx_msg void OnObjectBubble();
	afx_msg void OnModalDialog();
	afx_msg void OnModalessDialog();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
};

#ifndef _DEBUG  // XDrawerView.cpp�� ����� ����
inline CXDrawerDoc* CXDrawerView::GetDocument() const
   { return reinterpret_cast<CXDrawerDoc*>(m_pDocument); }
#endif

