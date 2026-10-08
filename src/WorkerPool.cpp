#include "../header/WorkerPool.h"

#include <iostream>
using namespace std;

WorkerPool::WorkerPool(int workercount)
{
    CreateWorkers(workercount);
}

void WorkerPool::CreateWorkers(int workercount)
{
    for (int i = 1; i <= workercount; ++i)
    {
        string name = "Worker " + to_string(i);
        Worker newWorker(name);
        _Workers.push_back(move(newWorker));
    }
}

optional<reference_wrapper<Worker>> WorkerPool::AcquireWorker()
{
    for (Worker& worker : _Workers)
    {
        if (worker.GetState() == WorkerState::Available)
        {
            worker.MarkBusy();
            return worker;
        }
    }

    return nullopt;
}