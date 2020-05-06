#pragma once
#include "SGTime.h"
#include <vector>
#include <memory>
#include <list>

namespace SG
{
	class SGTime;
	typedef std::shared_ptr<SGTime> StrongTimePtr;
	typedef std::weak_ptr<SGTime> WeakTimePtr;

	class SGTimeFactory
	{
	public:
		static StrongTimePtr GetTimer();
	};
}
