#include "SGEventManager.h"
#include "SGLog.h"
#include "AssertFault.h"

namespace SG
{
	GenericObjectFactory<SGIEventData, EventType> g_eventFactory;
}

int SG::SGEventManager::Initialize()
{
	m_MaxMS = 30;
	m_Name = "SGEventManager";
	m_activeQueue = 0;
	m_timer = SGTimeFactory::GetTimer(Resolution::Normal);
	LOG_INFO("SGEventManager Initialize");
	return 0;
}

void SG::SGEventManager::Finalize()
{
	LOG_INFO("SGEventManager Finalize");
}

void SG::SGEventManager::Tick()
{
	m_timer->Update();
	Update(m_MaxMS);
}

bool SG::SGEventManager::AddListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	LOG_INFO("Attempting to add delegate function for event type: %s", std::to_string(type).c_str());

	EventListenerList& eventListenerList = m_eventListeners[type];  // this will find or create the entry
	for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
	{
		if (eventDelegate == (*it))
		{
			LOG_WARN("Attempting to double-register a delegate");
			return false;
		}
	}

	eventListenerList.push_back(eventDelegate);
	LOG_INFO("Successfully added delegate for event type: %s", std::to_string(type).c_str());

	return true;
}

bool SG::SGEventManager::RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	LOG_INFO("Attempting to remove delegate function from event type: %s", std::to_string(type).c_str());
	bool success = false;

	auto findIt = m_eventListeners.find(type);
	if (findIt != m_eventListeners.end())
	{
		EventListenerList& listeners = findIt->second;
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (eventDelegate == (*it))
			{
				listeners.erase(it);
				LOG_INFO("Successfully removed delegate function from event type: %s", std::to_string(type).c_str());
				success = true;
				break;  // we don't need to continue because it should be impossible for the same delegate function to be registered for the same event more than once
			}
		}
	}

	return success;
}

bool SG::SGEventManager::TriggerEvent(const IEventDataPtr& pEvent) const
{
	LOG_INFO(("Attempting to trigger event " + std::string(pEvent->GetName())).c_str());
	bool processed = false;

	auto findIt = m_eventListeners.find(pEvent->GetEventType());
	if (findIt != m_eventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;
		for (EventListenerList::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
		{
			EventListenerDelegate listener = (*it);
			LOG_INFO(("Sending Event " + std::string(pEvent->GetName()) + " to delegate.").c_str());
			listener(pEvent);  // call the delegate
			processed = true;
		}
	}

	return processed;
}

bool SG::SGEventManager::QueueEvent(const IEventDataPtr& pEvent)
{
	ASSERT_TRUE(m_activeQueue >= 0);
	ASSERT_TRUE(m_activeQueue < EVENTMANAGER_NUM_QUEUES);

	// make sure the event is valid
	if (!pEvent)
	{
		LOG_ERROR("Invalid event in QueueEvent()");
		return false;
	}

	LOG_INFO(("Attempting to queue event: " + std::string(pEvent->GetName())).c_str());

	auto findIt = m_eventListeners.find(pEvent->GetEventType());
	if (findIt != m_eventListeners.end())
	{
		m_queues[m_activeQueue].push_back(pEvent);
		LOG_INFO(("Successfully queued event: " + std::string(pEvent->GetName())).c_str());
		return true;
	}
	else
	{
		LOG_INFO(("Skipping event since there are no delegates registered to receive it: " + std::string(pEvent->GetName())).c_str());
		return false;
	}
}

bool SG::SGEventManager::ThreadSafeQueueEvent(const IEventDataPtr& pEvent)
{
	m_realtimeEventQueue.push(pEvent);
	return true;
}

bool SG::SGEventManager::AbortEvent(const EventType& type, bool allOfType)
{
	ASSERT_TRUE(m_activeQueue >= 0);
	ASSERT_TRUE(m_activeQueue < EVENTMANAGER_NUM_QUEUES);

	bool success = false;
	EventListenerMap::iterator findIt = m_eventListeners.find(type);

	if (findIt != m_eventListeners.end())
	{
		EventQueue& eventQueue = m_queues[m_activeQueue];
		auto it = eventQueue.begin();
		while (it != eventQueue.end())
		{
			// Removing an item from the queue will invalidate the iterator, so have it point to the next member.  All
			// work inside this loop will be done using thisIt.
			auto thisIt = it;
			++it;

			if ((*thisIt)->GetEventType() == type)
			{
				eventQueue.erase(thisIt);
				success = true;
				if (!allOfType)
					break;
			}
		}
	}

	return success;
}

bool SG::SGEventManager::Update(uint64_t maxMillis)
{
	uint64_t currMs = m_timer->GetElapse();
	uint64_t maxMs = ((maxMillis == kINFINITE) ? (kINFINITE) : (currMs + maxMillis));

	// This section added to handle events from other threads.  Check out Chapter 20.
	IEventDataPtr pRealtimeEvent;
	while (m_realtimeEventQueue.try_pop(pRealtimeEvent))
	{
		QueueEvent(pRealtimeEvent);

		currMs = m_timer->GetElapse();
		if (maxMillis != kINFINITE)
		{
			if (currMs >= maxMs)
			{
				LOG_ERROR("A realtime process is spamming the event manager!");
			}
		}
	}

	// swap active queues and clear the new queue after the swap
	int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_NUM_QUEUES;
	m_queues[m_activeQueue].clear();

	//LOG_INFO(("Processing Event Queue " + std::to_string(queueToProcess) + "; " + std::to_string((unsigned long)m_queues[queueToProcess].size()) + " events to process").c_str());

	// Process the queue
	while (!m_queues[queueToProcess].empty())
	{
		// pop the front of the queue
		IEventDataPtr pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();
		LOG_INFO(("\t\tProcessing Event " + std::string(pEvent->GetName())).c_str());

		const EventType& eventType = pEvent->GetEventType();

		// find all the delegate functions registered for this event
		auto findIt = m_eventListeners.find(eventType);
		if (findIt != m_eventListeners.end())
		{
			const EventListenerList& eventListeners = findIt->second;
			LOG_INFO(("\t\tFound " + std::to_string((unsigned long)eventListeners.size()) + " delegates").c_str());

			// call each listener
			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
			{
				EventListenerDelegate listener = (*it);
				LOG_INFO(("\t\tSending event " + std::string(pEvent->GetName()) + " to delegate").c_str());
				listener(pEvent);
			}
		}

		// check to see if time ran out
		currMs = m_timer->GetElapse();
		if (maxMillis != kINFINITE && currMs >= maxMs)
		{
			LOG_INFO("Aborting event processing; time ran out");
			break;
		}
	}

	// If we couldn't process all of the events, push the remaining events to the new active queue.
	// Note: To preserve sequencing, go back-to-front, inserting them at the head of the active queue
	bool queueFlushed = (m_queues[queueToProcess].empty());
	if (!queueFlushed)
	{
		while (!m_queues[queueToProcess].empty())
		{
			IEventDataPtr pEvent = m_queues[queueToProcess].back();
			m_queues[queueToProcess].pop_back();
			m_queues[m_activeQueue].push_front(pEvent);
		}
	}

	return queueFlushed;
}


