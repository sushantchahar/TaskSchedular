#ifndef TASKSCHEDULAR_SCHEDULAR_H
#define TASKSCHEDULAR_SCHEDULAR_H
#include "../header/Job.h"
#include "../header/JobQueue.h"
#include "../header/Worker.h"

class Schedular
{
private:
    JobQueue& _JobQueue;
    Worker& _Worker;
public:
    Schedular(JobQueue& jobQueue, Worker& worker);
    std::optional<Job> SelectJob();
    Worker& SelectWorker();
    void DispatchJob();
};

#endif //TASKSCHEDULAR_SCHEDULAR_H
