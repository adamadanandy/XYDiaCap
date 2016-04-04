#ifndef PLUGINHEAD_H
#define PLUGINHEAD_H

#include <Windows.h>
#include <iostream>

#define PLUGIN_TYPE_BUTTON	1
#define PLUGIN_TYPE_NULL	0
#define PLUGIN_BASE			128

#define PLUGIN_BLOCK_SIZE	32

#define XYGetFigData gp_globalfunc->pfGetFigData
#define XYSetFigData gp_globalfunc->pfSetFigData
#define XYGetScorllData gp_globalfunc->pfGetScrollData
#define XYCaptureDesktop gp_globalfunc->pfCaptureDesktop
#define XYEndPlugin gp_globalfunc->pfEndPlugin

extern "C"
{
	//getfigdata(_O_int* pixelbits, _O_int* w, _O_int* h, _O_unsigned char* data)
	typedef void(*funcgetfigdata)(int*, int*, int*, unsigned char*);
	//setfigdata(_I_int pixelbits, _I_int w, _I_int h, _I_unsigned char* data)
	typedef void(*funcsetfigdata)(int, int, int, unsigned char*);
	//getscrolldata(_O_int* xpos, _O_int* ypos, _O_int* xscale, _O_int* yscale)
	typedef void(*funcgetscrolldata)(int*, int*, int*, int*);
	//capturedesktop(void);
	typedef void(*funccapturedesktop)(void);
	//endplugin(void);
	typedef void(*funcendplugin)(void);

	typedef struct tagpluginglobalfunc{
		unsigned int structsize;
		funcgetfigdata pfGetFigData;
		funcsetfigdata pfSetFigData;
		funcgetscrolldata pfGetScrollData;
		funccapturedesktop pfCaptureDesktop;
		funcendplugin pfEndPlugin;
		void* preserved;
	} pluginglobalfunc, *ppluginglobalfunc;

	typedef struct tagfigchange{
		BOOL bchangefig;
		int w;
		int h;
		int pixelbits;
		unsigned char* figdata;
	} figchange, *pfigchange;

	typedef struct tagpluginglobaldata{
		unsigned int	structsize;
		//global data
		HWND			hwndframe;
		HWND			hwnddrawbox;
		HDC				hdcdrawbox;

		int				reserved;
	} pluginglobaldata, *ppluginglobaldata;

	typedef struct tagpluginlocaldata{
		unsigned int	structsize;
		//plugin local data
		HWND			hwndplugin;
		unsigned int	pluginmsg;
		int				pluginid;

		int				reserved;
	} pluginlocaldata, *ppluginlocaldata;

	//RegisterPlugin(_I_ppluginglobalfunc pgfunc, _I_ppluginglobaldata pgdata, _I_ppluginlocaldata pldata);
	typedef BOOL(*funcregisterplugin)(ppluginglobalfunc, ppluginglobaldata, ppluginlocaldata);
	//OnLoadPlugin(_O_pfigchange pchange)
	typedef void(*funconloadplugin)(pfigchange);
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

	BOOL __declspec(dllexport) RegisterPlugin(ppluginglobalfunc pplugingfunc, ppluginglobaldata pplugingdata, ppluginlocaldata ppluginldata);

	extern ppluginglobaldata gp_globaldata;
	extern ppluginglobalfunc gp_globalfunc;
	extern ppluginlocaldata  gp_localdata;
};

#endif//PLUGINHEAD_H