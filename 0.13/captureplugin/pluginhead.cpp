#include "pluginhead.h"
extern "C"
{
	ppluginglobaldata gp_globaldata;
	ppluginglobalfunc gp_globalfunc;
	ppluginlocaldata  gp_localdata;

	BOOL __declspec(dllexport) RegisterPlugin(ppluginglobalfunc pplugingfunc, ppluginglobaldata pplugingdata, ppluginlocaldata ppluginldata)
	{
		gp_globaldata = pplugingdata;
		gp_globalfunc = pplugingfunc;
		gp_localdata = ppluginldata;
		return TRUE;
	}
};