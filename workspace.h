#ifndef WORKSPACE_H_
#define WORKSPACE_H_

#include <windows.h>
#include <vector>

#include "properties.h"
#include "object.h"

class workspace
{
public:
	
	//установка дескриптора окна
	void show(HWND hWnd_);
	
	workspace();
	~workspace();
	
	//обработка нажатия ЛКМ
	void pButton(objtype t, int x, int y);
	
	//обработка движения курсора в режиме создания объекта
	void mMove(int x, int y);
	
	//обработка нажатия кнопки останова рисования объекта
	void finishButton();

private:

	//дескриптор окна
	HWND hWnd;
	
	//массив объектов
	std::vector<object*> obj;
	
	//указатель на создаваемый объект
	object* curObj;
	
	//временная точка, необходимая для анимации эффекта рисования
	POINT ptmp;
	
	//создание нового объекта заданного типа
	object* createObj(objtype t);
	
	//отрисовка рабочего пространства вместе с объектами
	void draw();
	
	//отрисовка рабочего пространства
	void drawWS(HDC workDC);
	
	//добавление объекта в массив и обнуление указателя curObj
	void finishObjectCreate();
};

#endif //WORKSPACE_H_