#include "xyplugin.h"

#include <string>
void DefaultOnLoadPlugin(pfigchange pchange)
{
	if (!pchange)
	{
		pchange->bchangefig = FALSE;
	}
	return;
}
void DefaultOnMouseMove(LPARAM* plParam, WPARAM* pwParam, pfigchange pchange)
{
	if (!pchange)
	{
		pchange->bchangefig = FALSE;
	}
	return;
}

void DefaultOnMouseLDown(LPARAM* plParam, WPARAM* pwParam, pfigchange pchange)
{
	if (!pchange)
	{
		pchange->bchangefig = FALSE;
	}
	return;
}

void DefaultOnMouseRDown(LPARAM* plParam, WPARAM* pwParam, pfigchange pchange)
{
	if (!pchange)
	{
		pchange->bchangefig = FALSE;
	}
	return;
}

void DefaultOnMouseLUp(LPARAM* plParam, WPARAM* pwParam, pfigchange pchange)
{
	if (!pchange)
	{
		pchange->bchangefig = FALSE;
	}
	return;
}

void DefaultOnMouseRUp(LPARAM* plParam, WPARAM* pwParam, pfigchange pchange)
{
	if (!pchange)
	{
		pchange->bchangefig = FALSE;
	}
	return;
}

void DefaultOnPaintBeforePic(PAINTSTRUCT* ps)
{
	return;
}

void DefaultOnPaintAfterPic(PAINTSTRUCT* ps)
{
	return;
}

void DefaultOnPrivateMessage(LPARAM* plParam, WPARAM* pwParam, pfigchange pchange)
{
	if (!pchange)
	{
		pchange->bchangefig = FALSE;
	}
	return;
}

void DefaultOnInterupted(pfigchange pchange)
{
	if (!pchange)
	{
		pchange->bchangefig = FALSE;
	}
	return;
}

//void EndPlugin()
//{
//	std::cout << "Plugin Ended" << std::endl;
//}

XYPlugin::XYPlugin(HWND hwndp, HINSTANCE hinst) : pluginhead(NULL), pluginnum(0),
	hwndParent(hwndp), hInstance(hinst),
	ppluginAPIContainer(NULL), ppluginDataContainer(NULL),
	activePluginInd(-1)
{
	sortedPluginArrayPtr = new NodePlugin*[PLUGIN_BLOCK_SIZE];
	ZeroMemory(sortedPluginArrayPtr, sizeof(NodePlugin*)*PLUGIN_BLOCK_SIZE);
	sortedPluginArrayPtrSize = PLUGIN_BLOCK_SIZE;
}
void XYPlugin::PrivateAddPluginNode(NodePlugin* pnewnode)
{
	int i;
	if (this->pluginnum == 0)
	{
		this->pluginhead = pnewnode;
		pnewnode->next = pnewnode;
		pnewnode->last = pnewnode;
	}
	else
	{
		pnewnode->next = this->pluginhead;
		pnewnode->last = this->pluginhead->last;
		this->pluginhead->last->next = pnewnode;
		this->pluginhead->last = pnewnode;
	}
	if (this->pluginnum == this->sortedPluginArrayPtrSize)
	{
		//reallocate sortedPluginArrayPtr
		NodePlugin** cachePtrPtr = new NodePlugin*[this->sortedPluginArrayPtrSize + PLUGIN_BLOCK_SIZE];
		for (i = 0; i < this->sortedPluginArrayPtrSize; i++)
		{
			cachePtrPtr[i] = this->sortedPluginArrayPtr[i];
		}
		delete this->sortedPluginArrayPtr;
		this->sortedPluginArrayPtr = cachePtrPtr;
		this->sortedPluginArrayPtrSize += PLUGIN_BLOCK_SIZE;
	}
	this->sortedPluginArrayPtr[this->pluginnum] = pnewnode;
	this->pluginnum++;

}
void XYPlugin::InitPluginAPI(pluginglobalfunc* papi)
{
	this->ppluginAPIContainer = papi;
}

void XYPlugin::InitPluginGData(pluginglobaldata* pdata)
{
	this->ppluginDataContainer = pdata;	
}

