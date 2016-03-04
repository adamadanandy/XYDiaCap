#include "xywndbase.h"

BOOL XYWndBase::InitWnd()
{
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = this->wndProcThis;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = this->hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(this->backgroundColor);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = this->wndClass;

	if (!RegisterClass(&wndclass))
	{
		return FALSE;
	}
	this->hwndThis = CreateWindow(this->wndClass,
		this->wndTitle,
		this->wndStyle,
		this->posXWnd, this->posYWnd,
		this->lengthXWnd, this->lengthYWnd,
		this->hwndParent,
		this->hmnuThis,
		this->hInstance,
		this->ptrForWndProc
		);
	std::cout << "HWNDTHIS" << this->hwndThis << std::endl;
	return TRUE;
}

XYWndBase::XYWndBase(HWND hwndP, HMENU hmnu, HINSTANCE hinst,
	char* classname, char* title, int style, int bgcolor,
	int x, int y, int lengthx, int lengthy)
	: hwndParent(hwndP), hmnuThis(hmnu), hInstance(hinst),
	wndClass(classname), wndTitle(title), wndStyle(style), backgroundColor(bgcolor),
	posXWnd(x), posYWnd(y), lengthXWnd(lengthx), lengthYWnd(lengthy)
{

}

void XYWndBase::SetWndProclpParam(void* wplpParam)
{
	this->ptrForWndProc = wplpParam;
}

void XYWndBase::SetWndProc(WNDPROC wndproc)
{
	this->wndProcThis = wndproc;
}

void XYWndBase::SetWndSize(int w, int h)
{
	this->lengthXWnd = w;
	this->lengthYWnd = h;
}

POINT XYWndBase::OnChangeSize(int w, int h)
{
	return POINT{ w, h };
}