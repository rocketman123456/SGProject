#pragma once
#include "SGLog.h"
#include "SGMemoryMacros.h"
#include "SGIRuntimeModule.h"

#include "SGConfig.h"
#include "SGCamera.h"
#include "SGLight.h"
#include "SGMaterial.h"
#include "SGMaterialData.h"
#include "SGShader.h"
#include "SGModel.h"

#define GLFW_INCLUDE_VULKAN
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SG
{
	using StrongCameraPtr = std::shared_ptr<SGCamera>;
	using WeakCameraPtr = std::weak_ptr<SGCamera>;

	class SGOpenGLGraphicsManager : implements SGIRuntimeModule<SGOpenGLGraphicsManager>
	{
		SG_MEMORYPOOL_DECLARATION(0);
	public:
		// TODO: use uniform asset loader
		SGOpenGLGraphicsManager(const std::string& asset = SGProject_ASSET_DIR) :m_BaseAssetDir(asset) {}
		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;

	public:
		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		SGShader* GetShader() const { return m_LightingShader; }
		int32_t GetWindowWidth() const { return m_Width; }
		int32_t GetWindowHeight() const { return m_Height; }

	protected:
		void GenerateData();
		void GenerateShader();

	protected:
		GLFWwindow* m_Window;
		int32_t m_Width;
		int32_t m_Height;
		int32_t m_ShadowWidth;
		int32_t m_ShadowHeight;

		WeakCameraPtr m_Camera;
		SGModel* m_NanoSuitModel;
		
		SGShader* m_LightingShader;
		SGShader* m_LampShader;
		SGShader* m_ModelShader;
		SGShader* m_SkyboxShader;
		SGShader* m_NormalShader;

		SGModel* m_RockModel;
		SGModel* m_PlanetModel;
		SGShader* m_AsteroidShader;
		SGShader* m_PlanetShader;
		glm::mat4* m_ModelMatrices;

		std::string m_BaseAssetDir;
		uint32_t m_SkyboxVAO, m_SkyboxVBO;
		uint32_t m_CubemapTexture;
		//uint32_t m_VBO;
		//uint32_t m_cubeVAO, m_lightVAO;
		//uint32_t m_Texture1, m_Texture2;
		//uint32_t m_DiffuseMap, m_SpecularMap;

		float currentFrame = 0.0, lastFrame = 0.0, deltaTime = 0.0;
	};

	extern SGIRuntimeModule<SGOpenGLGraphicsManager>* g_pGLGraphicsManager;
}
