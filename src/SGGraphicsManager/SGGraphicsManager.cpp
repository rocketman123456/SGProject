#include "SGGraphicsManager.h"

int SG::SGGraphicsManager::Initialize()
{
	m_method = SGOpenGL ? OpenGL : Vulkan;
	int result = 0;
	if (m_method == OpenGL) {
		result = g_pGLGraphicsManager->Initialize();
	}
	else {
		result = g_pVKGraphicsManager->Initialize();
	}

	// add listener
	EventListenerDelegate helloFunc = fastdelegate::MakeDelegate(this, &SG::SGGraphicsManager::HelloEventHandle);
	SGEventManager::GetSingleton().AddListener(helloFunc, Evt_Word::sk_EventType);

	return 0;
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
	std::ostrstream out;
	std::shared_ptr<Evt_Word> p_cast = std::static_pointer_cast<Evt_Word>(event);
	p_cast->Serialize(out);
	word = out.rdbuf()->str();
	word = word.substr(0, out.pcount());
	LOG_DEBUG(word.c_str());
}
