#include "SGOpenGLApplication.h"
#include "SGOpenGLGraphicsManager.h"
#include "SGEventManager.h"
#include "SGInputManager.h"
#include "SGLog.h"

namespace SG
{
	SGLog* g_pLog = &SGLog::GetSingleton();
	SGIApplication<SGOpenGLApplication>* g_pApp = &SGOpenGLApplication::GetSingleton();
	SGIRuntimeModule<SGEventManager>* g_pEventManager = &SGEventManager::GetSingleton();
	SGIRuntimeModule<SGInputManager>* g_pInputManager = &SGInputManager::GetSingleton();
	SGIRuntimeModule<SGOpenGLGraphicsManager>* g_pGraphicsManager = &SGOpenGLGraphicsManager::GetSingleton();
}
