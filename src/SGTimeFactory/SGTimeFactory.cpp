#include "SGTimeFactory.h"
#include "SGLog.h"
using namespace SG;

StrongTimePtr SG::SGTimeFactory::GetTimer(Resolution res)
{
	SGTime* time = nullptr;
	switch (res)
	{
	case(High):
	{
		time = new SGTimeHigh();
	}break;
	case(Normal):
	{
		time = new SGTimeNormal();
	}break;
	case(Low):
	{
		time = new SGTimeLow();
	}break;
	}
	auto p = StrongTimePtr(time);
	return p;
}
