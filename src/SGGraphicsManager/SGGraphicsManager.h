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
#include "SGConfig.h"
#include "SGLog.h"

namespace SG
{
	class SGGraphicsManager : implements SGIRuntimeModule
	{
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;

	public:
		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		SGShader* GetShader() const { return m_LightingShader; }
		SGCamera* GetCamera() const { return m_Camera; }
		int32_t GetWindowWidth() const { return m_Witdh; }
		int32_t GetWindowHeight() const { return m_Height; }

	protected:
		void GenerateShader();
		void GenerateData();
		void GenerateTexture();

	protected:
		GLFWwindow* m_Window;
		SGCamera* m_Camera;

		SGShader* m_LightingShader;
		SGShader* m_LampShader;

		std::string m_BaseAssetDir = SGProject_ASSET_DIR;
		uint32_t m_VBO, m_cubeVAO, m_lightVAO;
		uint32_t m_Texture1;
		uint32_t m_Texture2;

		int32_t m_Witdh;
		int32_t m_Height;
	};

	extern SGIRuntimeModule* g_pGraphicsManager;
}
