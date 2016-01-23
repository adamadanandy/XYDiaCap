#ifndef XYCAP_H
#define XYCAP_H

class XYCap
{
public:
	HWND hwndDesktop;
	HDC hdcCompatible;
	HDC hdcDesktop;
	HBITMAP hbmpCompatibleDesktop;
	HBITMAP hbmptar;
	BITMAP bmpCompatible;
	BITMAP bmptar;
	HGDIOBJ hgdiCompatible;
	HGDIOBJ hgditar;
	int desktopWidth;
	int desktopHeight;
	int width;
	int height;
	unsigned char* figdata;
public:
	BOOL SetScreenData();
	BOOL GetScreenHDC();
	BOOL HDCtoBMP();
	BOOL SaveBMP();
	//BOOL CopyBMP(BITMAP& tbmp, BITMAP& sbmp);
	BOOL ReleaseObj(HBITMAP& thbmp);
};

#endif//XYCAP_H
