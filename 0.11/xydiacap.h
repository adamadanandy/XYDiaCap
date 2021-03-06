#ifndef XYDIACAP_H
#define XYDIACAP_H

#include <Windows.h>
#include <iostream>
#include "xybutton.h"
#include "xycap.h"
#include "xydebug.h"
#include "xydrawbox.h"
#include "xyframe.h"
#include "xyimage.h"
#include "xywndbase.h"

class XYDiaCap
{
public:
	XYFrame *pXYFrame;
	XYButton *pXYButtons[10];
	XYDrawbox *pXYDrawbox;
	HINSTANCE hInstance;
	MSG msg;
public:
	XYDiaCap(HINSTANCE hinst);
	BOOL InitWindows();
	void ShowUpdate(int iCmdShow);
	int MainLoop();
};

extern XYDiaCap* pg_xydiacap;
#endif//XYDIACAP_H