#ifndef TASKSCHEDULAR_WORKERPOOL_H
#define TASKSCHEDULAR_WORKERPOOL_H
#include <vector>
#include <optional>
#include "Worker.h"

class WorkerPool
{
private:
    std::vector<Worker> _Workers;

    // helpers
    void CreateWorkers(int workercount);
public:
    WorkerPool() = delete;
    WorkerPool(const WorkerPool&) = delete;
    WorkerPool(WorkerPool&&) = delete;

    WorkerPool& operator=(const WorkerPool&) = delete;
    WorkerPool& operator=(WorkerPool&&) = delete;

    WorkerPool(int workercount);

    std::optional<std::reference_wrapper<Worker>> AcquireWorker();
};

#endif //TASKSCHEDULAR_WORKERPOOL_H
