#pragma once
#include "SGIApplication.h"
#include "SGGraphicsManager.h"
#include "SGEventManager.h"

namespace SG 
{
	extern SGIApplication* g_pApp;
	extern SGIRuntimeModule* g_pEventManager;
	extern SGIRuntimeModule* g_pInputManager;
	extern SGIRuntimeModule* g_pGraphicsManager;
}
