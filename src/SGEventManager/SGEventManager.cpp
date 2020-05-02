#include "SGEventManager.h"
#include "SGLog.h"

int SG::SGEventManager::Initialize()
{
	LOG_INFO("SGEventManager Initialize");
	return 0;
}

void SG::SGEventManager::Finalize()
{
	LOG_INFO("SGEventManager Finalize");
}

void SG::SGEventManager::Tick()
{
}
