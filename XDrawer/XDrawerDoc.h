
// XDrawerDoc.h : CXDrawerDoc Ŭ������ �������̽�
//


#pragma once

class Box;
class Line;
class Circle;

class CXDrawerDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CXDrawerDoc();
	DECLARE_DYNCREATE(CXDrawerDoc)

	Box *boxes[100];
	int nBox;
	Line *lines[100];
	int nLine;
	Circle *circles[100];
	int nCircle;
// Ư���Դϴ�.
public:	

// �۾��Դϴ�.
public:
	void add(Box *pBox);
	void add(Line *pLine);
	void add(Circle *pCircle);
	inline int boxCount() { return nBox; }
	inline Box *getBox(int i) { return boxes[i]; }
	inline int lineCount() { return nLine; }
	inline Line *getLine(int i) { return lines[i]; }
	inline int circleCount() { return nCircle; }
	inline Circle *getCircle(int i) { return circles[i]; }
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
