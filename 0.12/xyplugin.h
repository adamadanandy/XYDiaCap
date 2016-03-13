#ifndef XYPLUGIN_H
#define XYPLUGIN_H

#include <Windows.h>
#include <iostream>

#define PLUGIN_TYPE_BUTTON	1
#define PLUGIN_TYPE_NULL	0

extern "C"
{
	//getfigdata(_O_int* pixelbits, _O_int* w, _O_int* h, _O_unsigned char* data)
	typedef void(*funcgetfigdata)(int*, int*, int*, unsigned char*);
	//setfigdata(_I_int pixelbits, _I_int w, _I_int h, _I_unsigned char* data)
	typedef void(*funcsetfigdata)(int, int, int, unsigned char*);
	//getscrollinfo(_O_int* xpos, _O_int* ypos, _O_int* xscale, _O_int* yscale)
	typedef void(*funcgetscrollinfo)(int*, int*, int*, int*);
	//capturedesktop(void);
	typedef void(*funccapturedesktop)(void);
	//endplugin(void);
	typedef void(*funcendplugin)(void);

	typedef struct tagutilfunc{
		unsigned int structsize;
		funcgetfigdata pfGetFigData;
		funcsetfigdata pfSetFigData;
		funcgetscrollinfo pfGetScrollInfo;
		funccapturedesktop pfCaptureDesktop;
		funcendplugin pfEndPlugin;
		void* preserved;
	} utilfunc,*putilfunc;

	typedef struct tagfigchange{
		BOOL bchangefig;
		int w;
		int h;
		int pixelbits;
		unsigned char* figdata;
	} figchange, *pfigchange;

	typedef struct tagutildata{
		unsigned int	structsize;
		HWND			hwndframe;
		HWND			hwnddrawbox;
		HWND			hwndmod;
		HDC				hdcdrawbox;
		unsigned int	btnmsg;
		unsigned int	privatemsg;
		int				reserved;
	} utildata, *putildata;

	//RegisterPlugin(_I_putildata pdata, _I_putilfunc pfunc, _O_int* type);
	typedef BOOL(*funcregisterplugin)(putildata, putilfunc, int*);
	//OnMouseMove(_I_LPARAM* plParam, _I_WPARAM* pwParam, _O_pfigchange pchange);
	typedef void(*funconmousemove)(LPARAM*, WPARAM*, pfigchange);
	//OnMouseLDown(_I_LPARAM* plParam, _I_WPARAM* pwParam, _O_pfigchange pchange);
	typedef void(*funconmouseldown)(LPARAM*, WPARAM*, pfigchange);
	//OnMouseRDown(_I_LPARAM* plParam, _I_WPARAM* pwParam, _O_pfigchange pchange);
	typedef void(*funconmouserdown)(LPARAM*, WPARAM*, pfigchange);
	//OnMouseLUp(_I_LPARAM* plParam, _I_WPARAM* pwParam, _O_pfigchange pchange);
	typedef void(*funconmouselup)(LPARAM*, WPARAM*, pfigchange);
	//OnMouseRUp(_I_LPARAM* plParam, _I_WPARAM* pwParam, _O_pfigchange pchange);
	typedef void(*funconmouserup)(LPARAM*, WPARAM*, pfigchange);
	//OnPaintBeforePic(_I_PAINTSTRUCT* ps);
	typedef void(*funconpaintbeforepic)(PAINTSTRUCT*);
	//OnPaintAfterPic(_I_PAINTSTRUCT* ps);
	typedef void(*funconpaintafterpic)(PAINTSTRUCT*);
	//OnPrivateMessage(LPARAM*,WPARAM*, _O_pfigchange pchange);
	typedef void(*funconprivatemessage)(LPARAM*, WPARAM*, pfigchange);
	//OnInterupted(_O_pfigchange pchange)
	typedef void(*funconinterupted)(pfigchange);

	typedef struct tagplugindata
	{
		char					pluginname[30];

		funcregisterplugin		funcRegisterPlugin;
		funconmousemove			funcOnMouseMove;
		funconmouseldown		funcOnMouseLDown;
		funconmouserdown		funcOnMouseRDown;
		funconmouselup			funcOnMouseLUp;
		funconmouserup			funcOnMouseRUp;
		funconpaintbeforepic	funcOnPaintBeforePic;
		funconpaintafterpic		funcOnPaintAfterPic;
		funconprivatemessage	funcOnPrivateMessage;
		funconinterupted		funcOnInterupted;
		HMODULE					hmoduledll;
		unsigned int			privatemsg;

		HWND					hwndplugin;
		int			plugintype;

		int						reserved;
	} plugindata, *pplugindata;
};

struct NodePrivate
{
public:
	NodePrivate *next;
	NodePrivate *last;
	plugindata data;
};

class XYPlugin
{
public:
	NodePrivate *pluginhead;
	utilfunc pluginAPIContainer;
	utildata pluginDataContainer;
	int pluginnum;
public:
	XYPlugin();
	void InitPluginAPI(utilfunc* papi);
	void InitPluginGData(utildata* pdata);
	BOOL AddPlugin(char* pluginname);
};

#endif//XYPLUGIN_H