#include "SGVulkanGraphicsManager.h"
#include "SGVulkanApplication.h"
#include "AssertFault.h"

namespace SG
{
	extern SGIApplication<SGVulkanApplication>* g_pGLApp;

	SG_MEMORYPOOL_DEFINITION(SGVulkanGraphicsManager);
	SG_MEMORYPOOL_AUTOINIT(SGVulkanGraphicsManager, 128);
}

int SG::SGVulkanGraphicsManager::Initialize()
{
	int result = 0;
	do {

	} while (false);
	LOG_INFO("SGGraphicsManager Initialize");
	return result;
}

void SG::SGVulkanGraphicsManager::Finalize()
{
	LOG_INFO("SGVulkanGraphicsManager Initialize");
}

void SG::SGVulkanGraphicsManager::Tick()
{
}
