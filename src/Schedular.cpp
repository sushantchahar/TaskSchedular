#include "../header/Schedular.h"
#include <iostream>
using namespace std;

Schedular::Schedular(JobQueue& jobQueue, WorkerPool& workerPool, JobRegistry& registry) : _JobQueue(jobQueue), _WorkerPool(workerPool), _JobRegistry(registry) {}

optional<reference_wrapper<Job>> Schedular::SelectJob()
{
    if (_JobQueue.IsEmpty()) return nullopt;
    const int id = _JobQueue.GetJobId();
    auto job = _JobRegistry.GetJob(id);
    return job;
}

void Schedular::DispatchJob()
{
    auto SelectedJob = SelectJob();

    if (SelectedJob)
    {
        auto SelectedWorkerReference = SelectWorker();
        if (!SelectedWorkerReference)
            return;

        Worker& SelectedWorker = SelectedWorkerReference->get();
        SelectedWorker.ReceiveJob(SelectedJob->get());
        SelectedWorker.TriggerWorker();
    }
}

optional<reference_wrapper<Worker>> Schedular::SelectWorker()
{
    return _WorkerPool.AcquireWorker();
}

// temporary for debugging and testing
void Schedular::ScheduleJob()
{
    Schedular::DispatchJob();
}