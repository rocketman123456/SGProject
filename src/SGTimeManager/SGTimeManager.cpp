#include "SGTimeManager.h"
#include "SGLog.h"
using namespace SG;

int SG::SGTimeManager::Initialize()
{
	LOG_INFO("SGTimeManager Initialize");
	return 0;
}

void SG::SGTimeManager::Finalize()
{
	LOG_INFO("SGTimeManager Finalize");
}

StrongTimePtr SG::SGTimeManager::GetTime()
{
	auto time = new SGTime();
	auto p = StrongTimePtr(time);
	return p;
}
