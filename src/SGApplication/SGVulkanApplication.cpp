#include "SGVulkanApplication.h"
#include <stdexcept>

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
		result += InitWindow();
		result += InitVulkan();
	} while (false);

	LOG_INFO("SGVulkanApplication Initialize");
	return result;
}

void SG::SGVulkanApplication::Finalize()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwDestroyWindow(m_Window);
	glfwTerminate();

	LOG_INFO("SGVulkanApplication Finalize");
}

void SG::SGVulkanApplication::Tick()
{
	m_bQuit = glfwWindowShouldClose(m_Window);

	glfwPollEvents();
}

bool SG::SGVulkanApplication::IsQuit()
{
	return m_bQuit;
}

int SG::SGVulkanApplication::InitWindow()
{
	int result = 0;
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Window = glfwCreateWindow(m_Width, m_Height, "Vulkan", nullptr, nullptr);

	if (m_Window == NULL)
	{
		LOG_ERROR("Failed to create GLFW window");
		glfwTerminate();
		result = 1;
	}
	return result;
}

int SG::SGVulkanApplication::InitVulkan()
{
	int result = 0;
	result += CreateInstance();
	return result;
}

int SG::SGVulkanApplication::CreateInstance()
{
	int result = 0;
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Vulkan";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		result = 1;
		LOG_ERROR("failed to create instance!");
	}
	return result;
}
