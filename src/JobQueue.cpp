#include "../header/JobQueue.h"
using namespace std;

void JobQueue::AddJob(Job& job)
{
    // Job is added to queue and now it can be processed further
    job.SetState(ExecutionState::Pending);
    _JobQueue.push(move(job));
}

optional<Job> JobQueue::GetJob()
{
    if (JobQueue::IsEmpty())
    {
        return nullopt;
    }

    Job job = move(_JobQueue.front());
    _JobQueue.pop();
    return move(job);
}

bool JobQueue::IsEmpty() const
{
    return _JobQueue.empty();
}