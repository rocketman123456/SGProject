#pragma once
#include "SGIRuntimeModule.h"

namespace SG
{
	class SGEventManager : implements SGIRuntimeModule<SGEventManager>
	{
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;

		virtual void Tick() override;
	};
	extern SGIRuntimeModule<SGEventManager>* g_pEventManager;
}
