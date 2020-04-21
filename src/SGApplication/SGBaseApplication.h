#pragma once
#include "SGIApplication.h"
#include "SGGraphicsManager.h"

namespace SG
{
	class SGBaseApplication : implements SGIApplication {
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;

		virtual void Tick() override;
		virtual bool IsQuit() override;
	};
}