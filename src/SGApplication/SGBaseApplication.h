#pragma once
#include "SGIApplication.h"
#include "SGGraphicsManager.h"

namespace SG
{
	class SGBaseApplication : implements SGIApplication {
	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();
		virtual bool IsQuit();
	};
}