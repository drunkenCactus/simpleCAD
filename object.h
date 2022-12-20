#ifndef OBJECT_H_
#define OBJECT_H_

#include <windows.h>
#include <vector>

#include "properties.h"

enum class objtype {rect, polygon, circle};


class object
{
public:

	object();
	
	//добавление точки в объект
	void addPoint(int x, int y);
	
	//отрисовка объекта в процессе его создания (с подвижной точкой)
	void drawTmp(HDC workDC, POINT& tmp);
	
	//отрисовка объекта
	virtual void draw(HDC workDC) = 0;
	
	//проверка максимума и минимума количества точек
	bool reachedMaxPoints() {return pt.size() >= maxPoints;}
	bool reachedMinPoints() {return pt.size() >= minPoints;}
	
	virtual ~object();
	
protected:

	//массив точек
	std::vector<POINT> pt;
	
	int maxPoints;
	int minPoints;

private:
	
	int id;
	static int count;
};

#endif //OBJECT_H_