#include "SGBaseApplication.h"
#include "SGLog.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

int SG::SGBaseApplication::Initialize(int32_t w, int32_t h)
{
	m_Witdh = w;
	m_Height = h;
	return Initialize();
}

int SG::SGBaseApplication::Initialize()
{
	int result = 0;
	do {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		LOG_INFO("OpenGL Version %d.%d", 4, 5)

		m_Window = glfwCreateWindow(m_Witdh, m_Height, "SGProject", NULL, NULL);
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

	LOG_INFO("SGBaseApplication Initialize");
	return result;
}

void SG::SGBaseApplication::Finalize()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	LOG_INFO("SGBaseApplication Finalize");
}

void SG::SGBaseApplication::Tick()
{
	m_bQuit = glfwWindowShouldClose(m_Window);
}

bool SG::SGBaseApplication::IsQuit()
{
	return m_bQuit;
}
