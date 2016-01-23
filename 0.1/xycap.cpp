#include <Windows.h>
#include <iostream>
#include <fstream>
#include "xycap.h"

BOOL XYCap::SetScreenData()
{
	desktopWidth = GetSystemMetrics(SM_CXSCREEN);
	desktopHeight = GetSystemMetrics(SM_CYSCREEN);
	std::cout << "desktopWidth=" << desktopWidth << std::endl;
	std::cout << "desktopHeight=" << desktopHeight << std::endl;
	return TRUE;
}
BOOL XYCap::GetScreenHDC()
{
	hwndDesktop = GetDesktopWindow();
	hdcDesktop = GetDC(hwndDesktop);
	hdcCompatible = CreateCompatibleDC(hdcDesktop);
	std::cout << "hwndDesktop=" << hwndDesktop << std::endl;
	std::cout << "hdcDesktop=" << hdcDesktop << std::endl;
	std::cout << "hdcCompatible=" << hdcCompatible << std::endl;
	return TRUE;
}
BOOL XYCap::HDCtoBMP()
{
	hbmpCompatibleDesktop = CreateCompatibleBitmap(hdcDesktop, desktopWidth, desktopHeight);
	hgdiCompatible = SelectObject(hdcCompatible, hbmpCompatibleDesktop);
	BitBlt(hdcCompatible, 0, 0, desktopWidth, desktopHeight, hdcDesktop, 0, 0, SRCCOPY);
	SelectObject(hdcCompatible, hgdiCompatible);
	GetObject(hbmpCompatibleDesktop, sizeof(BITMAP), &(bmpCompatible));
	std::cout << "hbmpCompatibleDesktop{" << "\nbmType=" << bmpCompatible.bmType;
	std::cout << "\nbmHeight=" << bmpCompatible.bmHeight;
	std::cout << "\nbmWidth=" << bmpCompatible.bmWidth;
	std::cout << "\nbmWidthBytes=" << bmpCompatible.bmWidthBytes;
	std::cout << "\nbmPlanes=" << bmpCompatible.bmPlanes;
	std::cout << "\nbmBitsPixel=" << bmpCompatible.bmBitsPixel;
	std::cout << "\nbmBits=" << bmpCompatible.bmBits << "\n}" << std::endl;
	DeleteObject(&bmpCompatible);
	std::cout << "hbmpCompatibleDesktop{" << "\nbmType=" << bmpCompatible.bmType;
	std::cout << "\nbmHeight=" << bmpCompatible.bmHeight;
	std::cout << "\nbmWidth=" << bmpCompatible.bmWidth;
	std::cout << "\nbmWidthBytes=" << bmpCompatible.bmWidthBytes;
	std::cout << "\nbmPlanes=" << bmpCompatible.bmPlanes;
	std::cout << "\nbmBitsPixel=" << bmpCompatible.bmBitsPixel;
	std::cout << "\nbmBits=" << bmpCompatible.bmBits << "\n}" << std::endl;
	return TRUE;
}
//BOOL XYCap::CopyBMP(BITMAP& tbmp, BITMAP& sbmp)
//{
//	tbmp.bmType = sbmp.bmType;
//	tbmp.bmHeight = sbmp.bmHeight;
//	tbmp.bmWidthBytes = sbmp.bmWidthBytes;
//	tbmp.bmPlanes = sbmp.bmPlanes;
//	tbmp.bmBitsPixel = sbmp.bmBitsPixel;
//	tbmp.bmBits = malloc(sbmp.bmHeight*sbmp.bmWidthBytes);
//	//memcpy(tbmp.bmBits, sbmp.bmBits, sbmp.bmHeight*sbmp.bmWidthBytes);
//	std::cout << "thbmp={" << std::endl;
//	std::cout << "bmType" << tbmp.bmType << std::endl;
//	std::cout << "bmHeight" << tbmp.bmHeight << std::endl;
//	std::cout << "bmWidthBytes" << tbmp.bmWidthBytes << std::endl;
//	std::cout << "bmPlanes" << tbmp.bmPlanes << std::endl;
//	std::cout << "bmBitsPixel" << tbmp.bmBitsPixel << std::endl;
//	std::cout << "sizeof(bmBits)" << sizeof(sbmp.bmBits) << std::endl;
//
//	return TRUE;
//}
BOOL XYCap::ReleaseObj(HBITMAP& thbmp)
{
	return DeleteObject(thbmp);
}
BOOL XYCap::SaveBMP()
{
	BITMAPINFO bi;
	figdata = (unsigned char*)malloc(desktopHeight*desktopWidth*32);
	ZeroMemory(figdata, desktopHeight*desktopWidth * 4);
	ZeroMemory(&bi.bmiHeader, sizeof(BITMAPINFO));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = bmpCompatible.bmWidth;
	bi.bmiHeader.biHeight = bmpCompatible.bmHeight;
	bi.bmiHeader.biPlanes = bmpCompatible.bmPlanes;
	bi.bmiHeader.biBitCount = bmpCompatible.bmBitsPixel;
	bi.bmiHeader.biCompression = BI_RGB;
	GetDIBits(hdcCompatible, hbmpCompatibleDesktop, 0, desktopHeight, figdata, &bi, DIB_RGB_COLORS);
	for (int i = 0; i < 100; i++)
	{
		printf("%x", figdata[i]);
	}
	return TRUE;
}
