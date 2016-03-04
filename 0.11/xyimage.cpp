#include "xyimage.h"
#include "xywindow.h"
#include "xycap.h"
#include <iostream>
LRESULT CALLBACK DrawBoxProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC            hdc;
	static HINSTANCE      hInstance;
	static XYImage      *pXYDrawbox;
	PAINTSTRUCT    ps;


	switch (message)
	{
	case WM_MOUSEMOVE:
		//std::cout << "[" << LOWORD(lParam) << "," << HIWORD(lParam) << "]" << std::endl;
		break;
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		pXYDrawbox = (XYImage*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		
		hdc = GetDC(hwnd);
		ShowScrollBar(hwnd, SB_BOTH, FALSE);
		break;
	case WM_SIZE:
		std::cout << "/" << LOWORD(lParam) << "," << HIWORD(lParam) << "/" << std::endl;
		pXYDrawbox->lengthXDrawbox = LOWORD(lParam);
		pXYDrawbox->lengthYDrawbox = HIWORD(lParam);
		if (pXYDrawbox->dataprepared == TRUE)
		{
			pXYDrawbox->SetupScrollbar();
		}
		break;
	case WM_PAINT:
		//hdc = BeginPaint(hwnd, &ps);
		BeginPaint(hwnd, 0);
		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = 1366;
		bmi.bmiHeader.biHeight = 768;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		if (pXYDrawbox->dataprepared == TRUE)
		{
			SetDIBitsToDevice(hdc,
				0,0,1366,768,
				pXYDrawbox->posXLeftUpCorner,0,
				pXYDrawbox->posYLeftUpCorner, 768,
				pXYDrawbox->pXYCap->figdata,
				&bmi,
				DIB_RGB_COLORS
				);
		}
		else
		{
			//do nothing
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEWHEEL:
		std::cout << "WM_MOUSEWHEEL" << std::endl;
		break;
	case WM_VSCROLL:
		pXYDrawbox->MessageVerticalScroll(message, wParam, lParam);
		std::cout << ":" << pXYDrawbox->posXLeftUpCorner << "," << pXYDrawbox->posYLeftUpCorner << ":" << std::endl;
		break;
	case WM_HSCROLL:
		pXYDrawbox->MessageHorizontalScroll(message, wParam, lParam);
		std::cout << ":" << pXYDrawbox->posXLeftUpCorner << "," << pXYDrawbox->posYLeftUpCorner << ":" << std::endl;
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

XYImage::XYImage()
{
	this->drawboxclass = "drawboxclass";
	this->drawboxtitle = "drawboxtitle";
	this->posXLeftUpCorner = 0;
	this->posYLeftUpCorner = 0;
	this->lengthXImage = 1366;
	this->lengthYImage = 768;
}

BOOL XYImage::InitDrawBox(HWND hwndparent, HINSTANCE hinstance, XYWindow *pParent)
{
	WNDCLASS wndclass;
	this->hwndParent = hwndparent;
	this->hInstance = hinstance;
	this->pXYWindow = pParent;
	this->pXYCap = &(pParent->xyMainObj);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = DrawBoxProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = drawboxclass;
	if (!RegisterClass(&wndclass))
	{
		return 0;
	}
	lengthXDrawbox = 40;
	lengthYDrawbox = 20;
	hwnddrawbox = CreateWindow(drawboxclass,
		drawboxtitle,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
		0, 35,
		40, 20,
		hwndParent,
		NULL,
		hInstance,
		this
		);
	return 1;
}

void XYImage::SetupScrollbar()
{
	//4 time move -> 1 page-> 1 height*0.9
	SCROLLINFO scrollinfo;
	ZeroMemory(&scrollinfo, sizeof(SCROLLINFO));
	if (lengthXImage > lengthXDrawbox)
	{
		scrollinfo.cbSize = sizeof(SCROLLINFO);
		scrollinfo.nMin = 0;
		scrollinfo.nMax = lengthXImage;
		scrollinfo.nPage = (int)(lengthXDrawbox);
		scrollinfo.fMask = SIF_RANGE | SIF_PAGE;
		ShowScrollBar(hwnddrawbox, SB_HORZ, TRUE);
		SetScrollInfo(hwnddrawbox, SB_HORZ, &scrollinfo, TRUE);
	}
	else
	{
		ShowScrollBar(hwnddrawbox, SB_HORZ, FALSE);
	}
	if (lengthYImage > lengthYDrawbox)
	{
		scrollinfo.cbSize = sizeof(SCROLLINFO);
		scrollinfo.nMin = 0;
		scrollinfo.nMax = lengthYImage;
		scrollinfo.nPage = (int)(lengthYDrawbox);
		scrollinfo.fMask = SIF_RANGE | SIF_PAGE;
		ShowScrollBar(hwnddrawbox, SB_VERT, TRUE);
		SetScrollInfo(hwnddrawbox, SB_VERT, &scrollinfo, TRUE);
	}
	else
	{
		ShowScrollBar(hwnddrawbox, SB_VERT, FALSE);
	}
	
}

void XYImage::MessageHorizontalScroll(UINT message, WPARAM wParam, LPARAM lParam)
{
	SCROLLINFO scrollinfo;
	ZeroMemory(&scrollinfo, sizeof(SCROLLINFO));
	scrollinfo.cbSize = sizeof(SCROLLINFO);
	scrollinfo.fMask = SIF_ALL;
	GetScrollInfo(hwnddrawbox, SB_HORZ, &scrollinfo);
	switch (LOWORD(wParam))
	{
	case SB_LINELEFT:
		scrollinfo.nPos -= scrollinfo.nPage / 4;
		break;
	case SB_LINERIGHT:
		scrollinfo.nPos += scrollinfo.nPage / 4;
		break;
	case SB_PAGELEFT:
		scrollinfo.nPos -= scrollinfo.nPage;
		break;
	case SB_PAGERIGHT:
		scrollinfo.nPos += scrollinfo.nPage;
		break;
	case SB_THUMBTRACK:
		scrollinfo.nPos = scrollinfo.nTrackPos;
		break;
	}
	scrollinfo.fMask = SIF_POS;
	SetScrollInfo(hwnddrawbox, SB_HORZ, &scrollinfo, TRUE);
	GetScrollInfo(hwnddrawbox, SB_HORZ, &scrollinfo);
	this->posXLeftUpCorner = scrollinfo.nPos;
	InvalidateRect(hwnddrawbox, 0, TRUE);
}

void XYImage::MessageVerticalScroll(UINT message, WPARAM wParam, LPARAM lParam)
{
	SCROLLINFO scrollinfo;
	ZeroMemory(&scrollinfo, sizeof(SCROLLINFO));
	scrollinfo.cbSize = sizeof(SCROLLINFO);
	scrollinfo.fMask = SIF_ALL;
	GetScrollInfo(hwnddrawbox, SB_VERT, &scrollinfo);
	switch (LOWORD(wParam))
	{
	case SB_LINELEFT:
		scrollinfo.nPos -= scrollinfo.nPage / 4;
		break;
	case SB_LINERIGHT:
		scrollinfo.nPos += scrollinfo.nPage / 4;
		break;
	case SB_PAGELEFT:
		scrollinfo.nPos -= scrollinfo.nPage;
		break;
	case SB_PAGERIGHT:
		scrollinfo.nPos += scrollinfo.nPage;
		break;
	case SB_THUMBTRACK:
		scrollinfo.nPos = scrollinfo.nTrackPos;
		break;
	}
	scrollinfo.fMask = SIF_POS;
	SetScrollInfo(hwnddrawbox, SB_VERT, &scrollinfo, TRUE);
	GetScrollInfo(hwnddrawbox, SB_VERT, &scrollinfo);
	this->posYLeftUpCorner = scrollinfo.nPos;
	InvalidateRect(hwnddrawbox, 0, TRUE);
}