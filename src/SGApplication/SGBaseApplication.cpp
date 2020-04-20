#include "SGBaseApplication.h"

int SG::SGBaseApplication::Initialize()
{
	m_bQuit = false;
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
