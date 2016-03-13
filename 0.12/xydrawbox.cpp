#include "xydrawbox.h"



XYDrawbox::XYDrawbox(HWND hwndp, HINSTANCE hinst, int xpos, int ypos, int xlen, int ylen)
	: XYWndBase(hwndp, NULL, hinst,"xydrawboxclass", "xydrawboxtitle",
	WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, GRAY_BRUSH,
	xpos, ypos, xlen, ylen),
	lengthXScroll(0), lengthYScroll(0), posXScroll(0), posYScroll(0),
	lengthXPage(0), lengthYPage(0), isXScroll(false), isYScroll(false), pimgdata(NULL)

{
	ZeroMemory(&scrollinfo, sizeof(SCROLLINFO));
	scrollinfo.cbSize = sizeof(SCROLLINFO);
}

BOOL XYDrawbox::InitWnd()
{
	SetWndProclpParam(this);
	std::cout << "WNDPROC :D:" << (this->wndProcThis) << std::endl;
	if (XYWndBase::InitWnd() == FALSE)
	{
		std::cout << "WARNING!!" << std::endl;
		return FALSE;
	}
	else
	{
		ShowScrollBar(this->hwndThis, SB_HORZ, FALSE);
		ShowScrollBar(this->hwndThis, SB_VERT, FALSE);
	}
	return TRUE;
}

void XYDrawbox::SetPosXScrollBar(int posx)
{
	this->posXScroll = posx;
}

void XYDrawbox::SetPosYScrollBar(int posy)
{
	this->posYScroll = posy;
}

void XYDrawbox::RefreshXPosScrollBar()
{
	scrollinfo.fMask = SIF_POS;
	scrollinfo.nPos = this->posXScroll;
	SetScrollInfo(this->hwndThis, SB_HORZ, &scrollinfo, TRUE);
	GetScrollInfo(this->hwndThis, SB_HORZ, &scrollinfo);
	this->posXScroll = scrollinfo.nPos;
}
void XYDrawbox::RefreshYPosScrollBar()
{
	scrollinfo.fMask = SIF_POS;
	scrollinfo.nPos = this->posYScroll;
	SetScrollInfo(this->hwndThis, SB_VERT, &scrollinfo, TRUE);
	GetScrollInfo(this->hwndThis, SB_VERT, &scrollinfo);
	this->posYScroll = scrollinfo.nPos;
}
void XYDrawbox::RefreshAllScrollBar()
{
	//Horizontal Scrollbar Refresh Setting
	if (this->isXScroll)
	{
		ShowScrollBar(this->hwndThis, SB_HORZ, TRUE);
		scrollinfo.fMask = SIF_ALL;
		scrollinfo.nMax = this->lengthXScroll;
		scrollinfo.nMin = 0;
		scrollinfo.nPage = this->lengthXPage;
		scrollinfo.nPos = this->posXScroll;
		SetScrollInfo(this->hwndThis, SB_HORZ, &scrollinfo, TRUE);
	}
	else
	{
		ShowScrollBar(this->hwndThis, SB_HORZ, FALSE);
	}
	//Vertical Scrollbar Refresh Setting
	if (this->isYScroll)
	{
		ShowScrollBar(this->hwndThis, SB_VERT, TRUE);
		scrollinfo.fMask = SIF_ALL;
		scrollinfo.nMax = this->lengthYScroll;
		scrollinfo.nMin = 0;
		scrollinfo.nPage = this->lengthYPage;
		scrollinfo.nPos = this->posYScroll;
		SetScrollInfo(this->hwndThis, SB_VERT, &scrollinfo, TRUE);
	}
	else
	{
		ShowScrollBar(this->hwndThis, SB_VERT, FALSE);
	}
}
void XYDrawbox::SetupScrollBar()
{
	this->lengthXPage = this->lengthXWnd;
	this->lengthYPage = this->lengthYWnd;
	this->isXScroll = this->lengthXScroll > this->lengthXWnd;
	this->isYScroll = this->lengthYScroll > this->lengthYWnd;
	std::cout << "LENGTHXWND:D:" << this->lengthXWnd << std::endl;
	std::cout << "LENGTHYWND:D:" << this->lengthYWnd << std::endl;
	std::cout << "LENGTHXPAGE:D:" << this->lengthXPage << std::endl;
	std::cout << "LENGTHYPAGE:D:" << this->lengthYPage << std::endl;
	std::cout << "LENGTHXSCROLL:D:" << this->lengthXScroll << std::endl;
	std::cout << "LENGTHYSCROLL:D:" << this->lengthYScroll << std::endl;
	std::cout << "POSXSCROLL:D:" << this->posXScroll << std::endl;
}

void XYDrawbox::DisplayImage(HDC& hdc)
{
	BITMAPINFO bmi;
	
	if (this->pimgdata == NULL)
	{
		std::cout << ":D:" << "IMGDATA==NULL" << std::endl;
		return;
	}
	else
	{
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = this->lengthXScroll;
		bmi.bmiHeader.biHeight = this->lengthYScroll;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		SetDIBitsToDevice(hdc,
			0, 0, this->lengthXScroll, this->lengthYScroll,
			this->posXScroll, 0,
			this->posYScroll, this->lengthYScroll,
			this->pimgdata,
			&bmi,
			DIB_RGB_COLORS
			);
	}
}

void XYDrawbox::PointImageData(int imgwidth, int imgheight, unsigned char* imgdata)
{
	this->pimgdata = imgdata;
	this->lengthXScroll = imgwidth;
	this->lengthYScroll = imgheight;
}

void XYDrawbox::GetXScrollTrackPos()
{
	scrollinfo.fMask = SIF_TRACKPOS;
	GetScrollInfo(hwndThis, SB_HORZ, &scrollinfo);
}
void XYDrawbox::GetYScrollTrackPos()
{
	scrollinfo.fMask = SIF_TRACKPOS;
	GetScrollInfo(hwndThis, SB_VERT, &scrollinfo);
}