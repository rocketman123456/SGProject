#pragma once
#include "SGIRuntimeModule.h"
#include "SGOpenGLGraphicsManager.h"
#include "SGVulkanGraphicsManager.h"
#include "SGEventManager.h"
#include "SGSystemEvent.h"

namespace SG
{
	extern SGIRuntimeModule<SGOpenGLGraphicsManager>* g_pGLGraphicsManager;
	extern SGIRuntimeModule<SGVulkanGraphicsManager>* g_pVKGraphicsManager;
	enum RenderMethod
	{
		OpenGL = 0,
		Vulkan,
	};
	// TODO: use uniform graphics manager to render
	class SGGraphicsManager : implements SGIRuntimeModule<SGGraphicsManager>
	{
	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();

		void HelloEventHandle(IEventDataPtr event);
	protected:
		RenderMethod m_method;
	};
}