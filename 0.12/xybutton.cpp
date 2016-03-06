#include "xybutton.h"

XYButton::XYButton(HWND hwndp, HINSTANCE hinst, int posx, int posy, int lenx, int leny, char* buttontext, int id)
	:XYWndBase(hwndp, (HMENU)id, hinst,
		"button", buttontext,
		WS_CHILD | WS_VISIBLE | BS_BITMAP,
		0, posx, posy, lenx, leny), btnID(id)
{

}

BOOL XYButton::InitWnd()
{
	this->hwndThis = CreateWindow(this->wndClass,
		this->wndTitle,
		this->wndStyle,
		this->posXWnd, this->posYWnd,
		this->lengthXWnd, this->lengthYWnd,
		this->hwndParent,
		this->hmnuThis,
		this->hInstance,
		0
		);
	return (hwndThis != 0);
}

BOOL XYButton::SetMessageButton(char* msgname)
{
	this->msgButton = RegisterWindowMessage(msgname);
	return (this->msgButton != 0);
}

void XYButton::WndProcFunction(int wParam)
{
	if (wParam == this->btnID)
	{
		SendMessage(this->hwndParent, this->msgButton, 0, 0);
	}
}

void XYButton::SetButtonPic(int width, int height, int bits, unsigned char * figdata)
{
	HBITMAP hbmpc;
	hbmpc = CreateBitmap(width, height, 1, bits, &figdata);
	SendMessage(hwndThis, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbmpc);
}

void XYButton::OnClick()
{
	std::cout << "ButtonID:: " << this->btnID <<" ButtonMSG:: "<<this->msgButton<< " OnClick " << std::endl;
	SendMessage(hwndParent, 33323, 0, 0);
	
}

void XYButton::ClickFunction(UINT message)
{
	if (message == this->msgButton)
	{
		this->OnClick();
	}
}