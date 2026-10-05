#include "../header/Worker.h"
#include <iostream>
using namespace std;

Worker::Worker(const std::string& name) : _Name(name)
{}

void Worker::ReceiveJob(Job& job)
{
    _CurrentJob = ref(job);
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

    auto& job = _CurrentJob->get();
    job.SetState(ExecutionState::Running);

    try
    {
        bool isExecuted = job.GetWork().Execute();

        if (isExecuted)
        {
            job.SetState(ExecutionState::Completed);
        }

        else
        {
            job.SetState(ExecutionState::Failed);
        }
    }
    catch (exception& e)
    {
        job.SetState(ExecutionState::Failed);
    }

    // Once job completes
    _CurrentJob.reset();
}

void Worker::TriggerWorker()
{
    Worker::ExecuteJob();
}

const string Worker::GetName()
{
    return _Name;
}