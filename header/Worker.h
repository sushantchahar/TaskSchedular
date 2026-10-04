#ifndef TASKSCHEDULAR_WORKER_H
#define TASKSCHEDULAR_WORKER_H
#include "Job.h"
#include <optional>

class Worker
{
private:
    std::string _Name;
    std::optional<std::reference_wrapper<Job>> _CurrentJob;

public:
    explicit Worker(const std::string& name);
    void ExecuteJob();
    void ReceiveJob(Job& job);
    bool HasJob();
    void TriggerWorker();
    const std::string GetName();
};


#endif //TASKSCHEDULAR_WORKER_H
