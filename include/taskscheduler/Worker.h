#ifndef TASKSCHEDULAR_WORKER_H
#define TASKSCHEDULAR_WORKER_H
#include "Job.h"
#include <optional>
#include "WorkerState.h"

class Worker
{
private:
    std::string _Name;
    std::optional<std::reference_wrapper<Job>> _CurrentJob;
    WorkerState _WorkerState = WorkerState::Available;

public:
    explicit Worker(const std::string& name);
    void ExecuteJob();
    void ReceiveJob(Job& job);
    bool HasJob();
    void TriggerWorker();
    const std::string GetName();
    void MarkBusy();
    void MarkAvailable();
    WorkerState GetState() const;
};


#endif //TASKSCHEDULAR_WORKER_H
