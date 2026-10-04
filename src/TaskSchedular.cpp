#include "../header/TaskSchedular.h"
using namespace std;

TaskSchedular::TaskSchedular(JobQueue& jobQueue, JobRegistry& jobRegistry, Schedular& schedular) :
_JobQueue(jobQueue),
_JobRegistry(jobRegistry),
_Schedular(schedular)
{}

void TaskSchedular::SubmitJob(Job& job)
{
    const int id = job.GetId();
    _JobRegistry.AddJob(job);
    _JobQueue.AddJob(id);
}

void TaskSchedular::Execute()
{
    while (!_JobQueue.IsEmpty())
    {
        _Schedular.ScheduleJob();
    }
}
