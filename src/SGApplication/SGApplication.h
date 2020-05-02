#pragma once
#include "SGIApplication.h"
#include "SGOpenGLApplication.h"
#include "SGVulkanApplication.h"
#include "SGConfig.h"

namespace SG
{
	extern SGIApplication<SGOpenGLApplication>* g_pGLApp;
	extern SGIApplication<SGVulkanApplication>* g_pVKApp;
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
	public:
		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		int32_t GetWindowWidth() const { return m_Width; }
		int32_t GetWindowHeight() const { return m_Height; }

	protected:
		AppType m_Type;
		GLFWwindow* m_Window = nullptr;
		int32_t m_Width = 1600;
		int32_t m_Height = 900;
	};
}
