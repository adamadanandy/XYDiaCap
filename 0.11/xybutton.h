#ifndef XYBUTTON_H
#define XYBUTTON_H
#include <Windows.h>
#include <iostream>
#include "xywndbase.h"

class XYButton : public XYWndBase
{
public:
	int btnID;
	unsigned int msgButton;
public:
	XYButton(HWND hwndp, HINSTANCE hinst, int posx, int posy, int lenx, int leny, char* buttontext, int id);
	BOOL InitWnd();
	void ButtonClick();
	BOOL SetMessageButton(char* msgname);
	void SetButtonPic(int width, int height, int bits, unsigned char * figdata);
};

#endif//XYBUTTON_H