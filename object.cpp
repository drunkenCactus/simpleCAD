#include "object.h"

#include <iostream>

#include "macro.h"

int object::count;

object::object()
{
	count ++;
	id = count;
	std::cout << "New object " << id << std::endl;
}

object::~object()
{
	std::cout << "Delete object " << id << std::endl;
}

//добавление точки в объект
void object::addPoint(int x, int y)
{
	POINT p;
	p.x = x;
	p.y = y;
	pt.push_back(p);
}

//отрисовка объекта в процессе его создания (с подвижной точкой)
void object::drawTmp(HDC workDC, POINT& tmp)
{
	pt.push_back(tmp);
	draw(workDC);
	pt.pop_back();
}
