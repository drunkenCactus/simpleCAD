#ifndef RECT_H_
#define RECT_H_

#include "object.h"

class rect : public object
{
public:
	
	rect();

private:
	
	//отрисовка объекта
	void draw(HDC workDC);
};

#endif //RECT_H_
