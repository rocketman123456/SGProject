// SGProject.h: 标准系统包含文件的包含文件
#pragma once
#include "SGDefine.h"
#include "SGModules.h"
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>



namespace SG
{
	class SGProject
	{
	public:
		int Init();
		void Run();
		void Exit();
	protected:
		void FileLoop();
		void EventLoop();
		void ProcessLoop();

		inline bool IsEventLoop() { return m_event; }
		inline bool IsProcessLoop() { return m_process; }
		inline bool IsFileLoop() { return m_file; }

		bool m_file = false;
		bool m_event = false;
		bool m_process = false;

		std::mutex m_mutex;
		std::condition_variable m_condVar;
		std::thread eventloop;
		std::thread processloop;
		std::thread fileloop;
	};
}