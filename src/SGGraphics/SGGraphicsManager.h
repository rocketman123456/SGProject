#pragma once
#include "SGIRuntimeModule.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SG
{
	class SGGraphicsManager : implements SGIRuntimeModule
	{
	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();
	protected:
		GLFWwindow* m_window;
		int16_t m_witdh = 1600;
		int16_t m_height = 900;
	};

	extern SGIRuntimeModule* g_pGraphicsManager;
}