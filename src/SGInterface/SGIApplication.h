#pragma once
#include "SGIRuntimeModule.h"

namespace SG
{
	template <typename T>
	Interface SGIApplication : implements SGIRuntimeModule<T> 
	{
	public:
		virtual int Initialize() = 0;
		virtual void Finalize() = 0;

		virtual void Tick() = 0;
		virtual bool IsQuit() = 0;
		void SetIsQuit(bool quit) { m_bQuit = quit; }
	protected:
		bool m_bQuit = false;
	};
}