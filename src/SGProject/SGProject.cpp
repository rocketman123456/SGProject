// SGProject.cpp: 定义应用程序的入口点。
#include "SGProject.h"
#include <thread>
#include <condition_variable>
using namespace SG;

void EventLoop()
{
	while (!g_pApp->IsQuit())
	{
		g_pEventManager->Tick();
	}
}

void ProcessLoop()
{
	while (!g_pApp->IsQuit())
	{
		g_pProcessManager->Tick();
	}
}

void FileLoop()
{
	while (!g_pApp->IsQuit())
	{
		g_pFileManager->Tick();
	}
}

int SGMain()
{
	int ret;
	do {
		if ((ret = g_pLog->Initialize()) != 0) { break; }
		LOG_INFO("SGProject Start.");

		if ((ret = g_pApp->Initialize()) != 0) {
			LOG_ERROR("Application Initialize Failed."); break;
		}
		if ((ret = g_pFileManager->Initialize()) != 0) {
			LOG_ERROR("FileManager Initialize Failed."); break;
		}
		if ((ret = g_pEventManager->Initialize()) != 0) {
			LOG_ERROR("EventManager Initialize Failed."); break;
		}
		if ((ret = g_pProcessManager->Initialize()) != 0) {
			LOG_ERROR("ProcessManager Initialize Failed."); break;
		}
		if ((ret = g_pInputManager->Initialize()) != 0) {
			LOG_ERROR("InputManager Initialize Failed."); break;
		}
		if ((ret = g_pGraphicsManager->Initialize()) != 0) {
			LOG_ERROR("GraphicsManager Initialize Failed."); break;
		}

		std::thread eventloop(EventLoop);
		std::thread processloop(ProcessLoop);
		std::thread fileloop(FileLoop);
		if (eventloop.joinable()) { eventloop.detach(); }
		if (processloop.joinable()) { processloop.detach(); }
		if (fileloop.joinable()) { fileloop.detach(); }

		while (!g_pApp->IsQuit())
		{
			auto start = std::chrono::high_resolution_clock::now();
			g_pApp->Tick();
			g_pInputManager->Tick();
			g_pGraphicsManager->Tick();
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			auto ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			if (ms < 30) {
				std::this_thread::sleep_for(std::chrono::microseconds(30 - ms));
			}
		}

		g_pGraphicsManager->Finalize();
		g_pInputManager->Finalize();
		g_pProcessManager->Finalize();
		g_pEventManager->Finalize();
		g_pFileManager->Finalize();
		g_pApp->Finalize();
	} while (false);

	return ret;
}
