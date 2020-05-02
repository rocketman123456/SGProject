#include "SGApplication.h"

int SG::SGApplication::Initialize()
{
	int result = 0;
	m_Type = SGOpenGL ? OpenGLApp : VulkanApp;
	if (m_Type == OpenGLApp) {
		result = g_pGLApp->Initialize();
		m_Width = static_cast<SGOpenGLApplication*>(g_pGLApp)->GetWindowWidth();
		m_Height = static_cast<SGOpenGLApplication*>(g_pGLApp)->GetWindowHeight();
		m_Window = static_cast<SGOpenGLApplication*>(g_pGLApp)->GetGLFWWindow();
	}
	else {
		result = g_pVKApp->Initialize();
		m_Width = static_cast<SGVulkanApplication*>(g_pVKApp)->GetWindowWidth();
		m_Height = static_cast<SGVulkanApplication*>(g_pVKApp)->GetWindowHeight();
		m_Window = static_cast<SGVulkanApplication*>(g_pVKApp)->GetGLFWWindow();
	}
	LOG_INFO("SGApplication Initialize");
	return result;
}

void SG::SGApplication::Finalize()
{
	if (m_Type == OpenGLApp) {
		g_pGLApp->Finalize();
	}
	else {
		g_pVKApp->Finalize();
	}
	LOG_INFO("SGApplication Finalize");
}

void SG::SGApplication::Tick()
{
	if (m_Type == OpenGLApp) {
		g_pGLApp->Tick();
	}
	else {
		g_pVKApp->Tick();
	}
}

bool SG::SGApplication::IsQuit()
{
	bool result = false;
	if (m_Type == OpenGLApp) {
		result = g_pGLApp->IsQuit();
	}
	else {
		result = g_pVKApp->IsQuit();
	}
	return result;
}
