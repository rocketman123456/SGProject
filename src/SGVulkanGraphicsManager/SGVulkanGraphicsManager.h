#pragma once
#include "SGLog.h"
#include "SGIRuntimeModule.h"
#include "SGMemoryMacros.h"

#define GLFW_INCLUDE_VULKAN
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>

namespace SG
{
	class SGVulkanGraphicsManager : implements SGIRuntimeModule<SGVulkanGraphicsManager>
	{
		SG_MEMORYPOOL_DECLARATION(0);
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;

	public:
		GLFWwindow* GetGLFWWindow() const { return m_Window; }
		int32_t GetWindowWidth() const { return m_Width; }
		int32_t GetWindowHeight() const { return m_Height; }

	protected:
		int initWindow();
		int initVulkan();
		int createInstance();
		int setupDebugMessenger();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		std::vector<const char*> getRequiredExtensions();
		bool checkValidationLayerSupport();

	protected:
		GLFWwindow* m_Window;
		int32_t m_Width;
		int32_t m_Height;

		// Vulkan
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
			VkDebugUtilsMessageTypeFlagsEXT messageType, 
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, 
			void* pUserData) {
			LOG_ERROR("validation layer: %s", pCallbackData->pMessage);
			return VK_FALSE;
		}
	};
}