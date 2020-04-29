#pragma once
#include "SGIRuntimeModule.h"
#include "SGCamera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

namespace SG
{
	class SGInputManager : implements SGIRuntimeModule
	{
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;

		virtual void Tick() override;
	public:
		bool CheckOnPress(int Key);
		bool CheckOnRelease(int Key);
		void UpdateCurrentKeys();
		void UpdatePreviousKeys();
	public:
		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		SGCamera* GetCamera() const { return m_Camera; }
		int32_t GetWindowWidth() const { return m_Width; }
		int32_t GetWindowHeight() const { return m_Height; }
	protected:
		GLFWwindow* m_Window = nullptr;
		SGCamera* m_Camera = nullptr;
		int32_t m_Width;
		int32_t m_Height;

		bool m_isMouseEnable = true;

		std::map<int, bool> m_previous;
		std::map<int, bool> m_current;

		float m_deltaTime = 0.0f, m_lastFrame = 0.0f, m_currentFrame = 0.0f;
	};

	extern SGIRuntimeModule* g_pInputManager;
}
