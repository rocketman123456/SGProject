#pragma once
#include "SGIApplication.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SG
{
	class SGBaseApplication : implements SGIApplication {
	public:
		int Initialize(int32_t w, int32_t h);
		virtual int Initialize() override;
		virtual void Finalize() override;

		virtual void Tick() override;
		virtual bool IsQuit() override;
	public:
		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		int32_t GetWindowWidth() const { return m_Witdh; }
		int32_t GetWindowHeight() const { return m_Height; }

	protected:
		GLFWwindow* m_Window;
		int32_t m_Witdh = 1600;
		int32_t m_Height = 900;
	};
}