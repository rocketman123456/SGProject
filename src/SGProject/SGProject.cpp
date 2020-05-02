// SGProject.cpp: 定义应用程序的入口点。
#include "SGProject.h"
using namespace SG;

int SGMain()
{
	int ret;
	do {
		if ((ret = g_pLog->Initialize()) != 0) { break; }
		LOG_INFO("Hello SGProject.");

		if ((ret = g_pGLApp->Initialize()) != 0) {
			LOG_ERROR("Application Initialize Failed."); break;
		}
		if ((ret = g_pTimeManager->Initialize()) != 0) {
			LOG_ERROR("TimeManager Initialize Failed."); break;
		}
		if ((ret = g_pEventManager->Initialize()) != 0) {
			LOG_ERROR("EventManager Initialize Failed."); break;
		}
		if ((ret = g_pInputManager->Initialize()) != 0) {
			LOG_ERROR("InputManager Initialize Failed."); break;
		}
		if ((ret = g_pGLGraphicsManager->Initialize()) != 0) {
			LOG_ERROR("GraphicsManager Initialize Failed."); break;
		}

		while (!g_pGLApp->IsQuit())
		{
			g_pGLApp->Tick();
			g_pTimeManager->Tick();
			g_pEventManager->Tick();
			g_pInputManager->Tick();
			g_pGLGraphicsManager->Tick();
		}

		g_pGLGraphicsManager->Finalize();
		g_pInputManager->Finalize();
		g_pEventManager->Finalize();
		g_pTimeManager->Finalize();
		g_pGLApp->Finalize();
	} while (false);

	return ret;
}
