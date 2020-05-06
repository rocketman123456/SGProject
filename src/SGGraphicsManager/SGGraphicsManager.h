#pragma once
#include "SGIRuntimeModule.h"
#include "SGOpenGLGraphicsManager.h"
#include "SGVulkanGraphicsManager.h"
#include "SGEventManager.h"
#include "SGSystemEvent.h"
#include "SGCamera.h"

namespace SG
{
	extern SGIRuntimeModule<SGOpenGLGraphicsManager>* g_pGLGraphicsManager;
	extern SGIRuntimeModule<SGVulkanGraphicsManager>* g_pVKGraphicsManager;
	enum RenderMethod
	{
		OpenGL = 0,
		Vulkan,
	};
	
	using StrongCameraPtr = std::shared_ptr<SGCamera>;
	using WeakCameraPtr = std::weak_ptr<SGCamera>;

	class SGGraphicsManager : implements SGIRuntimeModule<SGGraphicsManager>
	{
	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();

		inline WeakCameraPtr GetCamera() { return WeakCameraPtr(m_Camera); }

		void HelloEventHandle(IEventDataPtr event);
		void CameraMoveEventHandle(IEventDataPtr event);
		void CameraScrollEventHandle(IEventDataPtr event);
		void CameraPosMoveEventHandle(IEventDataPtr event);
	protected:
		RenderMethod m_method;
		StrongCameraPtr m_Camera;
	};
}