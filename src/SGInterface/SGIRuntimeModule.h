#pragma once
#include "SGDefine.h"
#include "SGISingleton.h"

namespace SG
{
	template <typename T>
	Interface SGIRuntimeModule : implements SGISingleton<T>
	{
	public:
		virtual ~SGIRuntimeModule() {};

		virtual int Initialize() = 0;
		virtual void Finalize() = 0;

		virtual void Tick() = 0;
	};
}

