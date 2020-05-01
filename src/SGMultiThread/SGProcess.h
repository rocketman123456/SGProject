#pragma once
#include "SGLog.h"
#include "SGDefine.h"
#include "AssertFault.h"
#include <memory>

namespace SG
{
	class SGProcess;
	typedef std::shared_ptr<SGProcess> StrongProcessPtr;
	typedef std::weak_ptr<SGProcess> WeakProcessPtr;

	Interface SGProcess
	{
		friend class ProcessManager;
		enum ProcessState
		{
			// start
			Uninitialized = 0,
			Removed,
			// run
			Running,
			Paused,
			// end
			Successed,
			Failed,
			Aborted,
		};
	private:
		ProcessState m_state;  // the current state of the process
		StrongProcessPtr m_pChild;  // the child process, if any

	public:
		// construction
		SGProcess(void);
		virtual ~SGProcess(void);

	protected:
		// interface; these functions should be overridden by the subclass as needed
		virtual void OnInit(void) { m_state = Running; }  // called during the first update; responsible for setting the initial state (typically RUNNING)
		virtual void OnUpdate(unsigned long deltaMs) = 0;  // called every frame
		virtual void OnSuccess(void) { }  // called if the process succeeds (see below)
		virtual void OnFail(void) { }  // called if the process fails (see below)
		virtual void OnAbort(void) { }  // called if the process is aborted (see below)

	public:
		// Functions for ending the process.
		inline void Succeed(void);
		inline void Fail(void);

		// pause
		inline void Pause(void);
		inline void UnPause(void);

		// accessors
		ProcessState GetState(void) const { return m_state; }
		bool IsAlive(void) const { return (m_state == Running || m_state == Paused); }
		bool IsDead(void) const { return (m_state == Successed || m_state == Failed || m_state == Aborted); }
		bool IsRemoved(void) const { return (m_state == Removed); }
		bool IsPaused(void) const { return m_state == Paused; }

		// child functions
		inline void AttachChild(StrongProcessPtr pChild);
		StrongProcessPtr RemoveChild(void);  // releases ownership of the child
		StrongProcessPtr PeekChild(void) { return m_pChild; }  // doesn't release ownership of the child

	private:
		void SetState(ProcessState newState) { m_state = newState; }
	};
}

namespace SG
{
	//---------------------------------------------------------------------------------------------------------------------
	// Inline function definitions
	//---------------------------------------------------------------------------------------------------------------------
	inline void SGProcess::Succeed(void)
	{
		ASSERT_TRUE(m_state == Running || m_state == Paused);
		m_state = Successed;
	}

	inline void SGProcess::Fail(void)
	{
		ASSERT_TRUE(m_state == Running || m_state == Paused);
		m_state = Failed;
	}

	inline void SGProcess::AttachChild(StrongProcessPtr pChild)
	{
		if (m_pChild) {
			m_pChild->AttachChild(pChild);
		}
		else {
			m_pChild = pChild;
		}
	}

	inline void SGProcess::Pause(void)
	{
		if (m_state == Running) {
			m_state = Paused;
		}
		else {
			LOG_DEBUG("Attempting to pause a process that isn't running");
		}
	}

	inline void SGProcess::UnPause(void)
	{
		if (m_state == Paused) {
			m_state = Running;
		}
		else {
			LOG_DEBUG("Attempting to unpause a process that isn't paused");
		}
	}
}
