#pragma once


// ModalDialog ��ȭ �����Դϴ�.
class CXDrawerView;

class ModalDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ModalDialog)

public:
	ModalDialog(CXDrawerView *const pView, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ModalDialog();
	CXDrawerView *m_pView;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MODAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_x1;
	int m_y1;
	CString m_x2;
	CString m_y2;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString figure;
};
