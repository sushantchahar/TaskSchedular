#include "../header/Worker.h"
#include <iostream>
using namespace std;

void Worker::ReceiveJob(Job job)
{
    _CurrentJob = move(job);
    _CurrentJob->SetState(ExecutionState::Running);
}

bool Worker::HasJob()
{
    return _CurrentJob.has_value();
}

void Worker::ExecuteJob()
{
    if (Worker::HasJob() == false)
    {
        // Debugging print statement
        cout << "Worker has not valid job. So cannot execute the work" << "\n";
        return;
    }
    bool IsWorkExecuted = _CurrentJob->GetWork().Execute();
    if (IsWorkExecuted)
    {
        _CurrentJob->SetState(ExecutionState::Completed);
    }

    else
    {
        _CurrentJob->SetState(ExecutionState::Failed);
    }

    // Once job completes
    _CurrentJob.reset();
}

void Worker::TriggerWorker()
{
    Worker::ExecuteJob();
}