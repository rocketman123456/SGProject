#pragma once
#include "SGIRuntimeModule.h"

namespace SG
{
	class SGEventManager : implements SGIRuntimeModule
	{
	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();
	};

	extern SGIRuntimeModule* g_pEventManager;
}