NodePlugin* XYPlugin::AddPlugin(char* pluginname)
{
	std::string filename(pluginname);
	HMODULE hdll;
	NodePlugin *pcache;
	if (strlen(pluginname) > 28)
	{
		std::cout << "Too Long Plugin Name!" << std::endl;
		return NULL;
	}
	filename = filename + ".dll";
	hdll = LoadLibrary(filename.c_str());
	if (!hdll)
	{
		return NULL;
	}
	pcache = new NodePlugin;
	
	strcpy(pcache->data.pluginname,pluginname);
	pcache->data.hmoduledll = hdll;
	pcache->data.funcRegisterPlugin = (funcregisterplugin)GetProcAddress(hdll, "RegisterPlugin");
	if (pcache->data.funcRegisterPlugin == 0)
	{
		std::cout << "can't find RegisterPlugin function" << std::endl;
		delete pcache;
		return NULL;
	}

	this->PrivateAddPluginNode(pcache);

	pcache->data.funcOnLoadPlugin = (funconloadplugin)GetProcAddress(hdll, "OnLoadPlugin");
	if (pcache->data.funcOnLoadPlugin == 0)
	{
		pcache->data.funcOnLoadPlugin = DefaultOnLoadPlugin;
	}

	pcache->data.funcOnMouseMove = (funconmousemove)GetProcAddress(hdll, "OnMouseMove");
	if (pcache->data.funcOnMouseMove == 0)
	{
		pcache->data.funcOnMouseMove = DefaultOnMouseMove;
	}

	pcache->data.funcOnMouseLDown = (funconmouseldown)GetProcAddress(hdll, "OnMouseLDown");
	if (pcache->data.funcOnMouseLDown == 0)
	{
		pcache->data.funcOnMouseLDown = DefaultOnMouseLDown;
	}

	pcache->data.funcOnMouseRDown = (funconmouserdown)GetProcAddress(hdll, "OnMouseRDown");
	if (pcache->data.funcOnMouseRDown == 0)
	{
		pcache->data.funcOnMouseRDown = DefaultOnMouseRDown;
	}

	pcache->data.funcOnMouseLUp = (funconmouselup)GetProcAddress(hdll, "OnMouseLUp");
	if (pcache->data.funcOnMouseLUp == 0)
	{
		pcache->data.funcOnMouseLUp = DefaultOnMouseLUp;
	}

	pcache->data.funcOnMouseRUp = (funconmouserup)GetProcAddress(hdll, "OnMouseRUp");
	if (pcache->data.funcOnMouseRUp == 0)
	{
		pcache->data.funcOnMouseRUp = DefaultOnMouseRUp;
	}

	pcache->data.funcOnPaintAfterPic = (funconpaintafterpic)GetProcAddress(hdll, "OnPaintAfterPic");
	if (pcache->data.funcOnPaintAfterPic == 0)
	{
		pcache->data.funcOnPaintAfterPic = DefaultOnPaintAfterPic;
	}

	pcache->data.funcOnPaintBeforePic = (funconpaintbeforepic)GetProcAddress(hdll, "OnPaintBeforePic");
	if (pcache->data.funcOnPaintBeforePic == 0)
	{
		pcache->data.funcOnPaintBeforePic = DefaultOnPaintBeforePic;
	}

	pcache->data.funcOnPrivateMessage = (funconprivatemessage)GetProcAddress(hdll, "OnPrivateMessage");
	if (pcache->data.funcOnPrivateMessage == 0)
	{
		pcache->data.funcOnPrivateMessage = DefaultOnPrivateMessage;
	}

	pcache->data.funcOnInterupted = (funconinterupted)GetProcAddress(hdll, "OnInterupted");
	if (pcache->data.funcOnInterupted == 0)
	{
		pcache->data.funcOnInterupted = DefaultOnInterupted;
	}
	//ASSERT(pluginDataContainer(Filled),pluginAPIContainer(Filled),data->type(NOTFilled),data->hwnd(NOTFilled)
	pcache->data.pBtnPlugin = new XYButton(this->hwndParent, this->hInstance, this->pluginnum * 35, 0, 30, 30, pluginname, PLUGIN_BASE + this->pluginnum);
	pcache->data.hwndplugin = pcache->data.pBtnPlugin->hwndThis;
	pcache->data.pBtnPlugin->InitWnd();
	pcache->data.pBtnPlugin->SetMessageButton(pluginname);
	pcache->data.pluginmsg = pcache->data.pBtnPlugin->msgButton;
	pcache->data.pluginid = PLUGIN_BASE + this->pluginnum - 1;
	pcache->data.pluginldata.hwndplugin = pcache->data.hwndplugin;
	pcache->data.pluginldata.pluginid = pcache->data.pluginid;
	pcache->data.pluginldata.pluginmsg = pcache->data.pluginmsg;
	pcache->data.pluginldata.structsize = sizeof(pluginlocaldata);
 
	pcache->data.funcRegisterPlugin(this->ppluginAPIContainer,this->ppluginDataContainer,&(pcache->data.pluginldata));
	
	return pcache;
}


