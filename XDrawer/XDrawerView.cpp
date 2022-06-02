
// XDrawerView.cpp : CXDrawerView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "XDrawer.h"
#endif

#include "ModalDialog.h"
#include "MainPopup.h"
#include "FigurePopup.h"

#include "XDrawerDoc.h"
#include "XDrawerView.h"

#include "X.h"
#include "Bubble.h"
#include "Box.h"
#include "Line.h"
#include "Circle.h"
#include "Diamond.h"
#include "Figure.h"
#include "FigureList.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DRAW_X			(1)
#define DRAW_BUBBLE		(2)
#define DRAW_BOX		(3)
#define DRAW_LINE		(4)
#define DRAW_CIRCLE		(5)
#define DRAW_DIAMOND	(6)

// CXDrawerView

IMPLEMENT_DYNCREATE(CXDrawerView, CView)

BEGIN_MESSAGE_MAP(CXDrawerView, CView)
	ON_COMMAND(ID_DELETE_FIGURE, &CXDrawerView::OnDeleteFigure)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CXDrawerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_OBJECT_BOX, &CXDrawerView::OnObjectBox)
	ON_COMMAND(ID_OBJECT_LINE, &CXDrawerView::OnObjectLine)
	ON_COMMAND(ID_OBJECT_CIRCLE, &CXDrawerView::OnObjectCircle)
	ON_COMMAND(ID_OBJECT_DIAMOND, &CXDrawerView::OnObjectDiamond)
	ON_COMMAND(ID_OBJECT_X, &CXDrawerView::OnObjectX)
	ON_COMMAND(ID_OBJECT_BUBBLE, &CXDrawerView::OnObjectBubble)
	ON_COMMAND(ID_MODAL_DIALOG, &CXDrawerView::OnModalDialog)
	ON_COMMAND(ID_MODALESS_DIALOG, &CXDrawerView::OnModalessDialog)
END_MESSAGE_MAP()

// CXDrawerView ����/�Ҹ�

CXDrawerView::CXDrawerView()
{
	//::MessageBox(NULL, _T("CXDrawerView"), _T("CXDrawerView"), 0);
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	currentFigure = NULL;
	whatToDraw = DRAW_BOX;	
	pDlg = new ModalDialog(this);	
	mainPopup = new MainPopup(this, _T("�׸���"));
	xPopup = new FigurePopup(this, _T("����"));
	bubblePopup = new FigurePopup(this, _T("����"));
	linePopup = new FigurePopup(this, _T("��"));
	boxPopup = new FigurePopup(this, _T("�簢��"));
	circlePopup = new FigurePopup(this, _T("��"));
	diamondPopup = new FigurePopup(this, _T("���̾Ƹ��"));
}

