#include "SGInputManager.h"
#include "SGOpenGLApplication.h"
#include "AssertFault.h"
#include "SGLog.h"

namespace SG
{
	extern SGIApplication* g_pApp;
}

// TODO: use struct to store data
static float lastX = 0.0f;
static float lastY = 0.0f;
static bool firstMouse = true;

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

	// TODO: use event to send data, not direct call
	static_cast<SG::SGInputManager*>(SG::g_pInputManager)->GetCamera()->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	static_cast<SG::SGInputManager*>(SG::g_pInputManager)->GetCamera()->ProcessMouseScroll(yoffset);
}

int SG::SGInputManager::Initialize()
{
	m_Width = static_cast<SGOpenGLApplication*>(g_pApp)->GetWindowWidth();
	m_Height = static_cast<SGOpenGLApplication*>(g_pApp)->GetWindowHeight();
	m_Window = static_cast<SGOpenGLApplication*>(g_pApp)->GetGLFWWindow();
	ASSERT_TRUE(m_Window);
	m_Camera = new SGCamera(glm::vec3(0.0f, 0.0f, 3.0f));

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);

	LOG_INFO("SGInputManager Initialize");
	return 0;
}

void SG::SGInputManager::Finalize()
{
	delete m_Camera;
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
	// TODO: use time class to calculate this
	m_currentFrame = glfwGetTime();
	m_deltaTime = m_currentFrame - m_lastFrame;
	m_lastFrame = m_currentFrame;

	UpdateCurrentKeys();

	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);

	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
		m_Camera->ProcessKeyboard(FORWARD, m_deltaTime);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
		m_Camera->ProcessKeyboard(BACKWARD, m_deltaTime);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
		m_Camera->ProcessKeyboard(LEFT, m_deltaTime);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
		m_Camera->ProcessKeyboard(RIGHT, m_deltaTime);
	}

	if (CheckOnPress(GLFW_KEY_F)) {
		if (m_isMouseEnable) {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		m_isMouseEnable = !m_isMouseEnable;
	}

	UpdatePreviousKeys();
}
