#include "SGBaseApplication.h"
#include "SGGraphicsManager.h"

namespace SG
{
	SGBaseApplication g_App;
	SGIApplication* g_pApp = &g_App;
	SGGraphicsManager g_GraphicsManager;
	SGIRuntimeModule* g_pGraphicsManager = &g_GraphicsManager;
}
