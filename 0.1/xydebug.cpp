#include "xydebug.h"
#include <Windows.h>
#include <iostream>

bool XYDebug::OpenConsole()
{
	FreeConsole();
	if (AllocConsole() == 0) return false;
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
	if (freopen("CONIN$", "rt", stdin) == 0) return false;
	if (freopen("CONOUT$", "wt", stdout) == 0) return false;
	if (freopen("CONOUT$", "wt", stderr) == 0) return false;
	SetConsoleTitle("XYDebug Debug Colsole");
	return true;
}
