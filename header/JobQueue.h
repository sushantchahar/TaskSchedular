#ifndef TASKSCHEDULAR_JOBQUEUE_H
#define TASKSCHEDULAR_JOBQUEUE_H
#include <queue>

class JobQueue
{
private:
    std::queue<int> _JobQueue;

public:
    void AddJob(const int id);
    int GetJobId();
    bool IsEmpty() const;
};


#endif //TASKSCHEDULAR_JOBQUEUE_H
