#include "SGGraphicsManager.h"
#include "SGConfig.h"
#include "SGLog.h"
#include "SGBaseApplication.h"

#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace SG
{
	extern SGIApplication* g_pApp;
}

float mixValue = 0.2f;

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

int SG::SGGraphicsManager::Initialize()
{
	int result = 0;
	do {
		// TODO : use uniform event manager to trigger an event
		m_SigEnd.connect(&SGIApplication::SetIsQuit, g_pApp);

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		LOG_INFO("OpenGL Version %d.%d", 4, 5)

			m_Window = glfwCreateWindow(m_witdh, m_height, "SGProject", NULL, NULL);
		if (m_Window == NULL)
		{
			LOG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			result = 1;
			break;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
			result = 2;
			break;
		}

		// build and compile our shader program
		// ------------------------------------
		std::string base = SGProject_SOURCE_DIR;
		std::string vs = base + "/Shaders/shaderVS.glsl";
		std::string fs = base + "/Shaders/shaderFS.glsl";
		m_Shader = new Shader(vs.c_str(), fs.c_str());

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
		};
		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

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
		std::string pic1 = base + "/Assets/Textures/container.jpg";
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
		std::string pic2 = base + "/Assets/Textures/awesomeface.png";
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

		m_Shader->use();
		m_Shader->setInt("texture1", 0);
		m_Shader->setInt("texture2", 1);

		LOG_INFO("SGGraphicsManager Initialize");
	} while (false);
	return result;
}

void SG::SGGraphicsManager::Finalize()
{
	delete m_Shader;
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glfwTerminate();
	LOG_INFO("SGGraphicsManager Finalize");
}

void SG::SGGraphicsManager::Tick()
{
	if (glfwWindowShouldClose(m_Window))
	{
		LOG_INFO("Close Window");
		m_SigEnd(true);
	}
	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_Texture2);

	m_Shader->use();

	// change picture mixture
	mixValue = (sin(glfwGetTime()) + 1.0) / 2.0;

	// create transformations
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)m_witdh / (float)m_height, 0.1f, 100.0f);

	m_Shader->setFloat("mixValue", mixValue);
	m_Shader->setMat4("model", model);
	m_Shader->setMat4("view", view);
	m_Shader->setMat4("projection", projection);

	// draw our first triangle
	
	glBindVertexArray(m_VAO);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}
