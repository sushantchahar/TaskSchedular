#ifndef TASKSCHEDULAR_WORKER_H
#define TASKSCHEDULAR_WORKER_H
#include "Job.h"
#include <optional>

class Worker
{
private:
    std::optional<std::reference_wrapper<Job>> _CurrentJob;

public:
    Worker() = default;
    void ExecuteJob();
    void ReceiveJob(Job& job);
    bool HasJob();
    void TriggerWorker();
};


#endif //TASKSCHEDULAR_WORKER_H
