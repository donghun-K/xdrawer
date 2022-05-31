// ModalDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "XDrawer.h"
#include "ModalDialog.h"
#include "afxdialogex.h"

#include "XDrawerView.h"
#include "XDrawerDoc.h"

#include "Box.h"
#include "X.h"
#include "Bubble.h"
#include "Circle.h"
#include "Line.h"
#include "Diamond.h"


// ModalDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ModalDialog, CDialogEx)

ModalDialog::ModalDialog(CXDrawerView *const pView, CWnd* pParent /*=NULL*/)
	: CDialogEx(ModalDialog::IDD, pParent)
	, m_x1(0)
	, m_y1(0)
	, m_x2(_T(""))
	, m_y2(_T(""))
	, m_pView(pView)
{
	// m_combo.AddString(_T("����")); 
}

ModalDialog::~ModalDialog()
{
}

void ModalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_x1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_y1);
	DDX_Text(pDX, IDC_EDIT_X2, m_x2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_y2);
	DDX_Control(pDX, IDC_COMBO_FIGURE, m_combo);
}


BEGIN_MESSAGE_MAP(ModalDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModalDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ModalDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// ModalDialog �޽��� ó�����Դϴ�.


void ModalDialog::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
	UpdateData();
	int x1 = m_x1;
	int y1 = m_y1;

	int x2 = _ttoi(m_x2);
	int y2 = _ttoi(m_y2);

	CString name;
	m_combo.GetWindowTextW(name);
	Figure *fig = NULL;

	if (name == _T("����")) {
		fig = new X(x1, y1);
	} else if (name == _T("����")) {
		fig = new Bubble(x1, y1);
	} else if (name == _T("�簢��")) {
		fig = new Box(x1, y1, x2, y2);
	} else if (name == _T("��")) {
		fig = new Line(x1, y1, x2, y2);
	} else if (name == _T("��")) {
		fig = new Circle(x1, y1, x2, y2);
	} else if (name == _T("���̾Ƹ��")) {
		fig = new Diamond(x1, y1, x2, y2);
	}	

	m_pView->GetDocument()->add(fig);
	m_pView->Invalidate();

	m_x1 = 0;
	m_y1 = 0;
	m_x2 = _T("0");
	m_y2 = _T("0");

	UpdateData(FALSE);
}


void ModalDialog::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


BOOL ModalDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_combo.AddString(_T("����"));
	m_combo.AddString(_T("����"));
	m_combo.AddString(_T("�簢��"));
	m_combo.AddString(_T("��"));
	m_combo.AddString(_T("��"));
	m_combo.AddString(_T("���̾Ƹ��"));

	m_combo.SetCurSel(2);

	return TRUE;  // return TRUE unless you set the focus to a control
}
