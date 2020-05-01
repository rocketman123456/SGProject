// code from https://www.codeproject.com/Articles/1169105/Cplusplus-std-thread-Event-Loop-with-Message-Queue
#pragma once
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace SG
{
    struct UserData
    {
        std::string msg;
        int year;
    };

    struct ThreadMsg;

    class SGWorkerThread
    {
    public:
        /// Constructor
        SGWorkerThread(const std::string& threadName);

        /// Destructor
        ~SGWorkerThread();

        /// Called once to create the worker thread
        /// @return TRUE if thread is created. FALSE otherwise.
        bool CreateThread();

        /// Called once a program exit to exit the worker thread
        void ExitThread();

        /// Get the ID of this thread instance
        /// @return The worker thread ID
        std::thread::id GetThreadId();

        /// Get the ID of the currently executing thread
        /// @return The current thread ID
        static std::thread::id GetCurrentThreadId();

        /// Add a message to thread queue.
        /// @param[in] data - thread specific information created on the heap using operator new.
        void PostMsg(const UserData* data);

    protected:
        SGWorkerThread(const SGWorkerThread&) = delete;
        SGWorkerThread& operator=(const SGWorkerThread&) = delete;

        /// Entry point for the worker thread
        void Process();

        /// Entry point for timer thread
        void TimerThread();

        std::thread* m_thread;
        std::queue<ThreadMsg*> m_queue;
        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::atomic<bool> m_timerExit;
        std::string THREAD_NAME;
    };
}
