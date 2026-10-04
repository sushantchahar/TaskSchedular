#include "../header/Schedular.h"
using namespace std;

Schedular::Schedular(JobQueue& jobQueue, Worker& worker, JobRegistry& registry) : _JobQueue(jobQueue), _Worker(worker), _JobRegistry(registry) {}

optional<reference_wrapper<Job>> Schedular::SelectJob()
{
    const int id = _JobQueue.GetJobId();
    if (id == -1) return nullopt;
    auto job = _JobRegistry.GetJob(id);
    return job;
}

void Schedular::DispatchJob()
{
    auto SelectedJob = SelectJob();
    Worker &SelectedWorker = SelectWorker();

    if (SelectedJob)
    {
        SelectedWorker.ReceiveJob(SelectedJob->get());
        SelectedWorker.TriggerWorker();
    }
}

Worker& Schedular::SelectWorker()
{
    return _Worker;
}

// temporary for debugging and testing
void Schedular::ScheduleJob()
{
    Schedular::DispatchJob();
}