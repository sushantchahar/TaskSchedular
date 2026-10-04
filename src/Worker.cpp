#include "../header/Worker.h"
#include <iostream>
using namespace std;

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
    job.GetWork().Execute();

    // Once job completes
    _CurrentJob.reset();
}

void Worker::TriggerWorker()
{
    Worker::ExecuteJob();
}