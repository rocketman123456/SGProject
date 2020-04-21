// SGProject.cpp: 定义应用程序的入口点。
//
#include "SGProject.h"
using namespace SG;

int SGMain()
{
	SGLog::GetSingleton().Initialize();
	LOG_INFO("Hello SGProject.");

	int ret;
	do {
		if ((ret = g_pApp->Initialize()) != 0) 
		{
			LOG_ERROR("Application Initialize Failed.");
			break;
		}
		if ((ret = g_pEventManager->Initialize()) != 0)
		{
			LOG_ERROR("EventManager Initialize Failed.");
			break;
		}
		if ((ret = g_pGraphicsManager->Initialize()) != 0)
		{
			LOG_ERROR("GraphicsManager Initialize Failed.");
			break;
		}

		while (!g_pApp->IsQuit())
		{
			g_pApp->Tick();
			g_pEventManager->Tick();
			g_pGraphicsManager->Tick();
		}

		g_pGraphicsManager->Finalize();
		g_pEventManager->Finalize();
		g_pApp->Finalize();
	} while (false);

	return ret;
}
