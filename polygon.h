#ifndef POLYGON_H_
#define POLYGON_H_

#include "object.h"

class polygon : public object
{
public:
	
	polygon();

private:
	
	//отрисовка объекта
	void draw(HDC workDC);
};

#endif //POLYGON_H_