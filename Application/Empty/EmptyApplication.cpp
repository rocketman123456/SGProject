#include "SGBaseApplication.h"
#include "SGGraphicsManager.h"
#include "SGEventManager.h"
#include "SGInputManager.h"

namespace SG
{
	SGBaseApplication g_App;
	SGEventManager g_EventManager;
	SGInputManager g_InputManager;
	SGGraphicsManager g_GraphicsManager;

	SGIApplication* g_pApp = &g_App;
	SGIRuntimeModule* g_pEventManager = &g_EventManager;
	SGIRuntimeModule* g_pGraphicsManager = &g_GraphicsManager;
	SGIRuntimeModule* g_pInputManager = &g_InputManager;
}
