#ifndef TASKSCHEDULAR_SCHEDULAR_H
#define TASKSCHEDULAR_SCHEDULAR_H
#include "JobRegistry.h"
#include "WorkerPool.h"
#include "Job.h"
#include "JobQueue.h"
#include "Worker.h"

class Schedular
{
private:
    JobQueue& _JobQueue;
    WorkerPool& _WorkerPool;
    JobRegistry& _JobRegistry;
public:
    Schedular(JobQueue& jobQueue, WorkerPool& workerPool, JobRegistry& registry);
    std::optional<std::reference_wrapper<Job>> SelectJob();
    std::optional<std::reference_wrapper<Worker>> SelectWorker();
    void DispatchJob();
    // temporary for debugging and testing
    void ScheduleJob();
};

#endif //TASKSCHEDULAR_SCHEDULAR_H
