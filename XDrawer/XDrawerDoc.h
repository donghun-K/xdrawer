
// XDrawerDoc.h : CXDrawerDoc Ŭ������ �������̽�
//


#pragma once

class Box;

class CXDrawerDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CXDrawerDoc();
	DECLARE_DYNCREATE(CXDrawerDoc)

	Box *boxes[100];
	int nBox;
// Ư���Դϴ�.
public:	

// �۾��Դϴ�.
public:
	void add(Box *pBox);
	inline int boxCount() { return nBox; }
	inline Box *getBox(int i) { return boxes[i]; }
// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CXDrawerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
