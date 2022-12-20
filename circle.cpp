#include "circle.h"

#include <cmath>

circle::circle()
{
	maxPoints = 2;
	minPoints = 2;
}

//отрисовка объекта
void circle::draw(HDC workDC)
{
	if(pt.size() != 2)
		return;
	
	SelectObject(workDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(workDC, OBJBRUSHCOLOR);
	
	SelectObject(workDC, GetStockObject(DC_PEN));
	SetDCPenColor(workDC, OBJPENCOLOR);
	
	int r = (int)hypot(pt[1].x - pt[0].x, pt[1].y - pt[0].y);
	Ellipse(workDC, pt[0].x - r, pt[0].y - r, pt[0].x + r, pt[0].y + r);
}