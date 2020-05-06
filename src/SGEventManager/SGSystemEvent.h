#pragma once
#include "SGIEventData.h"
#include "SGMemoryMacros.h"
#include <string>

namespace SG
{
	class Evt_Word : implements BaseEventData
	{
	protected:
		std::string m_output;
	public:
		static const EventType sk_EventType;
		explicit Evt_Word(const std::string& out = "Hello") :m_output(out) {}
		virtual const EventType& GetEventType(void) const override;
		virtual float GetTimeStamp(void) const override;
		virtual void Serialize(std::ostrstream& out) const override;
		virtual void Deserialize(std::istrstream& in) override;
		virtual IEventDataPtr Copy(void) const override;
		virtual const char* GetName(void) const override;
	};
}
