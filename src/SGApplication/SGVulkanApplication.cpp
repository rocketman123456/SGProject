#include "SGVulkanApplication.h"

namespace SG
{
	SG_MEMORYPOOL_DEFINITION(SGVulkanApplication);
	SG_MEMORYPOOL_AUTOINIT(SGVulkanApplication, 128);
}

int SG::SGVulkanApplication::Initialize(int32_t w, int32_t h)
{
	m_Width = w;
	m_Height = h;
	return Initialize();
}

int SG::SGVulkanApplication::Initialize()
{
	int result = 0;
	do {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(m_Width, m_Height, "Vulkan", nullptr, nullptr);
	} while (false);

	LOG_INFO("SGVulkanApplication Initialize");
	return result;
}

void SG::SGVulkanApplication::Finalize()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	LOG_INFO("SGVulkanApplication Finalize");
}

void SG::SGVulkanApplication::Tick()
{
	m_bQuit = glfwWindowShouldClose(m_Window);
}

bool SG::SGVulkanApplication::IsQuit()
{
	return m_bQuit;
}
