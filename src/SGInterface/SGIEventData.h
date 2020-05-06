#pragma once
#include "SGDefine.h"
#include "FastDelegate.h"
#include "concurrent_queue.h"
#include <memory>
#include <strstream>

namespace SG
{
	Interface SGIEventData;
	typedef uint64_t EventType;
	typedef std::shared_ptr<SGIEventData> IEventDataPtr;
	typedef fastdelegate::FastDelegate1<IEventDataPtr> EventListenerDelegate;
	typedef std::concurrent_queue<IEventDataPtr> ThreadSafeEventQueue;
	//---------------------------------------------------------------------------------------------------------------------
	// IEventData                               - Chapter 11, page 310
	// Base type for event object hierarchy, may be used itself for simplest event notifications such as those that do 
	// not carry additional payload data. If any event needs to propagate with payload data it must be defined separately.
	//---------------------------------------------------------------------------------------------------------------------
	Interface SGIEventData
	{
		//GCC_MEMORY_WATCHER_DECLARATION();
	public:
		virtual ~SGIEventData(void) {}
		virtual const EventType& GetEventType(void) const = 0;
		virtual double GetTimeStamp(void) const = 0;
		virtual void Serialize(std::ostrstream& out) const = 0;
		virtual void Deserialize(std::istrstream& in) = 0;
		virtual IEventDataPtr Copy(void) const = 0;
		virtual const char* GetName(void) const = 0;
	};

	//---------------------------------------------------------------------------------------------------------------------
	// class BaseEventData		- Chapter 11, page 311
	//---------------------------------------------------------------------------------------------------------------------
	class BaseEventData : public SGIEventData
	{
	protected:
		const double m_timeStamp;
	public:
		explicit BaseEventData(const float timeStamp = 0.0f) : m_timeStamp(timeStamp) { }

		// Returns the type of the event
		virtual const EventType& GetEventType(void) const = 0;

		double GetTimeStamp(void) const { return m_timeStamp; }

		// Serializing for network input / output
		//virtual void Serialize(std::ostrstream& out) const { }
		//virtual void Deserialize(std::istrstream& in) { }
	};
}
