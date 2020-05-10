#include "SGGraphicsManager.h"

int SG::SGGraphicsManager::Initialize()
{
	m_Camera = StrongCameraPtr(new SGCamera(glm::vec3(0.0f, 0.0f, 3.0f)));

	// add listener
	EventListenerDelegate helloFunc = fastdelegate::MakeDelegate(this, &SG::SGGraphicsManager::HelloEventHandle);
	SGEventManager::GetSingleton().AddListener(helloFunc, Evt_Word::sk_EventType);
	EventListenerDelegate cameramoveFunc = fastdelegate::MakeDelegate(this, &SG::SGGraphicsManager::CameraMoveEventHandle);
	SGEventManager::GetSingleton().AddListener(cameramoveFunc, Evt_CameraMove::sk_EventType);
	EventListenerDelegate camerascrollFunc = fastdelegate::MakeDelegate(this, &SG::SGGraphicsManager::CameraScrollEventHandle);
	SGEventManager::GetSingleton().AddListener(camerascrollFunc, Evt_CameraScroll::sk_EventType);
	EventListenerDelegate cameraposmoveFunc = fastdelegate::MakeDelegate(this, &SG::SGGraphicsManager::CameraPosMoveEventHandle);
	SGEventManager::GetSingleton().AddListener(cameraposmoveFunc, Evt_CameraPosMove::sk_EventType);

	m_method = SGOpenGL ? OpenGL : Vulkan;
	int result = 0;
	if (m_method == OpenGL) {
		result = g_pGLGraphicsManager->Initialize();
	}
	else {
		result = g_pVKGraphicsManager->Initialize();
	}

	LOG_INFO("SGGraphicsManager Initialize");
	return result;
}

void SG::SGGraphicsManager::Finalize()
{
	if (m_method == OpenGL) {
		g_pGLGraphicsManager->Finalize();
	}
	else {
		g_pVKGraphicsManager->Finalize();
	}

	// remove listener
	EventListenerDelegate helloFunc = fastdelegate::MakeDelegate(this, &SG::SGGraphicsManager::HelloEventHandle);
	SGEventManager::GetSingleton().RemoveListener(helloFunc, Evt_Word::sk_EventType);
	EventListenerDelegate cameramoveFunc = fastdelegate::MakeDelegate(this, &SG::SGGraphicsManager::CameraMoveEventHandle);
	SGEventManager::GetSingleton().RemoveListener(cameramoveFunc, Evt_CameraMove::sk_EventType);
	EventListenerDelegate camerascrollFunc = fastdelegate::MakeDelegate(this, &SG::SGGraphicsManager::CameraScrollEventHandle);
	SGEventManager::GetSingleton().RemoveListener(camerascrollFunc, Evt_CameraScroll::sk_EventType);
	EventListenerDelegate cameraposmoveFunc = fastdelegate::MakeDelegate(this, &SG::SGGraphicsManager::CameraPosMoveEventHandle);
	SGEventManager::GetSingleton().RemoveListener(cameraposmoveFunc, Evt_CameraPosMove::sk_EventType);

	LOG_INFO("SGGraphicsManager Finalize");
}

void SG::SGGraphicsManager::Tick()
{
	if (m_method == OpenGL) {
		g_pGLGraphicsManager->Tick();
	}
	else {
		g_pVKGraphicsManager->Tick();
	}
}

void SG::SGGraphicsManager::HelloEventHandle(IEventDataPtr event)
{
	std::string word;
	std::shared_ptr<Evt_Word> p_cast = std::static_pointer_cast<Evt_Word>(event);
	word = p_cast->m_output;
	LOG_DEBUG(word.c_str());
}

void SG::SGGraphicsManager::CameraMoveEventHandle(IEventDataPtr event)
{
	double x, y;
	std::shared_ptr<Evt_CameraMove> p_cast = std::static_pointer_cast<Evt_CameraMove>(event);
	x = p_cast->x_offset;
	y = p_cast->y_offset;
	m_Camera->ProcessMouseMovement(x, y);
}

void SG::SGGraphicsManager::CameraScrollEventHandle(IEventDataPtr event)
{
	double yoffset;
	std::shared_ptr<Evt_CameraScroll> p_cast = std::static_pointer_cast<Evt_CameraScroll>(event);
	yoffset = p_cast->scroll;
	m_Camera->ProcessMouseScroll(yoffset);
}

void SG::SGGraphicsManager::CameraPosMoveEventHandle(IEventDataPtr event)
{
	double dt;
	Camera_Movement move;
	std::shared_ptr<Evt_CameraPosMove> p_cast = std::static_pointer_cast<Evt_CameraPosMove>(event);
	dt = p_cast->deltaTime;
	move = p_cast->move;
	m_Camera->ProcessKeyboard(move, dt);
}
