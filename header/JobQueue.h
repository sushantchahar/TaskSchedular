#ifndef TASKSCHEDULAR_JOBQUEUE_H
#define TASKSCHEDULAR_JOBQUEUE_H
#include <queue>
#include "Job.h"
#include <optional>

class JobQueue
{
private:
    std::queue<Job> _JobQueue;

public:
    void AddJob(Job& job);
    std::optional<Job> GetJob();
    bool IsEmpty() const;
};


#endif //TASKSCHEDULAR_JOBQUEUE_H
