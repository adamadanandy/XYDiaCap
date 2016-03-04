#ifndef XYFRAME_H
#define XYFRAME_H
#include <Windows.h>
#include <iostream>
#include "xywndbase.h"

LRESULT CALLBACK WndProcFrame(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class XYFrame : public XYWndBase
{
public:
	RECT clientrect;
	int clientwidth;
	int clientheight;
	int toolbarheight;
public:
	XYFrame(HINSTANCE hinst);
	void RefreshClientAreaData();
	void ShowUpdate(int iCmdShow);
};

#endif//XYFRAME_H