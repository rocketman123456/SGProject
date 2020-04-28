#include "SGGraphicsManager.h"
#include "SGBaseApplication.h"
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
}

SG_MEMORYPOOL_DEFINITION(SG::SGGraphicsManager);

int SG::SGGraphicsManager::Initialize()
{
	int result = 0;
	do {
		SGGraphicsManager::InitMemoryPool(128);
		// get glfw from global app
		m_Width = static_cast<SGBaseApplication*>(g_pApp)->GetWindowWidth();
		m_Height = static_cast<SGBaseApplication*>(g_pApp)->GetWindowHeight();
		m_Window = static_cast<SGBaseApplication*>(g_pApp)->GetGLFWWindow();
		ASSERT_TRUE(m_Window);

		m_Camera = static_cast<SGInputManager*>(g_pInputManager)->GetCamera();
		ASSERT_TRUE(m_Camera);

		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);
		// 用多重采样来解决锯齿问题
		glEnable(GL_MULTISAMPLE);

		GenerateShader();
		GenerateData();
		GenerateTexture();
	} while (false);

	LOG_INFO("SGGraphicsManager Initialize");
	return result;
}

void SG::SGGraphicsManager::Finalize()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &m_cubeVAO);
    glDeleteBuffers(1, &m_VBO);

	SGGraphicsManager::DestroyMemoryPool();
	LOG_INFO("SGGraphicsManager Finalize");
}

void SG::SGGraphicsManager::Tick()
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

	// lighting
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	// be sure to activate shader when setting uniforms/drawing objects
	m_LightingShader->use();
	m_LightingShader->setVec3("viewPos", m_Camera->Position);
	m_LightingShader->setFloat("material.shininess", 32.0f);

	// directional light
	m_LightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	m_LightingShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	m_LightingShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	m_LightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	m_LightingShader->setVec3("pointLights[0].position", pointLightPositions[0]);
	m_LightingShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	m_LightingShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	m_LightingShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	m_LightingShader->setFloat("pointLights[0].constant", 1.0f);
	m_LightingShader->setFloat("pointLights[0].linear", 0.09);
	m_LightingShader->setFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	m_LightingShader->setVec3("pointLights[1].position", pointLightPositions[1]);
	m_LightingShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	m_LightingShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	m_LightingShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	m_LightingShader->setFloat("pointLights[1].constant", 1.0f);
	m_LightingShader->setFloat("pointLights[1].linear", 0.09);
	m_LightingShader->setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	m_LightingShader->setVec3("pointLights[2].position", pointLightPositions[2]);
	m_LightingShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	m_LightingShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	m_LightingShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	m_LightingShader->setFloat("pointLights[2].constant", 1.0f);
	m_LightingShader->setFloat("pointLights[2].linear", 0.09);
	m_LightingShader->setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	m_LightingShader->setVec3("pointLights[3].position", pointLightPositions[3]);
	m_LightingShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	m_LightingShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	m_LightingShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	m_LightingShader->setFloat("pointLights[3].constant", 1.0f);
	m_LightingShader->setFloat("pointLights[3].linear", 0.09);
	m_LightingShader->setFloat("pointLights[3].quadratic", 0.032);
	// spotLight
	m_LightingShader->setVec3("spotLight.position", m_Camera->Position);
	m_LightingShader->setVec3("spotLight.direction", m_Camera->Front);
	m_LightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	m_LightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	m_LightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	m_LightingShader->setFloat("spotLight.constant", 1.0f);
	m_LightingShader->setFloat("spotLight.linear", 0.09);
	m_LightingShader->setFloat("spotLight.quadratic", 0.032);
	m_LightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	m_LightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)m_Width / (float)m_Height, 0.1f, 100.0f);
	glm::mat4 view = m_Camera->GetViewMatrix();
	m_LightingShader->setMat4("projection", projection);
	m_LightingShader->setMat4("view", view);

	// bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseMap);
	// bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_SpecularMap);

	// render the cube
	glBindVertexArray(m_cubeVAO);

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		m_LightingShader->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// also draw the lamp object(s)
	m_LampShader->use();
	m_LampShader->setMat4("projection", projection);
	m_LampShader->setMat4("view", view);

	// we now draw as many light bulbs as we have point lights.
	glBindVertexArray(m_lightVAO);
	for (unsigned int i = 0; i < 4; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		m_LampShader->setMat4("model", model);

		m_LampShader->setVec3("lightColor", 0.0f, 0.0f, 0.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_LampShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// TODO: add Debug UI here -- imgui

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void SG::SGGraphicsManager::GenerateShader()
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
}

void SG::SGGraphicsManager::GenerateData()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	glGenVertexArrays(1, &m_cubeVAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// light VAO generation
	glGenVertexArrays(1, &m_lightVAO);
	glBindVertexArray(m_lightVAO);
	// we only need to bind to the VBO, the container's VBO's data already contains the data.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// set the vertex attributes (only position data for our lamp)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void SG::SGGraphicsManager::GenerateTexture()
{
	// load picture
	std::string picdiffuse = m_BaseAssetDir + "Textures/container2.png";
	m_DiffuseMap = LoadTexture(picdiffuse.c_str());
	std::string picspecular = m_BaseAssetDir + "Textures/container2_specular.png"; 
	//std::string picspecular = m_BaseAssetDir + "Textures/lighting_maps_specular_color.png";
	m_SpecularMap = LoadTexture(picspecular.c_str());
	m_LightingShader->use();
	m_LightingShader->setInt("material.diffuse", 0);
	m_LightingShader->setInt("material.specular", 1);
}

// TODO: use uniform resource manager
// utility function for loading a 2D texture from file
// ---------------------------------------------------
uint32_t SG::SGGraphicsManager::LoadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