CXDrawerView::~CXDrawerView()
{
	if (pDlg != NULL) delete pDlg;
	if (mainPopup != NULL) delete mainPopup;
	if (xPopup != NULL) delete xPopup;
	if (bubblePopup != NULL) delete bubblePopup;
	if (linePopup != NULL) delete linePopup;
	if (boxPopup != NULL) delete boxPopup;
	if (circlePopup != NULL) delete circlePopup;
	if (diamondPopup != NULL) delete diamondPopup;
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
	CGdiObject *oldBrush =pDC->SelectStockObject(NULL_BRUSH);

	FigureList *list = pDoc->getFigures();
	POSITION pos = list->GetHeadPosition();
	while (pos != NULL) {
		Figure *ptr = list->GetNext(pos);
		// referenc type ���� �ʿ�
		ptr->draw(pDC);
	}
	pDC->SelectObject(oldBrush);
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
	CPoint testPoint(point);
	ScreenToClient(&testPoint);

	currentFigure = NULL;

	CXDrawerDoc* pDoc = GetDocument();

	FigureList *list = pDoc->getFigures();
	POSITION pos = list->GetHeadPosition();
	while (pos != NULL) {
		Figure *ptr = list->GetNext(pos);
		if (ptr->region->PtInRegion(testPoint.x, testPoint.y)) {
			currentFigure = ptr;
			break;
		}
	}
	if (currentFigure == NULL) {
		mainPopup->popup(point.x, point.y);
	} else {
		currentFigure->popup(point.x, point.y);
	}
	/*
	//RTTI
	if (found == NULL) {
		mainPopup->popup(point.x, point.y);
	} else if (found->IsKindOf(RUNTIME_CLASS(X))) {
		xPopup->popup(point.x, point.y);
	} else if (found->IsKindOf(RUNTIME_CLASS(Box))) {
		boxPopup->popup(point.x, point.y);
	} else if (found->IsKindOf(RUNTIME_CLASS(Line))) {
		linePopup->popup(point.x, point.y);
	}
	*/
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
	CDC *pDC = GetDC();

	if(whatToDraw == DRAW_X) {
		currentFigure = new X(point.x, point.y);
		currentFigure->setPopup(xPopup);
	} else if(whatToDraw == DRAW_BUBBLE) {
		currentFigure = new Bubble(point.x, point.y);
		currentFigure->setPopup(bubblePopup);
	} else if(whatToDraw == DRAW_BOX) {
		currentFigure = new Box(point.x, point.y);	
		currentFigure->setPopup(boxPopup);
	} else if(whatToDraw == DRAW_LINE) {
		currentFigure = new Line(point.x, point.y);	
		currentFigure->setPopup(linePopup);
	} else if(whatToDraw == DRAW_CIRCLE) {
		currentFigure = new Circle(point.x, point.y);	
		currentFigure->setPopup(circlePopup);
	} else if(whatToDraw == DRAW_DIAMOND) {
		currentFigure = new Diamond(point.x, point.y);	
		currentFigure->setPopup(diamondPopup);
	}
	currentFigure->draw(pDC);
	
	CView::OnLButtonDown(nFlags, point);
}


void CXDrawerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(currentFigure != NULL)
	{
		CDC *pDC = GetDC();
		CGdiObject *oldBrush = pDC->SelectStockObject(NULL_BRUSH);

		currentFigure->setXY2(point.x, point.y);
		currentFigure->draw(pDC);

		pDC->SelectObject(oldBrush);

		CXDrawerDoc *pDoc = GetDocument();
		currentFigure->makeRegion();

		pDoc->add(currentFigure);
		pDoc->SetModifiedFlag(TRUE);
	}
	currentFigure = NULL;
	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}


void CXDrawerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(currentFigure != NULL)
	{
		CDC *pDC = GetDC();
		int oldMode = pDC->SetROP2(R2_NOTXORPEN);
		CGdiObject *oldBrush = pDC->SelectStockObject(NULL_BRUSH);

		currentFigure->draw(pDC);
		currentFigure->setXY2(point.x, point.y);
		currentFigure->draw(pDC);

		pDC->SelectObject(oldBrush);
		pDC->SetROP2(oldMode);
	}
	CView::OnMouseMove(nFlags, point);
}


void CXDrawerView::OnObjectBox()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	whatToDraw = DRAW_BOX;
}


void CXDrawerView::OnObjectLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	whatToDraw = DRAW_LINE;
}


void CXDrawerView::OnObjectCircle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	whatToDraw = DRAW_CIRCLE;
}


void CXDrawerView::OnObjectDiamond()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	whatToDraw = DRAW_DIAMOND;
}


void CXDrawerView::OnObjectX()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	whatToDraw = DRAW_X;
}


void CXDrawerView::OnObjectBubble()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	whatToDraw = DRAW_BUBBLE;
}


void CXDrawerView::OnModalDialog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ModalDialog aDlg(this);
	aDlg.DoModal();
}


void CXDrawerView::OnModalessDialog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.	
	pDlg->ShowWindow(SW_SHOW);
}


BOOL CXDrawerView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	pDlg->Create(ModalDialog::IDD);
	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CXDrawerView::OnDeleteFigure() {
	if (currentFigure == NULL) return;
	GetDocument()->removeFigure(currentFigure);
	delete currentFigure;
	currentFigure = NULL;
	Invalidate();
}