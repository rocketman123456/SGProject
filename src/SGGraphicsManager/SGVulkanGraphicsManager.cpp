#include "SGVulkanGraphicsManager.h"
SG_MEMORYPOOL_DEFINITION(SG::SGVulkanGraphicsManager);

int SG::SGVulkanGraphicsManager::Initialize()
{
	int result = 0;
	SGVulkanGraphicsManager::InitMemoryPool(128);
	do {

	} while (false);
	LOG_INFO("SGGraphicsManager Initialize");
	return result;
}

void SG::SGVulkanGraphicsManager::Finalize()
{
	SGVulkanGraphicsManager::DestroyMemoryPool();
	LOG_INFO("SGVulkanGraphicsManager Initialize");
}

void SG::SGVulkanGraphicsManager::Tick()
{
}
