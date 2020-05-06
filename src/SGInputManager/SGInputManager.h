#pragma once
#include "SGIRuntimeModule.h"
#include "SGTimeFactory.h"
#include "SGEventManager.h"
#include "SGSystemEvent.h"
#include "SGCamera.h"

#define GLFW_INCLUDE_VULKAN
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

namespace SG
{
	class SGInputManager : implements SGIRuntimeModule<SGInputManager>
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

	protected:
		GLFWwindow* m_Window = nullptr;
		int32_t m_Width;
		int32_t m_Height;

		bool m_isMouseEnable = true;

		std::map<int, bool> m_previous;
		std::map<int, bool> m_current;

		StrongTimePtr m_timer;
		float m_deltaTime = 0.0f;
	};

	extern SGIRuntimeModule<SGInputManager>* g_pInputManager;
}
