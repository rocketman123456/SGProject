// SGProject.cpp: 定义应用程序的入口点。
//
#include "SGProject.h"

namespace SG
{
	extern SGIApplication* g_pApp;
}

using namespace SG;

int SGMain()
{
	SGLog::GetSingleton().Initialize();
	LOG_DEBUG("Hello SGProject.")

	int ret;
	do {
		if ((ret = g_pApp->Initialize()) != 0) 
		{
			printf("Application Initialize Failed.");
			break;
		}

		while (!g_pApp->IsQuit())
		{
			g_pApp->Tick();
		}

		g_pApp->Finalize();
	} while (false);

	return ret;
}
