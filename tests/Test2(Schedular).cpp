#include <iostream>
#include "../header/Job.h"
#include "../header/JobQueue.h"
#include "../header/Work.h"
#include "../ConcreteWorks/PrintWorkJob.h"
#include "../header/Schedular.h"

using namespace std;

int main()
{
    JobQueue jobQueue;
    Worker worker;
    Schedular scheduler(jobQueue, worker);

    std::unique_ptr<Work> work = std::make_unique<PrintWorkJob>();

    Job job(
        "Ownership Test",
        "Test JobQueue to Scheduler to Worker ownership transfer",
        ExecutionState::Created,
        Priority::Medium,
        std::move(work)
    );

    jobQueue.AddJob(job);

    if (jobQueue.IsEmpty())
    {
        std::cout << "Test failed: JobQueue should contain the Job\n";
        return 1;
    }

    scheduler.DispatchJob();

    if (!jobQueue.IsEmpty())
    {
        std::cout << "Test failed: Job was not removed from JobQueue\n";
        return 1;
    }

    if (!worker.HasJob())
    {
        std::cout << "Test failed: Worker did not receive the Job\n";
        return 1;
    }

    std::cout << "Job ownership transferred to Worker successfully\n";

    worker.ExecuteJob();

    std::cout << "All Scheduler tests passed\n";

    return 0;
}