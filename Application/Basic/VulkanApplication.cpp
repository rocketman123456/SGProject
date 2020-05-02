#include "SGVulkanApplication.h"
#include "SGVulkanGraphicsManager.h"
#include "SGEventManager.h"
#include "SGInputManager.h"
#include "SGLog.h"

namespace SG
{
	SGVulkanApplication g_App;
	SGEventManager g_EventManager;
	SGInputManager g_InputManager;
	SGVulkanGraphicsManager g_GraphicsManager;

	SGLog* g_pLog = &SGLog::GetSingleton();
	SGIApplication* g_pApp = &g_App;
	SGIRuntimeModule* g_pEventManager = &g_EventManager;
	SGIRuntimeModule* g_pGraphicsManager = &g_GraphicsManager;
	SGIRuntimeModule* g_pInputManager = &g_InputManager;
}
