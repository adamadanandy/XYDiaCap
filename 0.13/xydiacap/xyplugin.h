#ifndef XYPLUGIN_H
#define XYPLUGIN_H
#include "xybutton.h"
#include <Windows.h>
#include <iostream>

#define PLUGIN_TYPE_BUTTON	1
#define PLUGIN_TYPE_NULL	0
#define PLUGIN_BASE			128

#define PLUGIN_BLOCK_SIZE	32

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
	} pluginglobalfunc,*ppluginglobalfunc;

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

	typedef struct tagplugindata
	{
		char					pluginname[30];

		funcregisterplugin		funcRegisterPlugin;
		funconloadplugin		funcOnLoadPlugin;
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
		unsigned int			pluginmsg;
		int						pluginid;
		pluginlocaldata			pluginldata;

		HWND					hwndplugin;
		int						plugintype;

		XYButton				*pBtnPlugin;

		int						reserved;
	} plugindata, *pplugindata;
};

struct NodePlugin
{
public:
	NodePlugin *next;
	NodePlugin *last;
	plugindata data;
};

class XYPlugin
{
public:
	NodePlugin *pluginhead;
	ppluginglobalfunc ppluginAPIContainer;
	ppluginglobaldata ppluginDataContainer;
	HWND hwndParent;
	HINSTANCE hInstance;
	int pluginnum;
	int activePluginInd;

	NodePlugin** sortedPluginArrayPtr;
	int sortedPluginArrayPtrSize;
	void PrivateAddPluginNode(NodePlugin* newnode);
public:
	XYPlugin(HWND hwndp, HINSTANCE hinst);
	void InitPluginAPI(pluginglobalfunc *papi);
	void InitPluginGData(pluginglobaldata *pdata);
	NodePlugin *AddPlugin(char* pluginname);

	void PluginSwitch(UINT message, WPARAM wParam, LPARAM lParam);
	void ActivePluginPrivateMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void ActivePluginLDown(UINT message, WPARAM wParam, LPARAM lParam);
	void ActivePluginRDown(UINT message, WPARAM wParam, LPARAM lParam);
	void ActivePluginLUp(UINT message, WPARAM wParam, LPARAM lParam);
	void ActivePluginRUp(UINT message, WPARAM wParam, LPARAM lParam);
	void ActivePluginMove(UINT message, WPARAM wParam, LPARAM lParam);
	void ActivePluginBeforePaint(UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* pps);
	void ActivePluginAfterPaint(UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* pps);
	void ActivePluginEnd();
};

#endif//XYPLUGIN_H