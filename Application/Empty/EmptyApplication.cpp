#include "SGBaseApplication.h"
#include "SGGraphicsManager.h"
#include "SGEventManager.h"

namespace SG
{
	SGBaseApplication g_App;
	SGGraphicsManager g_GraphicsManager;
	SGEventManager g_EventManager;

	SGIApplication* g_pApp = &g_App;
	SGIRuntimeModule* g_pGraphicsManager = &g_GraphicsManager;
	SGIRuntimeModule* g_pEventManager = &g_EventManager;
}
