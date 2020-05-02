#pragma once
#include "SGIApplication.h"
#include "SGOpenGLApplication.h"
#include "SGVulkanApplication.h"

namespace SG
{
	enum AppType
	{
		OpenGLApp = 0,
		VulkanApp,
	};
	class SGApplication : implements SGIApplication<SGApplication>
	{
	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();
		virtual bool IsQuit();
	};
}
