#pragma once
#include "SGIRuntimeModule.h"
#include "SGTime.h"
#include <vector>

namespace SG
{
	class SGTimeManager : implements SGIRuntimeModule<SGTimeManager>
	{
	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();
	protected:
		std::vector<SGTime> m_TimerList;
	};
}