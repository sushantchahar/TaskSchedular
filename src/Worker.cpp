#include "../header/Worker.h"
#include <iostream>
using namespace std;

void Worker::ReceiveJob(Job job)
{
    _CurrentJob = move(job);
    cout << boolalpha << "Has worker job : " << HasJob() << "\n";
}

bool Worker::HasJob()
{
    if (_CurrentJob && _CurrentJob.has_value()) return true;
    return false;
}

void Worker::ExecuteJob()
{
    cout << "Worker executed the job" << "\n";
    _CurrentJob->GetWork().Execute();
}