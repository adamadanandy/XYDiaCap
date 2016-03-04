#ifndef XYIMAGE_H
#define XYIMAGE_H

#include <Windows.h>
#include <iostream>

LRESULT CALLBACK DrawBoxProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class XYWindow;
class XYCap;

class XYImage
{
public:
	HWND hwnddrawbox;
	HWND hwndParent;
	HINSTANCE hInstance;
	char* drawboxclass;
	char* drawboxtitle;
	XYWindow *pXYWindow;
	XYCap * pXYCap;
	BOOL dataprepared;
	int lengthXDrawbox;
	int lengthYDrawbox;
	int lengthXImage;
	int lengthYImage;
	int posXLeftUpCorner;
	int posYLeftUpCorner;
	int lengthXScroll;
	int lengthYScroll;
public:
	BOOL InitDrawBox(HWND hwndparent, HINSTANCE hinstance, XYWindow *pParent);
	void SetupScrollbar();
	void MessageHorizontalScroll(UINT message, WPARAM wParam, LPARAM lParam);
	void MessageVerticalScroll(UINT message, WPARAM wParam, LPARAM lParam);
	XYImage();
};


#endif//XYIMAGE_H