#ifndef TASKSCHEDULAR_TASKSCHEDULAR_H
#define TASKSCHEDULAR_TASKSCHEDULAR_H
#include "JobQueue.h"
#include "JobRegistry.h"
#include "Schedular.h"

class TaskSchedular
{
private:
    JobQueue& _JobQueue;
    JobRegistry& _JobRegistry;
    Schedular& _Schedular;

public:
    TaskSchedular(JobQueue& _JobQueue, JobRegistry& _JobRegistry, Schedular& _Schedular);
    void SubmitJob(Job job);
    void Execute();
};

#endif //TASKSCHEDULAR_TASKSCHEDULAR_H
