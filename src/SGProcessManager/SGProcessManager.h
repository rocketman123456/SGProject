#include "SGIRuntimeModule.h"
#include "SGTimeFactory.h"
#include "SGProcess.h"
#include <list>

namespace SG
{
	class SGProcessManager : implements SGIRuntimeModule<SGProcessManager>
	{
		typedef std::list<StrongProcessPtr> ProcessList;
	protected:
		ProcessList m_processList;
		StrongTimePtr m_timer;

	public:
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();

		// interface
		uint32_t UpdateProcesses(uint64_t deltaMs);  // updates all attached processes
		WeakProcessPtr AttachProcess(StrongProcessPtr pProcess);  // attaches a process to the process mgr
		void AbortAllProcesses(bool immediate);

		// accessors
		uint32_t GetProcessCount(void) const { return m_processList.size(); }

	private:
		void ClearAllProcesses(void);  // should only be called by the destructor
	};
}
