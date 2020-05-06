#include "SGTimeFactory.h"
#include "SGLog.h"
using namespace SG;

StrongTimePtr SG::SGTimeFactory::GetTimer()
{
	auto time = new SGTime();
	auto p = StrongTimePtr(time);
	return p;
}
