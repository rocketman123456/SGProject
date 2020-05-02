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

void SG::SGTimeManager::Tick()
{
	for (auto time : m_TimerList)
	{
		if (time.expired()) 
		{

		}
	}
}

StrongTimePtr SG::SGTimeManager::GetTime()
{
	auto time = new SGTime();
	auto p = StrongTimePtr(time);
	m_TimerList.push_back(p);
	return p;
}
