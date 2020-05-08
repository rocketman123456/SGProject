#pragma once
#include "SGIApplication.h"
#include "SGIRuntimeModule.h"

#include "SGLog.h"
#include "SGProcessManager.h"
#include "SGEventManager.h"
#include "SGFileManager.h"
#include "SGInputManager.h"
#include "SGTimeFactory.h"

#include "SGApplication.h"
#include "SGGraphicsManager.h"
#include "SGOpenGLApplication.h"
#include "SGOpenGLGraphicsManager.h"
#include "SGVulkanApplication.h"
#include "SGVulkanGraphicsManager.h"

namespace SG 
{
	extern SGLog* g_pLog;
	extern SGIApplication<SGApplication>* g_pApp;
	extern SGIApplication<SGOpenGLApplication>* g_pGLApp;
	extern SGIApplication<SGVulkanApplication>* g_pVKApp;
	extern SGIRuntimeModule<SGProcessManager>* g_pProcessManager;
	extern SGIRuntimeModule<SGEventManager>* g_pEventManager;
	extern SGIRuntimeModule<SGFileManager>* g_pFileManager;
	extern SGIRuntimeModule<SGInputManager>* g_pInputManager;
	extern SGIRuntimeModule<SGGraphicsManager>* g_pGraphicsManager;
	extern SGIRuntimeModule<SGOpenGLGraphicsManager>* g_pGLGraphicsManager;
	extern SGIRuntimeModule<SGVulkanGraphicsManager>* g_pVKGraphicsManager;
}
