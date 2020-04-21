#pragma once
#include <sigslot/signal.hpp>
#include "SGModules.h"

namespace SG
{
	void ConnectSlots()
	{
		sigslot::signal<bool> sig_end;
		sig_end.connect(&SGIApplication::SetIsQuit, g_pApp);
	}
}
