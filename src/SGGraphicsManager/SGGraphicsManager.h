#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sigslot/signal.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SGIRuntimeModule.h"
#include "Shader.h"

namespace SG
{
	class SGGraphicsManager : implements SGIRuntimeModule
	{
	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();
	public:
		GLFWwindow* GetGLFWWindow() const { return m_Window; }
	protected:
		sigslot::signal<bool> m_SigEnd;

		GLFWwindow* m_Window;
		uint32_t m_VBO, m_VAO;
		uint32_t m_Texture1;
		uint32_t m_Texture2;
		Shader* m_Shader;

		int32_t m_witdh = 1600;
		int32_t m_height = 900;
	};

	extern SGIRuntimeModule* g_pGraphicsManager;
}
