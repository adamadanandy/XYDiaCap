#include "xydiacap.h"

XYDiaCap * pg_xydiacap;

void GetFigData(int* pw, int* ph, int* pnbits, unsigned char* pfigdata)
{
	pg_xydiacap->capture.GetFigData(pw, ph, &pfigdata);
	*pnbits = pg_xydiacap->capture.bmptar.bmBitsPixel;
}

void SetFigData (int w, int h, int nbits, unsigned char* figdata)
{
	pg_xydiacap->pXYDrawbox->PointImageData(w, h, figdata);
	pg_xydiacap->pXYDrawbox->SetupScrollBar();
	pg_xydiacap->pXYDrawbox->RefreshAllScrollBar();

	return;
}

void GetScrollData (int* pxpos, int* pypos, int* pxscale, int* pyscale)
{
	*pxpos = pg_xydiacap->pXYDrawbox->posXScroll;
	*pypos = pg_xydiacap->pXYDrawbox->posYScroll;
	*pxscale = pg_xydiacap->pXYDrawbox->lengthXScroll;
	*pyscale = pg_xydiacap->pXYDrawbox->lengthYScroll;
	return;
}

void CaptureDesktop()
{
	if (!pg_xydiacap->capture.OnCapture())
	{
		std::cout << "problem with capturing the screen" << std::endl;
	}
	else
	{
		unsigned char * figdata;
		int w, h;
		pg_xydiacap->capture.GetFigData(&w, &h, &figdata);
		pg_xydiacap->pXYDrawbox->PointImageData(w, h, figdata);
		pg_xydiacap->pXYDrawbox->SetupScrollBar();
		pg_xydiacap->pXYDrawbox->RefreshAllScrollBar();
	}
	return;
}

void EndPlugin()
{
	pg_xydiacap->pXYPlugin->ActivePluginEnd();
}

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
		pg_xydiacap->pXYPlugin->ActivePluginMove(message, wParam, lParam);
		break;
	case WM_CREATE:
		std::cout << ":D:" << "WM_CREATE" << std::endl;
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		pXYDrawbox = (XYDrawbox*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		hdc = GetDC(hwnd);
		pg_xydiacap->xyDiaCapUtilData.hdcdrawbox = hdc;
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
		pg_xydiacap->pXYPlugin->ActivePluginBeforePaint(message, wParam, lParam, &ps);
		pXYDrawbox->DisplayImage(hdc);
		pg_xydiacap->pXYPlugin->ActivePluginAfterPaint(message, wParam, lParam, &ps);
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
	case WM_LBUTTONDOWN:
		std::cout << ":LDOWN:" << std::endl;
		pg_xydiacap->pXYPlugin->ActivePluginLDown(message, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		std::cout << ":LUP:" << std::endl;
		pg_xydiacap->pXYPlugin->ActivePluginLUp(message, wParam, lParam);
		break;
	//case WM_LBUTTONDBLCLK:
	//	std::cout << ":LCC:" << std::endl;
	//	break;
	case WM_RBUTTONDOWN:
		std::cout << ":RDOWN:" << std::endl;
		pg_xydiacap->pXYPlugin->ActivePluginRDown(message, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		std::cout << ":RUP:" << std::endl;
		pg_xydiacap->pXYPlugin->ActivePluginRUp(message, wParam, lParam);
		break;
	//case WM_RBUTTONDBLCLK:
	//	std::cout << ":RCC:" << std::endl;
	//	break;
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
	static HDC				hdc;
	static HINSTANCE		hInstance;
	PAINTSTRUCT				ps;
//	int						iitr;
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
	}

	if (message == WM_COMMAND)
	{
//		for (iitr = 0; iitr < 10; iitr++)
//		{
//			if (pg_xydiacap->pXYButtons[iitr])
//			{
//				if (wParam == pg_xydiacap->pXYButtons[iitr]->btnID)
//				{
//					std::cout << "BUTTON" << iitr << ":WM_COMMAND:" << ":lParam=" << lParam << ":wParam" << wParam << std::endl;
//					pg_xydiacap->pXYButtons[0]->OnClick();
//				}
//			}
//		}
		pg_xydiacap->pXYPlugin->PluginSwitch(message, wParam, lParam);
	}
	if (pg_xydiacap->pXYPlugin != 0)
	{
		pg_xydiacap->pXYPlugin->ActivePluginPrivateMessage(message, wParam, lParam);
	}
	//for (iitr = 0; iitr < 10; iitr++)
	//{
	//	if (pg_xydiacap->pXYButtons[iitr])
	//	{
	//		if (message == pg_xydiacap->pXYButtons[0]->msgButton)
	//		{
	//			if (!pg_xydiacap->capture.OnCapture())
	//			{
	//				std::cout << "problem with capturing the screen" << std::endl;
	//			}
	//			else
	//			{
	//				unsigned char * figdata;
	//				int w, h;
	//				pg_xydiacap->capture.GetFigData(&w, &h, &figdata);
	//				pg_xydiacap->pXYDrawbox->PointImageData(w, h, figdata);
	//				pg_xydiacap->pXYDrawbox->SetupScrollBar();
	//				pg_xydiacap->pXYDrawbox->RefreshAllScrollBar();
	//			}
	//		}
	//	}
	//}
	
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
	//pXYButtons[0]->InitWnd();
	//pXYButtons[0]->SetMessageButton("blabla");
	pXYPlugin = new XYPlugin(this->pXYFrame->hwndThis, this->hInstance);
	xyDiaCapUtilFunc.pfCaptureDesktop = CaptureDesktop;
	xyDiaCapUtilFunc.pfGetFigData = GetFigData;
	xyDiaCapUtilFunc.pfGetScrollData = GetScrollData;
	xyDiaCapUtilFunc.pfSetFigData = SetFigData;
	xyDiaCapUtilFunc.pfEndPlugin = EndPlugin;
	xyDiaCapUtilFunc.structsize = sizeof(pluginglobalfunc);
	pXYPlugin->InitPluginAPI(&xyDiaCapUtilFunc);
	
	xyDiaCapUtilData.reserved = sizeof(pluginglobaldata);
	xyDiaCapUtilData.hwnddrawbox = this->pXYDrawbox->hwndThis;
	xyDiaCapUtilData.hwndframe = this->pXYFrame->hwndThis;
	xyDiaCapUtilData.hdcdrawbox = NULL;
	pXYPlugin->InitPluginGData(&xyDiaCapUtilData);
	pXYPlugin->AddPlugin("captureplugin");
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