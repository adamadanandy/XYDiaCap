#include "xydiacap.h"

XYDiaCap * pg_xydiacap;

LRESULT CALLBACK WndProcDrawbox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC            hdc;
	static HINSTANCE      hInstance;
	static XYDrawbox      *pXYDrawbox;
	static RECT           rc;
	static PAINTSTRUCT    ps;
	static HDC            cachehdc;
	switch (message)
	{
	case WM_MOUSEMOVE:
		std::cout << "<D>" << LOWORD(lParam) << "," << HIWORD(lParam) << "<D>" << std::endl;
		rc.left = LOWORD(lParam) - 5;
		rc.right = rc.left + 10;
		rc.top = HIWORD(lParam) - 5;
		rc.bottom = rc.top + 10;
		InvalidateRect(hwnd, &rc, TRUE);
		break;
	case WM_CREATE:
		std::cout << ":D:" << "WM_CREATE" << std::endl;
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		pXYDrawbox = (XYDrawbox*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		hdc = GetDC(hwnd);
		break;
	case WM_SIZE:
		std::cout << "\\D\\" << LOWORD(lParam) << "," << HIWORD(lParam) << "/D/" << std::endl;
		pXYDrawbox->SetWndSize(LOWORD(lParam), HIWORD(lParam));
		pXYDrawbox->SetupScrollBar();
		pXYDrawbox->RefreshAllScrollBar();
		break;
	case WM_PAINT:
		std::cout << ":D:" << "WM_PAINT" << std::endl;
		cachehdc = BeginPaint(hwnd, &ps);
		pXYDrawbox->DisplayImage(hdc);
		HPEN hpen;
		hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(hdc, hpen);
		MoveToEx(hdc, rc.left + 1, rc.top + 5, NULL);
		LineTo(hdc, rc.right - 1, rc.top + 5);
		EndPaint(hwnd, &ps);
		std::cout << "cachehdc::" << cachehdc << "hdc::" << hdc << std::endl;
		std::cout << "PAINTSTRUCT{" << "\nfEarse=" << ps.fErase << "\nfIncUpdate=" << ps.fIncUpdate << "\nrcPaint={" << ps.rcPaint.bottom << "," << ps.rcPaint.top << "," << ps.rcPaint.left << "," << ps.rcPaint.right << "}" << "\nhdc=" << ps.hdc << "\n}" << std::endl;
		break;
	case WM_DESTROY:
		std::cout << ":D:" << "WM_DESTROY" << std::endl;
		PostQuitMessage(0);
		break;
	case WM_MOUSEWHEEL:
		std::cout << ":D:" << "WM_MOUSE_WHEEL" << std::endl;
		break;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			pXYDrawbox->posYScroll -= pXYDrawbox->lengthYPage / 4;
			break;
		case SB_LINERIGHT:
			pXYDrawbox->posYScroll += pXYDrawbox->lengthYPage / 4;
			break;
		case SB_PAGELEFT:
			pXYDrawbox->posYScroll -= pXYDrawbox->lengthYPage;
			break;
		case SB_PAGERIGHT:
			pXYDrawbox->posYScroll += pXYDrawbox->lengthYPage;
			break;
		case SB_THUMBTRACK:
			pXYDrawbox->GetYScrollTrackPos();
			pXYDrawbox->posYScroll = pXYDrawbox->scrollinfo.nTrackPos;
			break;
		}
		pXYDrawbox->RefreshYPosScrollBar();
		InvalidateRect(hwnd, 0, TRUE);
		std::cout << ":D:" << pXYDrawbox->posXScroll << "," << pXYDrawbox->posYScroll << ":D:" << std::endl;
		break;
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			pXYDrawbox->posXScroll -= pXYDrawbox->lengthXPage / 4;
			break;
		case SB_LINERIGHT:
			pXYDrawbox->posXScroll += pXYDrawbox->lengthXPage / 4;
			break;
		case SB_PAGELEFT:
			pXYDrawbox->posXScroll -= pXYDrawbox->lengthXPage;
			break;
		case SB_PAGERIGHT:
			pXYDrawbox->posXScroll += pXYDrawbox->lengthXPage;
			break;
		case SB_THUMBTRACK:
			pXYDrawbox->GetXScrollTrackPos();
			pXYDrawbox->posXScroll = pXYDrawbox->scrollinfo.nTrackPos;
			break;
		}
		pXYDrawbox->RefreshXPosScrollBar();
		InvalidateRect(hwnd, 0, TRUE);
		std::cout << ":D:" << pXYDrawbox->posXScroll << "," << pXYDrawbox->posYScroll << ":D:" << std::endl;
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

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
	pXYDrawbox->SetWndProc(WndProcDrawbox);
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