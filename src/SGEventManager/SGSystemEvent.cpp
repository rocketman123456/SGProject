#include "SGSystemEvent.h"
#include "SGLog.h"
using namespace SG;

const EventType SG::Evt_Word::sk_EventType(0x950108bb);

const EventType& SG::Evt_Word::GetEventType(void) const
{
	return sk_EventType;
}

float SG::Evt_Word::GetTimeStamp(void) const
{
	return 0.0f;
}

void SG::Evt_Word::Serialize(std::ostrstream& out) const
{
	// must use space to divide
	out << m_output;
	LOG_TRACE("Evt_Word out %s", m_output.c_str());
}

void SG::Evt_Word::Deserialize(std::istrstream& in)
{
	in >> m_output;
	LOG_TRACE("Evt_Word in %s", m_output.c_str());
}

IEventDataPtr SG::Evt_Word::Copy(void) const
{
	return IEventDataPtr(SG_NEW Evt_Word(m_output));
}

const char* SG::Evt_Word::GetName(void) const
{
	return "Hello_Event";
}
