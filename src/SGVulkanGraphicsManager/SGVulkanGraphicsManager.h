#pragma once
#include "SGLog.h"
#include "SGIRuntimeModule.h"
#include "SGMemoryMacros.h"

#define GLFW_INCLUDE_VULKAN
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SG
{
	class SGVulkanGraphicsManager : implements SGIRuntimeModule<SGVulkanGraphicsManager>
	{
		SG_MEMORYPOOL_DECLARATION(0);
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;
	};
}