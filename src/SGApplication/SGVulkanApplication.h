#pragma once
#include "SGIApplication.h"
#include "SGMemoryMacros.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SG
{
	class SGVulkanApplication : implements SGIApplication
	{
		SG_MEMORYPOOL_DECLARATION(0);
	public:
		int Initialize(int32_t w, int32_t h);
		virtual int Initialize() override;
		virtual void Finalize() override;

		virtual void Tick() override;
		virtual bool IsQuit() override;
	public:
		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		int32_t GetWindowWidth() const { return m_Width; }
		int32_t GetWindowHeight() const { return m_Height; }

	protected:
		GLFWwindow* m_Window = 0;
		int32_t m_Width = 1600;
		int32_t m_Height = 900;
	};
}
