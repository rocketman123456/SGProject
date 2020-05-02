#pragma once
#include "SGIRuntimeModule.h"
#include "SGTime.h"
#include <vector>
#include <memory>

namespace SG
{
	class SGTime;
	typedef std::shared_ptr<SGTime> StrongTimePtr;
	typedef std::weak_ptr<SGTime> WeakTimePtr;

	class SGTimeManager : implements SGIRuntimeModule<SGTimeManager>
	{
	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();

		StrongTimePtr GetTime();
	protected:
		std::vector<WeakTimePtr> m_TimerList;
	};
}
