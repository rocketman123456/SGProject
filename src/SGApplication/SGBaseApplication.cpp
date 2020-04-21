#include "SGBaseApplication.h"
#include "SGLog.h"

int SG::SGBaseApplication::Initialize()
{
	LOG_INFO("SGBaseApplication Initialize");
	return 0;
}

void SG::SGBaseApplication::Finalize()
{
	LOG_INFO("SGBaseApplication Finalize");
}

void SG::SGBaseApplication::Tick()
{
}

bool SG::SGBaseApplication::IsQuit()
{
	return m_bQuit;
}
