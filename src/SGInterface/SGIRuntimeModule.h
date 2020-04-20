#pragma once
#include "SGDefine.h"

namespace SG
{
	Interface SGIRuntimeModule {
	public:
		virtual ~SGIRuntimeModule() {};

		virtual int Initialize() = 0;
		virtual void Finalize() = 0;

		virtual void Tick() = 0;
	};
}

