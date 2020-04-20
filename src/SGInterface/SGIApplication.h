#pragma once
#include "SGIRuntimeModule.h"

namespace SG
{
	Interface SGIApplication : implements SGIRuntimeModule{
	public:
		virtual int Initialize() = 0;
		virtual void Finalize() = 0;

		virtual void Tick() = 0;
		virtual bool IsQuit() = 0;

	public:
		void SetIsQuit(bool quit) { m_bQuit = quit; }
	protected:
		bool m_bQuit = false;
	};

	extern SGIApplication* g_pApp;
}