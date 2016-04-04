#include "pluginhead.h"

extern "C" {
	void __declspec(dllexport) OnLoadPlugin(pfigchange pfc)
	{
		XYCaptureDesktop();
		XYEndPlugin();
		pfc->bchangefig = TRUE;
	}
};