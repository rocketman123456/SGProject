#include "SGGraphicsManager.h"
#include "SGCubeData.h"
#include "SGBaseApplication.h"
#include "SGInputManager.h"
#include "AssertFault.h"

#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace SG
{
	extern SGIApplication* g_pApp;
	extern SGIRuntimeModule* g_pInputManager;
}

// texture mix value
float mixValue = 0.2f;
// world space positions of our cubes
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

int SG::SGGraphicsManager::Initialize()
{
	int result = 0;
	do {
		// get glfw from global app
		m_Witdh = static_cast<SGBaseApplication*>(g_pApp)->GetWindowWidth();
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
	delete m_LightingShader;
    glDeleteVertexArrays(1, &m_cubeVAO);
    glDeleteBuffers(1, &m_VBO);

	LOG_INFO("SGGraphicsManager Finalize");
}

void SG::SGGraphicsManager::Tick()
{
	// render start
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_Texture2);

	// change picture mixture
	mixValue = (sin(glfwGetTime()) + 1.0) / 2.0;
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = m_Camera->GetViewMatrix();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)m_Witdh / (float)m_Height, 0.1f, 100.0f);

	// activate shader
	m_LightingShader->use();
	m_LightingShader->setFloat("mixValue", mixValue);
	m_LightingShader->setMat4("view", view);
	m_LightingShader->setMat4("projection", projection);
	m_LightingShader->setVec3("viewPos", m_Camera->Position);

	m_LightingShader->setVec3("material.ambient", silver.ambient);
	m_LightingShader->setVec3("material.diffuse", silver.diffuse);
	m_LightingShader->setVec3("material.specular", silver.specular);
	m_LightingShader->setFloat("material.shininess", silver.shininess);

	glm::vec3 lightColor = glm::vec3(1.0f);
	//lightColor.x = sin(glfwGetTime() * 2.0f);
	//lightColor.y = sin(glfwGetTime() * 0.7f);
	//lightColor.z = sin(glfwGetTime() * 1.3f);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // 降低影响
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

	m_LightingShader->setVec3("light.position", lightPos);
	m_LightingShader->setVec3("light.ambient", ambientColor);
	m_LightingShader->setVec3("light.diffuse", diffuseColor); // 将光照调暗了一些以搭配场景
	m_LightingShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// TODO: load model and render
	// draw our first triangle
	glBindVertexArray(m_cubeVAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		float angle = 20.0f * i;
		model = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		m_LightingShader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// also draw the lamp object
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	m_LampShader->use();
	m_LampShader->setMat4("projection", projection);
	m_LampShader->setMat4("view", view);
	m_LampShader->setMat4("model", model);
	m_LampShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	glBindVertexArray(m_lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	// draw outline of the lamp
	m_LampShader->setVec3("lightColor", 0.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
	// texture 1
	// ---------
	int width, height, nrChannels;
	glGenTextures(1, &m_Texture1);
	glBindTexture(GL_TEXTURE_2D, m_Texture1);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	//stbi_set_flip_vertically_on_load(true);
	std::string pic1 = m_BaseAssetDir + "Textures/container.jpg";
	unsigned char* data = stbi_load(pic1.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG_ERROR("Failed to load texture %s", pic1.c_str());
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(1, &m_Texture2);
	glBindTexture(GL_TEXTURE_2D, m_Texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true);
	std::string pic2 = m_BaseAssetDir + "Textures/awesomeface.png";
	data = stbi_load(pic2.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG_ERROR("Failed to load texture %s", pic2.c_str());
	}
	stbi_image_free(data);

	m_LightingShader->use();
	m_LightingShader->setInt("texture1", 0);
	m_LightingShader->setInt("texture2", 1);
}
