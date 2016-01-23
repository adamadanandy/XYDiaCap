#ifndef XYWINDOW_H
#define XYWINDOW_H

#include <Windows.h>
#include <iostream>
#include "xycap.h"
#include "xyimage.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class XYWindow
{
public:
	XYCap xyMainObj;
	XYImage xyDrawbox;
	HINSTANCE hInstance;
	HWND hwnd;
	MSG msg;
	HWND hwndbutton[10];
	HWND hwnddesktop;
	char* wndClassName;
	char* wndTitle;
	HWND CreateButton(HWND hParent, HINSTANCE hInst, DWORD dwStyle, RECT& rc, int id, char* caption);
public:
	XYWindow(HINSTANCE hInstance);
	int MainLoop();
	BOOL InitWindow();
	BOOL InitDrawBox();
	void ShowUpdate(int iCmdShow);

};

#endif//XYWINDOW_H
