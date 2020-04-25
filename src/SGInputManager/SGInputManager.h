#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

#include "SGIRuntimeModule.h"
#include "SGCamera.h"

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
		SGCamera* GetCamera() const { return m_Camera; }
	protected:
		GLFWwindow* m_Window = nullptr;
		SGCamera* m_Camera = nullptr;

		bool m_isMouseEnable = false;
		std::map<int, bool> m_previous;
		std::map<int, bool> m_current;

		float m_deltaTime = 0.0f, m_lastFrame = 0.0f, m_currentFrame = 0.0f;
	};
}
