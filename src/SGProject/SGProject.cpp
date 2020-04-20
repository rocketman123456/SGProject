// SGProject.cpp: 定义应用程序的入口点。
//
#include "SGProject.h"

namespace SG
{
	extern SGIApplication* g_pApp;
}

int SGMain()
{
	printf("Hello SGProject.");
	int ret;

	do {
		if ((ret = SG::g_pApp->Initialize()) != 0) 
		{
			printf("Application Initialize Failed.");
			break;
		}

		while (!SG::g_pApp->IsQuit())
		{
			SG::g_pApp->Tick();
		}

		SG::g_pApp->Finalize();
	} while (false);

	return ret;
}
