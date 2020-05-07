#include "SGProcessManager.h"
#include "SGLog.h"
using namespace SG;

int SG::SGProcessManager::Initialize()
{
    m_timer = SGTimeFactory::GetTimer();
    m_timer->Initialize(Resolution::High);
    LOG_INFO("SGProcessManager Initialize");
    return 0;
}

void SG::SGProcessManager::Finalize()
{
    ClearAllProcesses();
    LOG_INFO("SGProcessManager Finalize");
}

void SG::SGProcessManager::Tick()
{
    static double dt = 0.0;
    m_timer->Update();
    UpdateProcesses(dt);
    dt = m_timer->GetElapse();
}

//---------------------------------------------------------------------------------------------------------------------
// The process update tick.  Called every logic tick.  This function returns the number of process chains that 
// succeeded in the upper 32 bits and the number of process chains that failed or were aborted in the lower 32 bits.
//---------------------------------------------------------------------------------------------------------------------
uint32_t SGProcessManager::UpdateProcesses(uint64_t deltaMs)
{
    uint32_t successCount = 0;
    uint32_t failCount = 0;

    ProcessList::iterator it = m_processList.begin();
    while (it != m_processList.end())
    {
        // grab the next process
        StrongProcessPtr pCurrProcess = (*it);

        // save the iterator and increment the old one in case we need to remove this process from the list
        ProcessList::iterator thisIt = it;
        ++it;

        // process is uninitialized, so initialize it
        if (pCurrProcess->GetState() == SGProcess::Uninitialized)
            pCurrProcess->OnInit();

        // give the process an update tick if it's running
        if (pCurrProcess->GetState() == SGProcess::Running)
            pCurrProcess->OnUpdate(deltaMs);

        // check to see if the process is dead
        if (pCurrProcess->IsDead())
        {
            // run the appropriate exit function
            switch (pCurrProcess->GetState())
            {
            case SGProcess::Successed:
            {
                pCurrProcess->OnSuccess();
                StrongProcessPtr pChild = pCurrProcess->RemoveChild();
                if (pChild)
                    AttachProcess(pChild);
                else
                    ++successCount;  // only counts if the whole chain completed
                break;
            }

            case SGProcess::Failed:
            {
                pCurrProcess->OnFail();
                ++failCount;
                break;
            }

            case SGProcess::Aborted:
            {
                pCurrProcess->OnAbort();
                ++failCount;
                break;
            }
            }

            // remove the process and destroy it
            m_processList.erase(thisIt);
        }
    }

    return ((successCount << 16) | failCount);
}

//---------------------------------------------------------------------------------------------------------------------
// Attaches the process to the process list so it can be run on the next update.
//---------------------------------------------------------------------------------------------------------------------
WeakProcessPtr SGProcessManager::AttachProcess(StrongProcessPtr pProcess)
{
    m_processList.push_front(pProcess);
    return WeakProcessPtr(pProcess);
}

//---------------------------------------------------------------------------------------------------------------------
// Clears all processes (and DOESN'T run any exit code)
//---------------------------------------------------------------------------------------------------------------------
void SGProcessManager::ClearAllProcesses(void)
{
    m_processList.clear();
}

//---------------------------------------------------------------------------------------------------------------------
// Aborts all processes.  If immediate == true, it immediately calls each ones OnAbort() function and destroys all 
// the processes.
//---------------------------------------------------------------------------------------------------------------------
void SGProcessManager::AbortAllProcesses(bool immediate)
{
    ProcessList::iterator it = m_processList.begin();
    while (it != m_processList.end())
    {
        ProcessList::iterator tempIt = it;
        ++it;

        StrongProcessPtr pProcess = *tempIt;
        if (pProcess->IsAlive())
        {
            pProcess->SetState(SGProcess::Aborted);
            if (immediate)
            {
                pProcess->OnAbort();
                m_processList.erase(tempIt);
            }
        }
    }
}
