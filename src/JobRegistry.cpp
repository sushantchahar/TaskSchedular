#include "../header/JobRegistry.h"
using namespace std;

void JobRegistry::AddJob(Job& job)
{
    _Jobs.emplace(job.GetId(), move(job));
}

void JobRegistry::RemoveJob(const int id)
{
    _Jobs.erase(id);
}

std::optional<std::reference_wrapper<Job>> JobRegistry::GetJob(const int id)
{
    auto job = _Jobs.find(id);

    if (job == _Jobs.end())
    {
        return nullopt;
    }

    return job->second;
}
