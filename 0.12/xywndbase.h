#ifndef XYWNDBASE_H
#define XYWNDBASE_H

#include <Windows.h>
#include <iostream>

class XYWndBase
{
public:
	HWND hwndThis;
	HWND hwndParent;
	HMENU hmnuThis;
	HINSTANCE hInstance;
	int lengthXWnd, lengthYWnd;
	int posXWnd, posYWnd;
	char* wndClass;
	char* wndTitle;
	DWORD wndStyle;
	int backgroundColor;
	WNDPROC wndProcThis;
	void* ptrForWndProc;
public:
	virtual BOOL InitWnd();
	XYWndBase(HWND hwndP, HMENU hmnu, HINSTANCE hinst,
		char* classname, char* title, int style, int bgcolor,
		int x, int y, int lengthx, int lengthy);
	void SetWndProc(WNDPROC wndproc);
	void SetWndProclpParam(void* wplpParam);
	void SetWndSize(int w, int h);
	POINT OnChangeSize(int w, int h);
};

#endif//XYWNDBASE_H