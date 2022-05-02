
// XDrawerView.cpp : CXDrawerView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "XDrawer.h"
#endif

#include "XDrawerDoc.h"
#include "XDrawerView.h"
#include "Box.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXDrawerView

IMPLEMENT_DYNCREATE(CXDrawerView, CView)

BEGIN_MESSAGE_MAP(CXDrawerView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CXDrawerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CXDrawerView ����/�Ҹ�

CXDrawerView::CXDrawerView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	currentBox = NULL;	
}

CXDrawerView::~CXDrawerView()
{
}

BOOL CXDrawerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CXDrawerView �׸���

void CXDrawerView::OnDraw(CDC* pDC)
{
	CXDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	/*
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Ellipse(100, 100, 200, 200);

	CPen pen(PS_SOLID, 3, RGB(0, 0, 255));
	CPen *oldPen = pDC->SelectObject(&pen);	
	
	pDC->Rectangle(100, 100, 200, 200);

	pDC->SelectObject(oldPen);

	pDC->MoveTo(300, 300);
	pDC->LineTo(100, 100);

	CPen pen2(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(&pen2);
	pDC->MoveTo(300, 300);
	pDC->LineTo(500, 500);

	CRect rect(50, 50, 100, 100);
	CBrush br(RGB(255, 0, 0));
	pDC->FillRect(&rect, &br);
	*/

	for(int i=0; i<pDoc->boxCount(); i++)
	{
		pDoc->getBox(i)->draw(pDC);
	}


}


// CXDrawerView �μ�


void CXDrawerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CXDrawerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CXDrawerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CXDrawerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CXDrawerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CXDrawerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CXDrawerView ����

#ifdef _DEBUG
void CXDrawerView::AssertValid() const
{
	CView::AssertValid();
}

void CXDrawerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXDrawerDoc* CXDrawerView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXDrawerDoc)));
	return (CXDrawerDoc*)m_pDocument;
}
#endif //_DEBUG


// CXDrawerView �޽��� ó����


void CXDrawerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	currentBox = new Box(point.x, point.y);
	CDC *pDC = GetDC();
	currentBox->draw(pDC);
	
	CView::OnLButtonDown(nFlags, point);
}


void CXDrawerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(currentBox != NULL)
	{
		CDC *pDC = GetDC();
		CGdiObject *oldBrush = pDC->SelectStockObject(NULL_BRUSH);

		currentBox->setXY2(point.x, point.y);
		currentBox->draw(pDC);

		pDC->SelectObject(oldBrush);

		CXDrawerDoc *pDoc = GetDocument();
		pDoc->add(currentBox);
	}
	currentBox = NULL;

	CView::OnLButtonUp(nFlags, point);
}


void CXDrawerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(currentBox != NULL)
	{
		CDC *pDC = GetDC();
		int oldMode = pDC->SetROP2(R2_NOTXORPEN);
		CGdiObject *oldBrush = pDC->SelectStockObject(NULL_BRUSH);

		currentBox->draw(pDC);
		currentBox->setXY2(point.x, point.y);
		currentBox->draw(pDC);

		pDC->SelectObject(oldBrush);
		pDC->SetROP2(oldMode);

	}

	CView::OnMouseMove(nFlags, point);
}