void XYPlugin::PluginSwitch(UINT message, WPARAM wParam, LPARAM lParam)
{
	int i;
	figchange cacheFigChangeTag;
	ZeroMemory(&cacheFigChangeTag, sizeof(figchange));
	for (i = 0; i < this->pluginnum; i++)
	{
		if (this->sortedPluginArrayPtr[i]->data.pluginid == wParam)
		{
			//interrupt -> Search and Interrupt
			if (this->activePluginInd != -1)
			{
				this->sortedPluginArrayPtr[this->activePluginInd]->data.funcOnInterupted(&cacheFigChangeTag);
			}
			this->sortedPluginArrayPtr[i]->data.funcOnLoadPlugin(&cacheFigChangeTag);
			//TODO autoallocate array -> activePluginInd->arrayindex
			this->activePluginInd = this->sortedPluginArrayPtr[i]->data.pluginid - PLUGIN_BASE;
			//ASSERT(this->sortedPluginArrayPtr[this->activePluginInd] == pCacheNode)
			break;
		}
	}
}

void XYPlugin::ActivePluginPrivateMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	figchange cachefigchange;
	if (this->activePluginInd == -1)
	{
		return;
	}
	
	this->sortedPluginArrayPtr[this->activePluginInd]->data.funcOnPrivateMessage(&lParam, &wParam, &cachefigchange);
}

void XYPlugin::ActivePluginLDown(UINT message, WPARAM wParam, LPARAM lParam)
{
	figchange cachefigchange;
	if (this->activePluginInd == -1)
	{
		return;
	}

	this->sortedPluginArrayPtr[this->activePluginInd]->data.funcOnMouseLDown(&lParam, &wParam, &cachefigchange);
}
void XYPlugin::ActivePluginRDown(UINT message, WPARAM wParam, LPARAM lParam)
{
	figchange cachefigchange;
	if (this->activePluginInd == -1)
	{
		return;
	}

	this->sortedPluginArrayPtr[this->activePluginInd]->data.funcOnMouseRDown(&lParam, &wParam, &cachefigchange);
}
void XYPlugin::ActivePluginLUp(UINT message, WPARAM wParam, LPARAM lParam)
{
	figchange cachefigchange;
	if (this->activePluginInd == -1)
	{
		return;
	}

	this->sortedPluginArrayPtr[this->activePluginInd]->data.funcOnMouseLUp(&lParam, &wParam, &cachefigchange);
}
void XYPlugin::ActivePluginRUp(UINT message, WPARAM wParam, LPARAM lParam)
{
	figchange cachefigchange;
	if (this->activePluginInd == -1)
	{
		return;
	}

	this->sortedPluginArrayPtr[this->activePluginInd]->data.funcOnMouseRUp(&lParam, &wParam, &cachefigchange);
}
void XYPlugin::ActivePluginMove(UINT message, WPARAM wParam, LPARAM lParam)
{
	figchange cachefigchange;
	if (this->activePluginInd == -1)
	{
		return;
	}

	this->sortedPluginArrayPtr[this->activePluginInd]->data.funcOnMouseMove(&lParam, &wParam, &cachefigchange);
}
void XYPlugin::ActivePluginBeforePaint(UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* pps)
{
	if (this->activePluginInd == -1)
	{
		return;
	}

	this->sortedPluginArrayPtr[this->activePluginInd]->data.funcOnPaintBeforePic(pps);
}
void XYPlugin::ActivePluginAfterPaint(UINT message, WPARAM wParam, LPARAM lParam, PAINTSTRUCT* pps)
{
	if (this->activePluginInd == -1)
	{
		return;
	}

	this->sortedPluginArrayPtr[this->activePluginInd]->data.funcOnPaintAfterPic(pps);
}

void XYPlugin::ActivePluginEnd()
{
	if (this->activePluginInd < 0)
	{
		std::cout << "Warning Nothing Loaded And Now Something End A Plugin!!!" << std::endl;
	}
	this->activePluginInd = -1;
}