#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include <windows.h>

#include "macro.h"
#include "properties.h"
#include "workspace.h"

#define BUTTONRECT 101
#define BUTTONPOLY 102
#define BUTTONCIRC 103


//экземпляр рабочей области
workspace ws;

//координаты курсора
int x;
int y;

//текущий тип объекта
objtype curObj = objtype::rect;

void createButton(const wchar_t* name, HWND hWnd, HINSTANCE hInstance, int id, int dy);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //создание оконного класса

    WNDCLASS wc;
	const wchar_t className[] = L"class";

    //заполнение оконного класса

    wc.style			= CS_OWNDC;								// стиль окна									
    wc.lpfnWndProc		= WindowProc;							// указатель  на оконную процедуру		
    wc.cbClsExtra		= 0;									// дополнительные байты после класса. Всегда ставьте 0
    wc.cbWndExtra		= 0;									// дополнительные байты после экземпляра окна. Всегда ставьте 0
    wc.hInstance		= hInstance;							// экземпляр приложения. Передаётся  в виде параметра  в WinMain		
    wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// иконка приложения							
    wc.hCursor			= LoadCursor(NULL, IDC_HAND);			// курсор приложения						
    wc.hbrBackground	= (HBRUSH)(6);							// цвет фона		
    wc.lpszMenuName		= NULL;									// имя меню
    wc.lpszClassName	= className;							// имя класса		

    //регистрация класса окна
    RegisterClass(&wc);


    //создание окна
	
    //Функция возвращает дескриптор окна

	HWND hWnd = CreateWindow
	(
		className,				// имя класса
		L"CAD",					// имя окна (отображается  в заголовке)
		WS_OVERLAPPEDWINDOW,	// стиль окна
		WNDCORNERX,				// координата  по горизонтали  от левого края экрана
		WNDCORNERY,				// координата  по вертикали  от верхнего края экрана
		WNDWIDTH,				// ширина окна
		WNDHEIGHT,				// высота окна
		NULL,					// родительское окно
		NULL,					// описатель меню
		hInstance,				// экземпляр приложения	
		NULL					// параметр; всегда ставьте NULL
	);
	
	createButton(L"Rectangle", hWnd, hInstance, BUTTONRECT, -120);
	createButton(L"Polygon", hWnd, hInstance, BUTTONPOLY, -20);
	createButton(L"Circle", hWnd, hInstance, BUTTONCIRC, 80);
    
    //показ окна

    //Первый аргумент - описатель созданного нами окна, второй - четвёртый аргумент WinMain.
    //В данной функции мы говорим созданному окну (hWnd) как оно должно отображаться (через nCmdShow).
	ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	//экземпляр сообщения
	MSG msg;
	
	//инициализация рабочей области
	ws.show(hWnd);

	//цикл обработки сообщений
	for(;;)
	{
		if(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
    return 0;
}

//создание кнопки
void createButton(const wchar_t* name, HWND hWnd, HINSTANCE hInstance, int id, int dy)
{
	CreateWindow
	(
		L"button",
		name,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		WORKSPWIDTH + 50,
		WORKSPHEIGHT/2 + dy,
		100,
		40,
		hWnd,
		(HMENU)id,
		hInstance,
		NULL
	);
}

//установка координат курсора мыши в рабочей области
void getCoords(LPARAM lParam)
{
	x = LOWORD(lParam) - WORKSPCORNERX;
	y = HIWORD(lParam) - WORKSPCORNERY;
}

//возвращает true, когда курсор внутри рабочей области
bool checkCoords()
{
	return (x >= 0 && x <= WORKSPWIDTH) && (y >= 0 && y <= WORKSPHEIGHT);
}

//оконная процедура
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
    {
		//сообщение о закрытии окна (Х)
		case WM_CLOSE:
			//CV("WM_CLOSE")
			//уничтожение окна
			//по видимому, вызывается заново WindowProc с сообщением WM_DESTROY
        	DestroyWindow(hWnd);
        	break;
		
		//сообщение об уничтожении окна
		case WM_DESTROY:
        	//CV("WM_DESTROY")
			//функция указывает системе, что поток сделал запрос на то, чтобы завершить свою работу (завершение работы приложения)
			//генерирует сообщение WM_QUIT, которое никак не связанос потоком данного окна
			//WM_QUIT можно поймать только из общего потока
			PostQuitMessage(0);
        	break;
		
		//сообщение о нажатии клавиши
		//тип нажатой клавиши содержится в wParam
		case WM_KEYDOWN:
			//CV("WM_KEYDOWN")
			ws.finishButton();
			break;
			
		//сообщение о нажатии ЛКМ
		case WM_LBUTTONDOWN:
			getCoords(lParam);
			if(checkCoords())
				ws.pButton(curObj, x, y);
			break;
		
		//сообщение о перемещении курсора мыши
		case WM_MOUSEMOVE:
			getCoords(lParam);
			if(checkCoords())
				ws.mMove(x, y);
			break;
		
		//сообщение о нажатии кнопки в окне
		case WM_COMMAND:
			//CV("WM_COMMAND")
			switch(LOWORD(wParam))
			{
				case BUTTONRECT:
					CV("Rectangle selected")
					curObj = objtype::rect;
					break;
					
				case BUTTONPOLY:
					CV("Polygon selected")
					curObj = objtype::polygon;
					break;
					
				case BUTTONCIRC:
					CV("Circle selected")
					curObj = objtype::circle;
					break;
			}
			//установка фокуса клавиатуры в родительское окно
			SetFocus(hWnd);
			break;
			
		default:
        	return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
