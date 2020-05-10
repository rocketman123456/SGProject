// SGProject.cpp: 定义应用程序的入口点。
#include "SGProject.h"
using namespace SG;

int SGMain()
{
	int ret;
	SG::SGProject app;
	do {
		ret = app.Init();

		app.Run();
		app.Exit();
	} while (false);

	return ret;
}

int SG::SGProject::Init()
{
	int ret = 0;
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

		eventloop = std::thread(&SGProject::EventLoop, this);
		processloop = std::thread(&SGProject::ProcessLoop, this);
		fileloop = std::thread(&SGProject::FileLoop, this);

		if (eventloop.joinable()) { eventloop.detach(); }
		if (processloop.joinable()) { processloop.detach(); }
		if (fileloop.joinable()) { fileloop.detach(); }
	} while (false);
	return ret;
}

void SG::SGProject::Exit()
{
	g_pGraphicsManager->Finalize();
	g_pInputManager->Finalize();
	g_pProcessManager->Finalize();
	g_pEventManager->Finalize();
	g_pFileManager->Finalize();
	g_pApp->Finalize();
}

void SG::SGProject::Run()
{
	while (!g_pApp->IsQuit())
	{
		std::lock_guard<std::mutex> guard(m_mutex);
		m_event = m_file = m_process = true;
		m_condVar.notify_all();
		auto start = std::chrono::high_resolution_clock::now();
		g_pApp->Tick();
		g_pInputManager->Tick();
		g_pGraphicsManager->Tick();
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		auto ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
		if (ms < 20) {
			std::this_thread::sleep_for(std::chrono::microseconds(30 - ms));
		}
	}
}

void SG::SGProject::EventLoop()
{
	while (!g_pApp->IsQuit())
	{
		std::unique_lock<std::mutex> mlock(m_mutex);
		m_condVar.wait(mlock, std::bind(&SGProject::IsEventLoop, this));
		m_event = false;
		g_pEventManager->Tick();
	}
}

void SG::SGProject::ProcessLoop()
{
	while (!g_pApp->IsQuit())
	{
		std::unique_lock<std::mutex> mlock(m_mutex);
		m_condVar.wait(mlock, std::bind(&SGProject::IsProcessLoop, this));
		m_process = false;
		g_pProcessManager->Tick();
	}
}

void SG::SGProject::FileLoop()
{
	while (!g_pApp->IsQuit())
	{
		std::unique_lock<std::mutex> mlock(m_mutex);
		m_condVar.wait(mlock, std::bind(&SGProject::IsFileLoop, this));
		m_file = false;
		g_pFileManager->Tick();
	}
}
