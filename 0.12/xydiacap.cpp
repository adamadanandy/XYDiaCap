#include "xydiacap.h"

XYDiaCap * pg_xydiacap;

LRESULT CALLBACK WndProcFrame(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC            hdc;
	static HINSTANCE      hInstance;
	RECT crect;
	PAINTSTRUCT    ps;
	switch (message)
	{
	case WM_MOUSEMOVE:
		//std::cout << "(" << LOWORD(lParam) <<","<< HIWORD(lParam) << ")" << std::endl;
		break;
	//case WM_MOUSEWHEEL:
	//	std::cout << "WM_MOUSEWHEEL_PARENT" << std::endl;
	//	break;
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		//pXYWindow = (XYWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);

		break;
	case WM_SIZE:
		std::cout << "\\" << LOWORD(lParam) << "," << HIWORD(lParam) << "\\" << std::endl;
		SetWindowPos(pg_xydiacap->pXYDrawbox->hwndThis, NULL, 0, 35, LOWORD(lParam), HIWORD(lParam) - 35, SWP_NOZORDER);
		//SetWindowPos(xydbtst->hwndThis, NULL, 0, 35, LOWORD(lParam), HIWORD(lParam) - 35, SWP_NOZORDER);
		//GetClientRect(pXYWindow->hwnd, &crect);
		//std::cout << "\\l" << crect.left << "\\r" << crect.right << "\\t" << crect.top << "\\b" << crect.bottom << std::endl;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case 33323:
		if (!pg_xydiacap->capture.OnCapture())
		{
			std::cout << "problem with capturing the screen" << std::endl;
			break;
		}
		unsigned char * figdata;
		int w, h;
		pg_xydiacap->capture.GetFigData(&w, &h, &figdata);
		pg_xydiacap->pXYDrawbox->PointImageData(w, h, figdata);
		pg_xydiacap->pXYDrawbox->SetupScrollBar();
		pg_xydiacap->pXYDrawbox->RefreshAllScrollBar();
	}
	if (pg_xydiacap->pXYButtons[0])
	{
		if (message == WM_COMMAND)
		{
			pg_xydiacap->pXYButtons[0]->WndProcFunction(wParam);
		}
		pg_xydiacap->pXYButtons[0]->ClickFunction(message);
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

XYDiaCap::XYDiaCap(HINSTANCE hinst) : hInstance(hinst)
{
	pXYFrame = new XYFrame(hinst);
	pXYFrame->SetWndProc(WndProcFrame);
	pXYFrame->SetWndProclpParam(this);
	

}

BOOL XYDiaCap::InitWindows()
{
	pXYFrame->InitWnd();
	pXYDrawbox = new XYDrawbox(pXYFrame->hwndThis, hInstance, 0, 35, 10, 10);
	pXYButtons[0] = new XYButton(pXYFrame->hwndThis, hInstance, 1, 1, 30, 30, "btn0", 323);
	pXYDrawbox->InitWnd();
	pXYButtons[0]->InitWnd();
	pXYButtons[0]->SetMessageButton("blabla");
	return TRUE;
}

void XYDiaCap::ShowUpdate(int iCmdShow)
{
	pXYFrame->ShowUpdate(iCmdShow);
}

int XYDiaCap::MainLoop()
{
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}