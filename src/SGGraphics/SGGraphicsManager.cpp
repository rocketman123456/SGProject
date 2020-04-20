#include "SGGraphicsManager.h"
#include "SGIApplication.h"
#include "SGBaseApplication.h"
#include "SGLog.h"

namespace SG
{
	extern SGIApplication* g_pApp;
}

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
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_witdh, m_height, "SGProject", NULL, NULL);
	if (m_window == NULL)
	{
		LOG_ERROR("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("Failed to initialize GLAD");
		return -1;
	}

	return 0;
}

void SG::SGGraphicsManager::Finalize()
{
	glfwTerminate();
}

void SG::SGGraphicsManager::Tick()
{
	if (glfwWindowShouldClose(m_window))
	{
		LOG_INFO("Close Window");
		g_pApp->SetIsQuit(true);
	}
	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
