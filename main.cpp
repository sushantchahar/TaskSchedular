#include <iostream>
#include <cassert>

#include "header/WorkerPool.h"
#include "header/Worker.h"
#include "header/Job.h"
#include "header/JobRegistry.h"
#include "header/JobQueue.h"
#include "header/Schedular.h"
#include "header/TaskSchedular.h"

using namespace std;

class SuccessfulWork : public Work
{
public:
    bool Execute() override
    {
        return true;
    }
};

class FailedWork : public Work
{
public:
    bool Execute() override
    {
        return false;
    }
};

int main()
{
    // Create a pool with three workers.
    WorkerPool workerPool(3);

    // Verify that all workers can be acquired.
    auto worker1 = workerPool.AcquireWorker();
    auto worker2 = workerPool.AcquireWorker();
    auto worker3 = workerPool.AcquireWorker();

    assert(worker1.has_value());
    assert(worker2.has_value());
    assert(worker3.has_value());

    // Each acquired worker should be marked as Busy.
    assert(worker1->get().GetState() == WorkerState::Busy);
    assert(worker2->get().GetState() == WorkerState::Busy);
    assert(worker3->get().GetState() == WorkerState::Busy);

    cout << "All workers acquired successfully.\n";

    // No worker should be available after all workers are acquired.
    auto noWorker = workerPool.AcquireWorker();

    assert(!noWorker.has_value());

    cout << "Worker pool correctly reports no available worker.\n";

    // Release the first worker by giving it a job and executing it.
    JobRegistry registry;
    JobQueue queue;
    Schedular schedular(queue, workerPool, registry);
    TaskSchedular taskSchedular(queue, registry, schedular);

    Job job(
        "Test Job",
        "Checks worker state after execution",
        Priority::Medium,
        make_unique<SuccessfulWork>()
    );

    taskSchedular.SubmitJob(move(job));

    // The scheduler acquires the available worker and executes the job.
    // Since all three workers are currently Busy, this should not execute.
    taskSchedular.Execute();

    // Manually make one worker available for the execution test.
    worker1->get().MarkAvailable();

    auto availableWorker = workerPool.AcquireWorker();

    assert(availableWorker.has_value());
    assert(availableWorker->get().GetState() == WorkerState::Busy);

    cout << "Released worker was successfully acquired again.\n";

    // Create another job directly for checking execution and state transition.
    Job executionJob(
        "Execution Test",
        "Checks Running to Completed transition",
        Priority::High,
        make_unique<SuccessfulWork>()
    );

    availableWorker->get().ReceiveJob(executionJob);

    // Worker should become Available after execution.
    availableWorker->get().TriggerWorker();

    assert(executionJob.GetState() == ExecutionState::Completed);
    assert(availableWorker->get().GetState() == WorkerState::Available);

    cout << "Worker returned to Available after successful execution.\n";

    // Check that a failed job also releases the worker.
    Job failedJob(
        "Failed Job",
        "Checks failed execution",
        Priority::Low,
        make_unique<FailedWork>()
    );

    auto failedWorker = workerPool.AcquireWorker();

    assert(failedWorker.has_value());
    assert(failedWorker->get().GetState() == WorkerState::Busy);

    failedWorker->get().ReceiveJob(failedJob);
    failedWorker->get().TriggerWorker();

    assert(failedJob.GetState() == ExecutionState::Failed);
    assert(failedWorker->get().GetState() == WorkerState::Available);

    cout << "Worker returned to Available after failed execution.\n";

    cout << "\nAll WorkerPool tests passed.\n";

    return 0;
}