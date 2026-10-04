#include "../header/JobQueue.h"
using namespace std;

void JobQueue::AddJob(const int id)
{
    _JobQueue.push(id);
}

int JobQueue::GetJobId()
{
    if (IsEmpty()) return -1;
    const int id = _JobQueue.front();
    _JobQueue.pop();
    return id;
}

bool JobQueue::IsEmpty() const
{
    return _JobQueue.empty();
}