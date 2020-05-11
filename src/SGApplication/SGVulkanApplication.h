#pragma once
#include "SGIApplication.h"
#include "SGMemoryMacros.h"

#define GLFW_INCLUDE_VULKAN
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SG
{
	class SGVulkanApplication : implements SGIApplication<SGVulkanApplication>
	{
		SG_MEMORYPOOL_DECLARATION(0);
	public:
		virtual int Initialize(int32_t w, int32_t h);
		virtual int Initialize() override;
		virtual void Finalize() override;

		virtual void Tick() override;
		virtual bool IsQuit() override;
	public:
		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		int32_t GetWindowWidth() const { return m_Width; }
		int32_t GetWindowHeight() const { return m_Height; }

	protected:
		int InitWindow();

	protected:
		GLFWwindow* m_Window = 0;
		int32_t m_Width = 1600;
		int32_t m_Height = 900;
	protected:
		VkInstance instance;
	};
}
