#include "SGInputManager.h"
#include "SGApplication.h"
#include "AssertFault.h"
#include "SGLog.h"

namespace SG
{
	extern SGIApplication<SGApplication>* g_pApp;
}

// TODO: use struct to store data
static float lastX = 0.0f;
static float lastY = 0.0f;
static bool firstMouse = true;
static bool mouseControl = true;

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (mouseControl) {
		std::shared_ptr<SG::Evt_CameraMove> pCamera(SG_NEW SG::Evt_CameraMove(xoffset, yoffset));
		SG::SGEventManager::GetSingleton().QueueEvent(pCamera);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	std::shared_ptr<SG::Evt_CameraScroll> pCamera(SG_NEW SG::Evt_CameraScroll(yoffset));
	SG::SGEventManager::GetSingleton().QueueEvent(pCamera);
}

int SG::SGInputManager::Initialize()
{
	m_Width = static_cast<SGApplication*>(g_pApp)->GetWindowWidth();
	m_Height = static_cast<SGApplication*>(g_pApp)->GetWindowHeight();
	m_Window = static_cast<SGApplication*>(g_pApp)->GetGLFWWindow();
	ASSERT_TRUE(m_Window);

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);

	m_timer = SGTimeFactory::GetTimer();
	m_timer->Initialize(Resolution::High);
	LOG_INFO("SGInputManager Initialize");
	return 0;
}

void SG::SGInputManager::Finalize()
{
	LOG_INFO("SGInputManager Finalize");
}

void SG::SGInputManager::UpdateCurrentKeys()
{
	for (int i = 39; i < 93; ++i)
	{
		m_current[i] = glfwGetKey(m_Window, i);
	}
}

void SG::SGInputManager::UpdatePreviousKeys()
{
	for (int i = 39; i < 93; ++i)
	{
		m_previous[i] = m_current[i];
	}
}

bool SG::SGInputManager::CheckOnPress(int Key)
{
	bool result = false;
	result = m_current[Key] == GLFW_PRESS && m_previous[Key] == GLFW_RELEASE;
	return result;
}

bool SG::SGInputManager::CheckOnRelease(int Key)
{
	bool result = false;
	result = m_current[Key] == GLFW_RELEASE && m_previous[Key] == GLFW_PRESS;
	return result;
}

void SG::SGInputManager::Tick()
{
	m_deltaTime = m_timer->GetElapse();
	m_timer->Update();
	UpdateCurrentKeys();

	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_Window, true);
	}

	Camera_Movement move = FORWARD;
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
		move = FORWARD;
		std::shared_ptr<SG::Evt_CameraPosMove> pCamera(SG_NEW SG::Evt_CameraPosMove(move, m_deltaTime));
		SG::SGEventManager::GetSingleton().QueueEvent(pCamera);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
		move = BACKWARD;
		std::shared_ptr<SG::Evt_CameraPosMove> pCamera(SG_NEW SG::Evt_CameraPosMove(move, m_deltaTime));
		SG::SGEventManager::GetSingleton().QueueEvent(pCamera);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
		move = LEFT;
		std::shared_ptr<SG::Evt_CameraPosMove> pCamera(SG_NEW SG::Evt_CameraPosMove(move, m_deltaTime));
		SG::SGEventManager::GetSingleton().QueueEvent(pCamera);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
		move = RIGHT;
		std::shared_ptr<SG::Evt_CameraPosMove> pCamera(SG_NEW SG::Evt_CameraPosMove(move, m_deltaTime));
		SG::SGEventManager::GetSingleton().QueueEvent(pCamera);
	}

	if (CheckOnPress(GLFW_KEY_E)) {
		std::string word = "Hello_World";
		std::istrstream in(word.c_str());
		std::shared_ptr<SG::Evt_Word> pHello(SG_NEW SG::Evt_Word());
		pHello->Deserialize(in);
		SGEventManager::GetSingleton().QueueEvent(pHello);
	}

	if (CheckOnPress(GLFW_KEY_F)) {
		if (m_isMouseEnable) {
			mouseControl = false;
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			mouseControl = true;;
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		m_isMouseEnable = !m_isMouseEnable;
	}

	UpdatePreviousKeys();
}
