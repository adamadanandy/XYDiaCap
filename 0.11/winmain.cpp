//TODO:
//winmain	:: WinMain()
//XYWindow	:: all Window structure related function: button showpicture drawrect highlight...
//XYCap		:: capture the desktop get the figure data
//XYBmp		:: open bmp get the figure data, save as bmp file
//XYAlgo	:: algorithm container for XYDiaCap project:
//				FIND PART:	
//					find horizontal line, find vertical line, find curve line, find dashed line, find data point...
//				MANIPULATE FIG DATA:
//					grey level, brightness level, choose color, mix color
//				ALGORITHM OF FIG DATA:
//					sharpness, ...
//XYFrame	:: build a local frame and convert the pixel coordinate to local frame coordinate
//
/*
#include <windows.h>
#include "xydebug.h"
#include "xywindow.h"
#include <iostream>

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	XYDebug gXYDebug;
	XYWindow gXYWindow(hInstance);
	gXYDebug.OpenConsole();
	gXYWindow.InitWindow();
	gXYWindow.ShowUpdate(iCmdShow);

	return gXYWindow.MainLoop();
}
*/

#include <windows.h>
#include "xydebug.h"
#include "xydiacap.h"
#include <iostream>

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	XYDebug gXYDebug;
	
	gXYDebug.OpenConsole();
	pg_xydiacap = new XYDiaCap(hInstance);
	pg_xydiacap->InitWindows();
	pg_xydiacap->ShowUpdate(iCmdShow);

	return pg_xydiacap->MainLoop();
}
