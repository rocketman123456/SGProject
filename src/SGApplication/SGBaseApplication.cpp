#include "SGBaseApplication.h"

int SG::SGBaseApplication::Initialize()
{
	return 0;
}

void SG::SGBaseApplication::Finalize()
{
}

void SG::SGBaseApplication::Tick()
{
}

bool SG::SGBaseApplication::IsQuit()
{
	return m_bQuit;
}
