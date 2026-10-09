#ifndef TASKSCHEDULAR_JOBREGISTRY_H
#define TASKSCHEDULAR_JOBREGISTRY_H
#include <unordered_map>
#include <optional>
#include "Job.h"

class JobRegistry
{
private:
    std::unordered_map<int, Job> _Jobs;

public:
    void AddJob(Job job);
    std::optional<std::reference_wrapper<Job>> GetJob(const int id);
    void RemoveJob(const int id);
};


#endif //TASKSCHEDULAR_JOBREGISTRY_H
