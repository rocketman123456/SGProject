#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <sigslot/signal.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SGIRuntimeModule.h"
#include "SGShader.h"
#include "SGCamera.h"

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
		SGShader* GetShader() const { return m_Shader; }
		SGCamera* GetCamera() const { return m_Camera; }
		int32_t GetWindowWidth() const { return m_Witdh; }
		int32_t GetWindowHeight() const { return m_Height; }
	protected:
		GLFWwindow* m_Window;
		SGShader* m_Shader;
		SGCamera* m_Camera;

		uint32_t m_VBO, m_VAO;
		uint32_t m_Texture1;
		uint32_t m_Texture2;

		int32_t m_Witdh;
		int32_t m_Height;
	};

	extern SGIRuntimeModule* g_pGraphicsManager;
}
