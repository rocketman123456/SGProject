#include "SGOpenGLGraphicsManager.h"
#include "SGOpenGLApplication.h"
#include "SGGraphicsManager.h"
#include "SGTextureLoader.h"
#include "AssertFault.h"
#include "SGCubeData.h"

#include <stb_image.h>
#include <string>
#include <vector>

namespace SG
{
	extern SGIApplication<SGOpenGLApplication>* g_pGLApp;
	extern SGIRuntimeModule<SGGraphicsManager>* g_pGraphicsManager;

	SG_MEMORYPOOL_DEFINITION(SGOpenGLGraphicsManager);
	SG_MEMORYPOOL_AUTOINIT(SGOpenGLGraphicsManager, 128);
}

static uint32_t amount = 1*100*100;

int SG::SGOpenGLGraphicsManager::Initialize()
{
	int result = 0;
	do {
		// get glfw from global app
		m_Width = static_cast<SGOpenGLApplication*>(g_pGLApp)->GetWindowWidth();
		m_Height = static_cast<SGOpenGLApplication*>(g_pGLApp)->GetWindowHeight();
		m_Window = static_cast<SGOpenGLApplication*>(g_pGLApp)->GetGLFWWindow();
		ASSERT_TRUE(m_Window);

		m_Camera = static_cast<SGGraphicsManager*>(g_pGraphicsManager)->GetCamera();
		ASSERT_TRUE(!m_Camera.expired());

		// configure global opengl state
		// -----------------------------
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// Set the polygon winding to front facing for the right handed system.
		glFrontFace(GL_CCW);
		// Enable back face culling.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		// 用多重采样来解决锯齿问题
		glEnable(GL_MULTISAMPLE);
		// Gamma Correct
		glEnable(GL_FRAMEBUFFER_SRGB);
		
		// load model
		std::string m1 = m_BaseAssetDir + "Models/nanosuit.obj";
		m_NanoSuitModel = new SGModel(m1.c_str());
		ASSERT_TRUE(m_NanoSuitModel);
		std::string m2 = m_BaseAssetDir + "Models/rock.obj";
		m_RockModel = new SGModel(m2.c_str());
		ASSERT_TRUE(m_RockModel);
		std::string m3 = m_BaseAssetDir + "Models/planet.obj";
		m_PlanetModel = new SGModel(m3.c_str());
		ASSERT_TRUE(m_PlanetModel);

		GenerateData();
		GenerateShader();

		m_SkyboxShader->use();
		m_SkyboxShader->setInt("skybox", 0);
		m_ModelShader->use();
		m_ModelShader->setInt("skybox", 4);

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
	if (m_Camera.expired()) {
		LOG_ERROR("Camera Destroyed");
	}
	StrongCameraPtr camera = m_Camera.lock();
	// per-frame time logic
	// --------------------
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// render start
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)m_Width / (float)m_Height, 0.1f, 2000.0f);
	//glm::mat4 view = m_Camera->GetViewMatrix();
	glm::mat4 view = camera->AutoLookAt(glm::vec3(0,0,0));

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	
	//m_ModelShader->use();
	//m_ModelShader->setMat4("projection", projection);
	//m_ModelShader->setMat4("view", view);
	//m_ModelShader->setMat4("model", model);
	//m_ModelShader->setVec3("cameraPos", camera->Position);
	//m_ModelShader->setFloat("time", glfwGetTime());
	//m_ModelShader->setFloat("time", 0.0f);
	//glActiveTexture(GL_TEXTURE4);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubemapTexture);
	//m_NanoSuitModel->Draw(*m_ModelShader);

	// then draw model with normal visualizing geometry shader
	//m_NormalShader->use();
	//m_NormalShader->setMat4("projection", projection);
	//m_NormalShader->setMat4("view", view);
	//m_NormalShader->setMat4("model", model);
	// draw model
	//m_NanoSuitModel->Draw(*m_NormalShader);

	// draw planet
	glm::mat4 model_planet = glm::mat4(1.0f);
	model_planet = glm::translate(model_planet, glm::vec3(0.0f, -18.0f, 0.0f));
	model_planet = glm::scale(model_planet, glm::vec3(4.0f, 4.0f, 4.0f));
	
	m_PlanetShader->use();
	m_PlanetShader->setMat4("model", model_planet);
	m_PlanetShader->use();
	m_PlanetShader->setMat4("projection", projection);
	m_PlanetShader->setMat4("view", view);
	m_PlanetModel->Draw(*m_PlanetShader);

	// draw meteorites
	m_AsteroidShader->use();
	m_AsteroidShader->setInt("texture_diffuse1", 0);
	m_AsteroidShader->setMat4("projection", projection);
	m_AsteroidShader->setMat4("view", view);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_RockModel->textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
	for (unsigned int i = 0; i < m_RockModel->meshes.size(); i++)
	{
		glBindVertexArray(m_RockModel->meshes[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, m_RockModel->meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}

	// draw skybox as last
	view = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
	m_SkyboxShader->use();
	m_SkyboxShader->setMat4("view", view);
	m_SkyboxShader->setMat4("projection", projection);
	// skybox cube
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	glBindVertexArray(m_SkyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default

	// TODO: add Debug UI here -- imgui

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void SG::SGOpenGLGraphicsManager::GenerateData()
{
	// generate a large list of semi-random model transformation matrices
		// ------------------------------------------------------------------
	m_ModelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // initialize random seed	
	float radius = 150.0;
	float offset = 25.0f;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. scale: Scale between 0.05 and 0.25f
		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. now add to list of matrices
		m_ModelMatrices[i] = model;
	}

	// configure instanced array
	// -------------------------
	uint32_t buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &m_ModelMatrices[0], GL_STATIC_DRAW);

	// set transformation matrices as an instance vertex attribute (with divisor 1)
	// note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
	// normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
	// -----------------------------------------------------------------------------------------------------------------------------------
	for (uint32_t i = 0; i < m_RockModel->meshes.size(); i++)
	{
		uint32_t VAO = m_RockModel->meshes[i].VAO;
		glBindVertexArray(VAO);
		// set attribute pointers for matrix (4 times vec4)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}

	// skybox VAO
	glGenVertexArrays(1, &m_SkyboxVAO);
	glGenBuffers(1, &m_SkyboxVBO);
	glBindVertexArray(m_SkyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_SkyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	std::vector<std::string> faces
	{
		(m_BaseAssetDir + "Textures/skybox/right.jpg"),
		(m_BaseAssetDir + "Textures/skybox/left.jpg"),
		(m_BaseAssetDir + "Textures/skybox/top.jpg"),
		(m_BaseAssetDir + "Textures/skybox/bottom.jpg"),
		(m_BaseAssetDir + "Textures/skybox/front.jpg"),
		(m_BaseAssetDir + "Textures/skybox/back.jpg")
	};
	m_CubemapTexture = CubeMapFromFile(faces);
}

void SG::SGOpenGLGraphicsManager::GenerateShader()
{
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
	std::string gs3 = m_BaseAssetDir + "Shaders/ModelShaderGS.glsl";
	m_ModelShader = new SGShader(vs3.c_str(), fs3.c_str(), gs3.c_str());
	ASSERT_TRUE(m_ModelShader);
	std::string vs4 = m_BaseAssetDir + "Shaders/SkyboxShaderVS.glsl";
	std::string fs4 = m_BaseAssetDir + "Shaders/SkyboxShaderFS.glsl";
	m_SkyboxShader = new SGShader(vs4.c_str(), fs4.c_str());
	ASSERT_TRUE(m_SkyboxShader);
	std::string vs5 = m_BaseAssetDir + "Shaders/NormalShaderVS.glsl";
	std::string fs5 = m_BaseAssetDir + "Shaders/NormalShaderFS.glsl";
	std::string gs5 = m_BaseAssetDir + "Shaders/NormalShaderGS.glsl";
	m_NormalShader = new SGShader(vs5.c_str(), fs5.c_str(), gs5.c_str());
	ASSERT_TRUE(m_NormalShader);
	std::string vs6 = m_BaseAssetDir + "Shaders/AsteroidsShaderVS.glsl";
	std::string fs6 = m_BaseAssetDir + "Shaders/AsteroidsShaderFS.glsl";
	m_AsteroidShader = new SGShader(vs6.c_str(), fs6.c_str());
	ASSERT_TRUE(m_AsteroidShader);
	std::string vs7 = m_BaseAssetDir + "Shaders/PlanetShaderVS.glsl";
	std::string fs7 = m_BaseAssetDir + "Shaders/PlanetShaderFS.glsl";
	m_PlanetShader = new SGShader(vs7.c_str(), fs7.c_str());
	ASSERT_TRUE(m_PlanetShader);
}