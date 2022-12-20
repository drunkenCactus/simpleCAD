#include "polygon.h"

polygon::polygon()
{
	maxPoints = 100;
	minPoints = 3;
}

//отрисовка объекта
void polygon::draw(HDC workDC)
{
	if(pt.size() < 2)
		return;
	
	SelectObject(workDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(workDC, OBJBRUSHCOLOR);
	
	SelectObject(workDC, GetStockObject(DC_PEN));
	SetDCPenColor(workDC, OBJPENCOLOR);
	
	Polygon(workDC, &pt[0], pt.size());
}