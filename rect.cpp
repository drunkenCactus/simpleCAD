#include "rect.h"

rect::rect()
{
	maxPoints = 2;
	minPoints = 2;
}

//отрисовка объекта
void rect::draw(HDC workDC)
{
	if(pt.size() != 2)
		return;
	
	SelectObject(workDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(workDC, OBJBRUSHCOLOR);
	
	SelectObject(workDC, GetStockObject(DC_PEN));
	SetDCPenColor(workDC, OBJPENCOLOR);
	
	Rectangle(workDC, pt[0].x, pt[0].y, pt[1].x, pt[1].y);
}
