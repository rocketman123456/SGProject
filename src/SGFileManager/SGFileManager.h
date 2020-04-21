#pragma once
#include "SGIRuntimeModule.h"

namespace SG
{
	class SGFileManager : implements SGIRuntimeModule
	{
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;

		virtual void Tick() override;
	};
}
