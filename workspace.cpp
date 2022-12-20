#include "workspace.h"

#include <iostream>

#include "macro.h"
#include "rect.h"
#include "polygon.h"
#include "circle.h"


workspace::workspace()
{
	CV("workspace created")
	curObj = NULL;
}

workspace::~workspace()
{
	for(auto& o : obj)
		delete o;
	CV("workspace deleted")
}

void workspace::show(HWND hWnd_)
{
	hWnd = hWnd_;
	draw();
}

//отрисовка рабочего пространства вместе с объектами
void workspace::draw()
{
	//CV("draw workspace with objects")
	
	HDC wndDC = GetDC(hWnd);
	HDC memDC = CreateCompatibleDC(wndDC);
	HBITMAP memBM = CreateCompatibleBitmap
	(
		wndDC,
		WORKSPWIDTH,
		WORKSPHEIGHT
	);
	SelectObject(memDC, memBM);
	
	//отрисовка рабочего пространства
	drawWS(memDC);
	//отрисовка всех созданных объектов
	for(auto& o : obj)
		o->draw(memDC);
	//отрисовка объекта, создаваемого в данный момент - анимация эффекта рисования
	if(curObj)
		curObj->drawTmp(memDC, ptmp);
	
	BitBlt
	(
		wndDC,				// дескриптор целевого DC		
		WORKSPCORNERX,		// x-коорд. левого верхнего угла целевого прямоугольника
		WORKSPCORNERY,		// y-коорд. левого верхнего угла целевого прямоугольника
		WORKSPWIDTH,		// ширина целевого прямоугольника
		WORKSPHEIGHT,  		// высота целевого прямоугольника	       
		memDC,          	// дескриптор исходного DC	
		0,              	// x-коорд. левого верхнего угла исходного прямоугольника	
		0,              	// y-коорд. левого верхнего угла исходного прямоугольника	
		SRCCOPY         	// код растровой операции	
	);
	
	//освобождение ресурсов
	DeleteDC(memDC);
	DeleteObject(memBM);
	ReleaseDC(hWnd, wndDC);
}

//отрисовка рабочего пространства
void workspace::drawWS(HDC workDC)
{
	//CV("draw workspace")
	
	SelectObject(workDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(workDC, WSBRUSHCOLOR);
	
	SelectObject(workDC, GetStockObject(DC_PEN));
	SetDCPenColor(workDC, WSPENCOLOR);
	
	Rectangle(workDC, 0, 0, WORKSPWIDTH, WORKSPHEIGHT);
}

//обработка нажатия ЛКМ
void workspace::pButton(objtype t, int x, int y)
{
	//если новый объект не создан
	if(!curObj)
	{
		//создание нового объекта
		curObj = createObj(t);
		CV("begin object creation");
	}
	
	//добавление точки в объект
	curObj->addPoint(x, y);
	
	//если достигнут максимум точек для объекта, то завершаем его создание
	if(curObj->reachedMaxPoints())
	{
		finishObjectCreate();
		draw();
	}
}

//создание нового объекта заданного типа
object* workspace::createObj(objtype t)
{
	switch(t)
	{
		case objtype::rect:
			return new rect;
			
		case objtype::polygon:
			return new polygon;
		
		case objtype::circle:
			return new circle;
		
		default:
			CV("invalid object type");
			exit(0);
			return NULL;
	}
}

//добавление объекта в массив и обнуление указателя curObj
void workspace::finishObjectCreate()
{
	if(!curObj)
		return;
	
	CV("end object creation");
	obj.push_back(curObj);
	curObj = NULL;
}

//обработка движения курсора в режиме создания объекта
void workspace::mMove(int x, int y)
{
	if(!curObj)
		return;
	
	ptmp.x = x;
	ptmp.y = y;
	draw();
}

//обработка нажатия кнопки останова рисования объекта
void workspace::finishButton()
{
	if(!curObj)
		return;
	
	//если достигнут минимум точек для объекта, то завершаем его создание
	if(curObj->reachedMinPoints())
	{
		finishObjectCreate();
	}
	//прекращаем создание объекта и удаляем его
	else
	{
		CV("abort object creation");
		delete curObj;
		curObj = NULL;
	}
	draw();
}