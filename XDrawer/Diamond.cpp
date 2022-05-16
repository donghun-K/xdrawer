#include "stdafx.h"
#include "Diamond.h"


Diamond::Diamond()
	:Figure()
{	
}
Diamond::Diamond(int x1, int y1)
	:Figure(x1, y1)
{	
}
Diamond::Diamond(int x1, int y1, int x2, int y2)
	:Figure(x1, y1, x2, y2)
{
}
Diamond::~Diamond()
{
}

//Scope resolution operator
void Diamond::draw(CDC* pDC)
{
	int dx, dy;
	dx = m_x1 + (m_x2 - m_x1) / 2;
	dy = m_y1 + (m_y2 - m_y1) / 2;

	pDC->MoveTo(dx, m_y1); // ��ǥ ���� �̵�
	pDC->LineTo(m_x2, dy); // �� ��ǥ���� ���� ��ǥ���� ���� �׸���
	pDC->LineTo(dx, m_y2);
	pDC->LineTo(m_x1, dy);
	pDC->LineTo(dx, m_y1);
}
