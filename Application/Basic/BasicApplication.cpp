#include "SGOpenGLApplication.h"
#include "SGOpenGLGraphicsManager.h"
#include "SGVulkanApplication.h"
#include "SGVulkanGraphicsManager.h"
#include "SGGraphicsManager.h"
#include "SGEventManager.h"
#include "SGInputManager.h"
#include "SGTimeManager.h"
#include "SGLog.h"

namespace SG
{
	SGLog* g_pLog = &SGLog::GetSingleton();
	SGIApplication<SGOpenGLApplication>* g_pGLApp = &SGOpenGLApplication::GetSingleton();
	SGIApplication<SGVulkanApplication>* g_pVKApp = &SGVulkanApplication::GetSingleton();
	SGIRuntimeModule<SGTimeManager>* g_pTimeManager = &SGTimeManager::GetSingleton();
	SGIRuntimeModule<SGEventManager>* g_pEventManager = &SGEventManager::GetSingleton();
	SGIRuntimeModule<SGInputManager>* g_pInputManager = &SGInputManager::GetSingleton();
	SGIRuntimeModule<SGGraphicsManager>* g_pGraphicsManager = &SGGraphicsManager::GetSingleton();
	SGIRuntimeModule<SGOpenGLGraphicsManager>* g_pGLGraphicsManager = &SGOpenGLGraphicsManager::GetSingleton();
	SGIRuntimeModule<SGVulkanGraphicsManager>* g_pVKGraphicsManager = &SGVulkanGraphicsManager::GetSingleton();
}
