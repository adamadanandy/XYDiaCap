#include "xyframe.h"



XYFrame::XYFrame(HINSTANCE hinst) : XYWndBase(NULL, NULL, hinst,
	"xydiacapclass", "XYDiaCap",
	WS_OVERLAPPEDWINDOW, LTGRAY_BRUSH,
	CW_USEDEFAULT, CW_USEDEFAULT, 500, 300),
	toolbarheight(35)
{
}

void XYFrame::RefreshClientAreaData()
{
	GetClientRect(this->hwndThis, &(this->clientrect));
	this->clientheight = this->clientrect.bottom - this->clientrect.top;
	this->clientwidth = this->clientrect.right - this->clientrect.left;
}

void XYFrame::ShowUpdate(int iCmdShow)
{
	ShowWindow(this->hwndThis, iCmdShow);
	UpdateWindow(this->hwndThis);
}