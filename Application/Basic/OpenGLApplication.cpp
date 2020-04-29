#include "SGOpenGLApplication.h"
#include "SGOpenGLGraphicsManager.h"
#include "SGEventManager.h"
#include "SGInputManager.h"

namespace SG
{
	SGOpenGLApplication g_App;
	SGEventManager g_EventManager;
	SGInputManager g_InputManager;
	SGOpenGLGraphicsManager g_GraphicsManager;

	SGIApplication* g_pApp = &g_App;
	SGIRuntimeModule* g_pEventManager = &g_EventManager;
	SGIRuntimeModule* g_pGraphicsManager = &g_GraphicsManager;
	SGIRuntimeModule* g_pInputManager = &g_InputManager;
}
