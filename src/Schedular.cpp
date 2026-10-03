#include "../header/Schedular.h"
using namespace std;

Schedular::Schedular(JobQueue& jobQueue, Worker& worker) : _JobQueue(jobQueue), _Worker(worker) {}

optional<Job> Schedular::SelectJob()
{
    return move(_JobQueue.GetJob());
}

void Schedular::DispatchJob()
{
    auto SelectedJob = SelectJob();
    Worker &SelectedWorker = SelectWorker();

    if (SelectedJob)
    {
        SelectedWorker.ReceiveJob(move(SelectedJob.value()));
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