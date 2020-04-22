#include "SGWorkerThread.h"
#include "SGLog.h"
#include "AssertFault.h"
#include <iostream>

using namespace SG;
using namespace std;

//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(void)
{
	SGLog::GetSingleton().Initialize();
	std::string name = "Hello";
	LOG_INFO(name.c_str());

	// Worker thread instances
	SGWorkerThread workerThread1("WorkerThread1");
	SGWorkerThread workerThread2("WorkerThread2");

	// Create worker threads
	workerThread1.CreateThread();
	workerThread2.CreateThread();

	// Create message to send to worker thread 1
	UserData* userData1 = new UserData();
	userData1->msg = "Hello world";
	userData1->year = 2019;

	// Create message to send to worker thread 2
	UserData* userData2 = new UserData();
	userData2->msg = "Goodbye world";
	userData2->year = 2019;

	// Post the message to worker thread 1
	workerThread1.PostMsg(userData1);
	// Post the message to worker thread 2
	workerThread2.PostMsg(userData2);

	// Give time for messages processing on worker threads
	this_thread::sleep_for(5s);

	workerThread1.ExitThread();
	workerThread2.ExitThread();

	return 0;
}
