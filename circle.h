#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "object.h"

class circle : public object
{
public:
	
	circle();

private:
	
	//отрисовка объекта
	void draw(HDC workDC);
};

#endif //CIRCLE_H_