#ifndef XYDRAWBOX_H
#define XYDRAWBOX_H

#include <Windows.h>
#include <iostream>
#include "xywndbase.h"

LRESULT CALLBACK WndProcDrawbox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class XYDrawbox : public XYWndBase
{
public:
	int lengthXScroll;
	int lengthYScroll;
	int posXScroll;
	int posYScroll;
	int lengthXPage;
	int lengthYPage;
	bool isXScroll;
	bool isYScroll;
	unsigned char* pimgdata;
	SCROLLINFO scrollinfo;

public:
	XYDrawbox(HWND hwndp, HINSTANCE hinst, int xpos, int ypos, int xlen, int ylen);
	BOOL InitWnd();
	void RefreshXPosScrollBar();
	void RefreshYPosScrollBar();
	void RefreshAllScrollBar();
	void SetPosXScrollBar(int posx);
	void SetPosYScrollBar(int posy);
	void SetupScrollBar();
	void PointImageData(int imgwidth, int imgheight, unsigned char* imgdata);
	void DisplayImage(HDC& hdc);
	void GetXScrollTrackPos();
	void GetYScrollTrackPos();
};

#endif//XYDRAWBOX_H