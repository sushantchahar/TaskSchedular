#ifndef TASKSCHEDULAR_WORKER_H
#define TASKSCHEDULAR_WORKER_H
#include "Job.h"
#include <optional>

class Worker
{
private:
    std::optional<Job> _CurrentJob;

public:
    Worker() = default;
    void ExecuteJob();
    void ReceiveJob(Job job);
    bool HasJob();
};


#endif //TASKSCHEDULAR_WORKER_H
