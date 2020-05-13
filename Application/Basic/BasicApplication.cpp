#include "SGOpenGLApplication.h"
#include "SGOpenGLGraphicsManager.h"
#include "SGVulkanApplication.h"
#include "SGVulkanGraphicsManager.h"
#include "SGGraphicsManager.h"
#include "SGApplication.h"
#include "SGEventManager.h"
#include "SGFileManager.h"
#include "SGInputManager.h"
#include "SGProcessManager.h"
#include "SGTimeFactory.h"
#include "SGLog.h"

namespace SG
{
	SGLog* g_pLog = &SGLog::GetSingleton();
	SGIApplication<SGApplication>* g_pApp = &SGApplication::GetSingleton();
	SGIApplication<SGOpenGLApplication>* g_pGLApp = &SGOpenGLApplication::GetSingleton();
	SGIApplication<SGVulkanApplication>* g_pVKApp = &SGVulkanApplication::GetSingleton();

	SGIRuntimeModule<SGProcessManager>* g_pProcessManager = &SGProcessManager::GetSingleton();
	SGIRuntimeModule<SGEventManager>* g_pEventManager = &SGEventManager::GetSingleton();
	SGIRuntimeModule<SGFileManager>* g_pFileManager = &SGFileManager::GetSingleton();
	SGIRuntimeModule<SGInputManager>* g_pInputManager = &SGInputManager::GetSingleton();

	SGIRuntimeModule<SGGraphicsManager>* g_pGraphicsManager = &SGGraphicsManager::GetSingleton();
	SGIRuntimeModule<SGOpenGLGraphicsManager>* g_pGLGraphicsManager = &SGOpenGLGraphicsManager::GetSingleton();
	SGIRuntimeModule<SGVulkanGraphicsManager>* g_pVKGraphicsManager = &SGVulkanGraphicsManager::GetSingleton();
}
