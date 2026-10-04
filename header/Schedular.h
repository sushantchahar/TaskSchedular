#ifndef TASKSCHEDULAR_SCHEDULAR_H
#define TASKSCHEDULAR_SCHEDULAR_H
#include "JobRegistry.h"
#include "../header/Job.h"
#include "../header/JobQueue.h"
#include "../header/Worker.h"

class Schedular
{
private:
    JobQueue& _JobQueue;
    Worker& _Worker;
    JobRegistry& _JobRegistry;
public:
    Schedular(JobQueue& jobQueue, Worker& worker, JobRegistry& registry);
    std::optional<std::reference_wrapper<Job>> SelectJob();
    Worker& SelectWorker();
    void DispatchJob();
    // temporary for debugging and testing
    void ScheduleJob();
};

#endif //TASKSCHEDULAR_SCHEDULAR_H
