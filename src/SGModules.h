#pragma once
#include "SGIApplication.h"
#include "SGIRuntimeModule.h"

#include "SGOpenGLApplication.h"
#include "SGOpenGLGraphicsManager.h"
#include "SGEventManager.h"
#include "SGInputManager.h"
#include "SGLog.h"

namespace SG 
{
	extern SGLog* g_pLog;
	extern SGIApplication<SGOpenGLApplication>* g_pApp;
	extern SGIRuntimeModule<SGEventManager>* g_pEventManager;
	extern SGIRuntimeModule<SGInputManager>* g_pInputManager;
	extern SGIRuntimeModule<SGOpenGLGraphicsManager>* g_pGraphicsManager;
}
