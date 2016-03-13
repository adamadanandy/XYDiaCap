#include "xyplugin.h"
#include <string>

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

XYPlugin::XYPlugin() : pluginhead(NULL), pluginnum(0)
{
	pluginAPIContainer.structsize = sizeof(putilfunc);
}

BOOL XYPlugin::AddPlugin(char* pluginname)
{
	std::string filename(pluginname);
	HMODULE hdll;
	NodePrivate *pcache;
	if (strlen(pluginname) > 28)
	{
		std::cout << "Too Long Plugin Name!" << std::endl;
		return FALSE;
	}
	filename = filename + ".dll";
	hdll = LoadLibrary(filename.c_str());
	if (!hdll)
	{
		return FALSE;
	}
	pcache = new NodePrivate;
	if (this->pluginnum == 0)
	{
		this->pluginhead = pcache;
		pcache->next = pcache;
		pcache->last = pcache;
	}
	else
	{
		pcache->next = this->pluginhead;
		pcache->last = this->pluginhead->last;
		this->pluginhead->last->next = pcache;
		this->pluginhead->last = pcache;
	}
	this->pluginnum++;
	
	strcpy(pcache->data.pluginname,pluginname);
	pcache->data.hmoduledll = hdll;
	pcache->data.funcRegisterPlugin = (funcregisterplugin)GetProcAddress(hdll, "RegisterPlugin");
	if (pcache->data.funcRegisterPlugin == 0)
	{
		std::cout << "can't find RegisterPlugin function" << std::endl;
		return FALSE;
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
	pcache->data.funcRegisterPlugin(&this->pluginDataContainer, &this->pluginAPIContainer, &pcache->data.plugintype);
	//ASSERT(data.type(Filled))
	//TODO::make button if necessary
	//TODO::register a private message number
	return TRUE;
}