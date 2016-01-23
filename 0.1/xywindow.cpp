#include "xywindow.h"
#include "rs.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC            hdc;
	static HINSTANCE      hInstance;
	static XYWindow      *pXYWindow;
	PAINTSTRUCT    ps;
	switch (message)
	{
	case WM_MOUSEMOVE:
		std::cout << "(" << LOWORD(lParam) <<","<< HIWORD(lParam) << ")" << std::endl;
		break;
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		pXYWindow = (XYWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		break;
	case WM_SIZE:
		std::cout << "\\" << LOWORD(lParam) << "," << HIWORD(lParam) << "\\" << std::endl;
		SetWindowPos(pXYWindow->xyDrawbox.hwnddrawbox, NULL, 0, 35, LOWORD(lParam), HIWORD(lParam)-35, SWP_NOZORDER);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case BUTTON_ID_0:
			std::cout << "BUTTON_ID_0" << std::endl;
			pXYWindow->xyMainObj.SetScreenData();
			pXYWindow->xyMainObj.GetScreenHDC();
			pXYWindow->xyMainObj.HDCtoBMP();
			pXYWindow->xyMainObj.SaveBMP();
			pXYWindow->xyDrawbox.dataprepared = TRUE;
			pXYWindow->xyDrawbox.SetupScrollbar();
			InvalidateRect(pXYWindow->xyDrawbox.hwnddrawbox, 0, TRUE);
			//pXYWindow->xyMainObj.tst();
			//pXYWindow->xyMainObj.CopyBMP(pXYWindow->xyMainObj.bmptar, pXYWindow->xyMainObj.bmpsrc);
			//pXYWindow->xyMainObj.ReleaseObj(pXYWindow->xyMainObj.hbmpsrc);
			break;
		case BUTTON_ID_1:
			std::cout << "BUTTON_ID_1" << std::endl;
			
			break;
		case BUTTON_ID_2:
			std::cout << "BUTTON_ID_2" << std::endl;
			
			break;
		case BUTTON_ID_3:
			std::cout << "BUTTON_ID_3" << std::endl;
			
			break;
		case BUTTON_ID_4:
			std::cout << "BUTTON_ID_4" << std::endl;
			
			break;
		case BUTTON_ID_5:
			std::cout << "BUTTON_ID_5" << std::endl;
			
			break;
		case BUTTON_ID_6:
			std::cout << "BUTTON_ID_6" << std::endl;
			
			break;
		case BUTTON_ID_7:
			std::cout << "BUTTON_ID_7" << std::endl;
			break;
		case BUTTON_ID_8:
			std::cout << "BUTTON_ID_8" << std::endl;
			break;
		case BUTTON_ID_9:
			std::cout << "BUTTON_ID_9" << std::endl;
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}


XYWindow::XYWindow(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
	this->wndClassName = "xydiacapclass";
	this->wndTitle = "XYDiaCap";
	this->hwnddesktop = GetDesktopWindow();
}

BOOL XYWindow::InitWindow()
{
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = wndClassName;
	CREATESTRUCT csmsg;
	csmsg.lpCreateParams = this;
	if (!RegisterClass(&wndclass))
	{
		return 0;
	}
	hwnd = CreateWindow(wndClassName,
		wndTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 300,
		NULL,
		NULL,
		hInstance,
		this
		);
	hwndbutton[0] = CreateButton(hwnd, hInstance, 0, RECT{ 1  , 1, 30 , 30 }, BUTTON_ID_0, "A");
	hwndbutton[1] = CreateButton(hwnd, hInstance, 0, RECT{ 36 , 1, 65 , 30 }, BUTTON_ID_1, "B");
	hwndbutton[2] = CreateButton(hwnd, hInstance, 0, RECT{ 71 , 1, 100, 30 }, BUTTON_ID_2, "C");
	hwndbutton[3] = CreateButton(hwnd, hInstance, 0, RECT{ 106, 1, 135, 30 }, BUTTON_ID_3, "D");
	hwndbutton[4] = CreateButton(hwnd, hInstance, 0, RECT{ 141, 1, 170, 30 }, BUTTON_ID_4, "E");
	hwndbutton[5] = CreateButton(hwnd, hInstance, 0, RECT{ 176, 1, 205, 30 }, BUTTON_ID_5, "F");
	hwndbutton[6] = CreateButton(hwnd, hInstance, 0, RECT{ 211, 1, 240, 30 }, BUTTON_ID_6, "G");
	hwndbutton[7] = CreateButton(hwnd, hInstance, 0, RECT{ 246, 1, 275, 30 }, BUTTON_ID_7, "H");
	hwndbutton[8] = CreateButton(hwnd, hInstance, 0, RECT{ 281, 1, 310, 30 }, BUTTON_ID_8, "I");
	hwndbutton[9] = CreateButton(hwnd, hInstance, 0, RECT{ 316, 1, 345, 30 }, BUTTON_ID_9, "J");
	xyDrawbox.InitDrawBox(this->hwnd,this->hInstance,this);
	return 1;
}



void XYWindow::ShowUpdate(int iCmdShow)
{
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
}

int XYWindow::MainLoop()
{
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

HWND XYWindow::CreateButton(HWND hParent,HINSTANCE hInst, DWORD dwStyle, RECT& rc, int id, char* caption)
{
	dwStyle |= WS_CHILD | WS_VISIBLE;
	return CreateWindowEx(
		0,
		TEXT("BUTTON"),
		caption,
		dwStyle,
		rc.left,
		rc.top,
		rc.right - rc.left,
		rc.bottom - rc.top,
		hParent,
		(HMENU)(id),
		hInst,
		NULL);
}
