#include "SGFileManager.h"
#include "SGLog.h"

int SG::SGFileManager::Initialize()
{
	LOG_INFO("SGFileManager Initialize");
	return 0;
}

void SG::SGFileManager::Finalize()
{
	LOG_INFO("SGFileManager Finalize");
}

void SG::SGFileManager::Tick()
{
}

bool SG::SGFileManager::CheckFileExist(const std::string& filename)
{
	return false;
}
