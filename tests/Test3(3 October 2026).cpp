#include <iostream>
#include "../ConcreteWorks/Print1toNnumbers.h"
#include "../header/Job.h"
#include "../header/JobQueue.h"
#include "../header/Work.h"
#include "../header/Schedular.h"
#include "../ConcreteWorks/Print1toNnumbers.h"

using namespace std;

int main()
{
    Worker worker;
    JobQueue jobQueue;
    Schedular schedular(jobQueue, worker);
    unique_ptr<Work> work = make_unique<Print1toNnumbers>();

    Job job1(
        "PrintWork",
        "Print work job",
        Priority::Low,
        move(work)
    );

    jobQueue.AddJob(job1);
    schedular.ScheduleJob();

    return 0;
}