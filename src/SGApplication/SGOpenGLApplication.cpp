#include "SGOpenGLApplication.h"
#include "SGLog.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

namespace SG
{
	SG_MEMORYPOOL_DEFINITION(SGOpenGLApplication);
	SG_MEMORYPOOL_AUTOINIT(SGOpenGLApplication, 128);
}

int SG::SGOpenGLApplication::Initialize(int32_t w, int32_t h)
{
	m_Width = w;
	m_Height = h;
	return Initialize();
}

int SG::SGOpenGLApplication::Initialize()
{
	int result = 0;
	do {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		LOG_INFO("OpenGL Version %d.%d", 4, 5)

		m_Window = glfwCreateWindow(m_Width, m_Height, "SGProject", NULL, NULL);
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

		if (m_Window == NULL)
		{
			LOG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			result = 1;
			break;
		}
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
			result = 2;
			break;
		}
	} while (false);

	LOG_INFO("SGOpenGLApplication Initialize");
	return result;
}

void SG::SGOpenGLApplication::Finalize()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwDestroyWindow(m_Window);
	glfwTerminate();

	LOG_INFO("SGOpenGLApplication Finalize");
}

void SG::SGOpenGLApplication::Tick()
{
	m_bQuit = glfwWindowShouldClose(m_Window);
}

bool SG::SGOpenGLApplication::IsQuit()
{
	return m_bQuit;
}
