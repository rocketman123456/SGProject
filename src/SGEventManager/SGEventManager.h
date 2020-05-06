#pragma once
#include "SGIRuntimeModule.h"
#include "SGIEventData.h"
#include "SGTimeFactory.h"
#include "GenericObjectFactory.h"

#include <string>
#include <map>
#include <list>

namespace SG
{
	extern GenericObjectFactory<SGIEventData, EventType> g_eventFactory;
	#define REGISTER_EVENT(eventClass) g_eventFactory.Register<eventClass>(eventClass::sk_EventType)
	#define CREATE_EVENT(eventType) g_eventFactory.Create(eventType)
	const uint32_t EVENTMANAGER_NUM_QUEUES = 2;

	template<typename T>
	class SGIEventManager : implements SGIRuntimeModule<T>
	{
	public:
		enum eConstants { kINFINITE = 0xffffffff };

		virtual int Initialize() = 0;
		virtual void Finalize() = 0;
		virtual void Tick() = 0;

		// Registers a delegate function that will get called when the event type is triggered.  Returns true if 
		// successful, false if not.
		virtual bool AddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

		// Removes a delegate / event type pairing from the internal tables.  Returns false if the pairing was not found.
		virtual bool RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

		// Fire off event NOW.  This bypasses the queue entirely and immediately calls all delegate functions registered 
		// for the event.
		virtual bool TriggerEvent(const IEventDataPtr& pEvent) const = 0;

		// Fire off event.  This uses the queue and will call the delegate function on the next call to VTick(), assuming
		// there's enough time.
		virtual bool QueueEvent(const IEventDataPtr& pEvent) = 0;
		virtual bool ThreadSafeQueueEvent(const IEventDataPtr& pEvent) = 0;

		// Find the next-available instance of the named event type and remove it from the processing queue.  This 
		// may be done up to the point that it is actively being processed ...  e.g.: is safe to happen during event
		// processing itself.
		//
		// if allOfType is true, then all events of that type are cleared from the input queue.
		//
		// returns true if the event was found and removed, false otherwise
		virtual bool AbortEvent(const EventType& type, bool allOfType = false) = 0;

		// Allow for processing of any queued messages, optionally specify a processing time limit so that the event 
		// processing does not take too long. Note the danger of using this artificial limiter is that all messages 
		// may not in fact get processed.
		//
		// returns true if all messages ready for processing were completed, false otherwise (e.g. timeout )
		virtual bool Update(uint64_t maxMillis = kINFINITE) = 0;
	};

	class SGEventManager : public SGIEventManager<SGEventManager>
	{
		typedef std::list<EventListenerDelegate> EventListenerList;
		typedef std::map<EventType, EventListenerList> EventListenerMap;
		typedef std::list<IEventDataPtr> EventQueue;
	protected:
		std::string m_Name;
		StrongTimePtr m_timer;
		EventListenerMap m_eventListeners;
		EventQueue m_queues[EVENTMANAGER_NUM_QUEUES];
		int32_t m_activeQueue;  // index of actively processing queue; events enque to the opposing queue

		ThreadSafeEventQueue m_realtimeEventQueue;

	public:
		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;

		virtual bool AddListener(const EventListenerDelegate& eventDelegate, const EventType& type) override;
		virtual bool RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) override;

		virtual bool TriggerEvent(const IEventDataPtr& pEvent) const override;
		virtual bool QueueEvent(const IEventDataPtr& pEvent) override;
		virtual bool ThreadSafeQueueEvent(const IEventDataPtr& pEvent) override;
		virtual bool AbortEvent(const EventType& type, bool allOfType = false) override;

		virtual bool Update(uint64_t maxMillis = kINFINITE) override;
	};

	extern SGIRuntimeModule<SGEventManager>* g_pEventManager;
}
