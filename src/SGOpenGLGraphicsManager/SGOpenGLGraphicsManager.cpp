#include "SGOpenGLGraphicsManager.h"
#include "SGOpenGLApplication.h"
#include "SGInputManager.h"
#include "AssertFault.h"
#include "SGCubeData.h"

#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace SG
{
	extern SGIApplication* g_pApp;
	extern SGIRuntimeModule* g_pInputManager;

	SG_MEMORYPOOL_DEFINITION(SGOpenGLGraphicsManager);
	SG_MEMORYPOOL_AUTOINIT(SGOpenGLGraphicsManager, 128);
}

int SG::SGOpenGLGraphicsManager::Initialize()
{
	int result = 0;
	do {
		// get glfw from global app
		m_Width = static_cast<SGOpenGLApplication*>(g_pApp)->GetWindowWidth();
		m_Height = static_cast<SGOpenGLApplication*>(g_pApp)->GetWindowHeight();
		m_Window = static_cast<SGOpenGLApplication*>(g_pApp)->GetGLFWWindow();
		ASSERT_TRUE(m_Window);

		m_Camera = static_cast<SGInputManager*>(g_pInputManager)->GetCamera();
		ASSERT_TRUE(m_Camera);

		// configure global opengl state
		// -----------------------------
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		// �ö��ز���������������
		glEnable(GL_MULTISAMPLE);
		// Set the polygon winding to front facing for the right handed system.
		//glFrontFace(GL_CCW);
		// Enable back face culling.
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		// build and compile our shader program
		// ------------------------------------
		std::string vs1 = m_BaseAssetDir + "Shaders/LightShaderVS.glsl";
		std::string fs1 = m_BaseAssetDir + "Shaders/LightShaderFS.glsl";
		m_LightingShader = new SGShader(vs1.c_str(), fs1.c_str());
		ASSERT_TRUE(m_LightingShader);
		std::string vs2 = m_BaseAssetDir + "Shaders/LampShaderVS.glsl";
		std::string fs2 = m_BaseAssetDir + "Shaders/LampShaderFS.glsl";
		m_LampShader = new SGShader(vs2.c_str(), fs2.c_str());
		ASSERT_TRUE(m_LampShader);
		std::string vs3 = m_BaseAssetDir + "Shaders/ModelShaderVS.glsl";
		std::string fs3 = m_BaseAssetDir + "Shaders/ModelShaderFS.glsl";
		m_ModelShader = new SGShader(vs3.c_str(), fs3.c_str());
		ASSERT_TRUE(m_ModelShader);

		std::string m1 = m_BaseAssetDir + "Models/nanosuit.obj";
		m_Model = new SGModel(m1.c_str());
		ASSERT_TRUE(m_Model);
	} while (false);

	LOG_INFO("SGOpenGLGraphicsManager Initialize");
	return result;
}

void SG::SGOpenGLGraphicsManager::Finalize()
{
	LOG_INFO("SGOpenGLGraphicsManager Finalize");
}

void SG::SGOpenGLGraphicsManager::Tick()
{
	// per-frame time logic
	// --------------------
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// render start
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ModelShader->use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)m_Width / (float)m_Height, 0.1f, 100.0f);
	glm::mat4 view = m_Camera->GetViewMatrix();
	m_ModelShader->setMat4("projection", projection);
	m_ModelShader->setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	m_ModelShader->setMat4("model", model);
	m_Model->Draw(*m_ModelShader);

	// TODO: add Debug UI here -- imgui

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}
