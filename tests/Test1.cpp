#include <iostream>
#include "../header/Job.h"
#include "../header/JobQueue.h"
#include "../header/Work.h"
#include "../ConcreteWorks/PrintWorkJob.h"

using namespace std;

int main()
{
    // Testcase-1: Checks for behaviour when queue is empty
    JobQueue queue;
    if (queue.IsEmpty())
    {
        cout << "Test 1: Empty queue - PASS\n";
    }
    else
    {
        cout << "Test 1: Empty queue - FAIL\n";
    }

    // Testcase-2: Checks for behaviour of JobQueue.GetJob() when queue is empty
    optional<Job> emptyJob = queue.GetJob();

    if (!emptyJob.has_value())
    {
        cout << "Test 2: GetJob on empty queue - PASS\n";
    }
    else
    {
        cout << "Test 2: GetJob on empty queue - FAIL\n";
    }

    string name = "PrintWork";
    string description = "Print the work";
    Priority priority = Priority::Medium;
    ExecutionState state = ExecutionState::Created;
    unique_ptr<Work> work = make_unique<PrintWorkJob>();

    Job* job1 = new Job(
        name,
        description,
        state,
        priority,
        move(work)
    );

    // Adding first work to the queue
    queue.AddJob(*job1);

    // Deleting the job1 object to check whether the ownership got transferred or we got an error?
    delete job1;
    job1 = nullptr;

    // It will validate whether our ownership transfer is working or not??
    optional<Job> retrievedJob = queue.GetJob();

    if (retrievedJob.has_value())
    {
        cout << "Test 3: Retrieve Job after original destruction - PASS\n";
        cout << "Job ID: " << retrievedJob->GetId() << '\n';

        retrievedJob->GetWork().Execute();
    }
    else
    {
        cout << "Test 3: Retrieve Job after original destruction - FAIL\n";
    }

    Job* jobA = new Job(
        "Job A",
        "First job",
        ExecutionState::Created,
        Priority::Medium,
        make_unique<PrintWorkJob>()
    );

    Job* jobB = new Job(
        "Job B",
        "Second job",
        ExecutionState::Created,
        Priority::Medium,
        make_unique<PrintWorkJob>()
    );

    Job* jobC = new Job(
        "Job C",
        "Third job",
        ExecutionState::Created,
        Priority::Medium,
        make_unique<PrintWorkJob>()
    );

    queue.AddJob(*jobA);
    queue.AddJob(*jobB);
    queue.AddJob(*jobC);

    delete jobA;
    delete jobB;
    delete jobC;

    jobA = nullptr;
    jobB = nullptr;
    jobC = nullptr;

    // Validating the order of retrieval and insertion in the JobQueue
    optional<Job> firstJob = queue.GetJob();
    optional<Job> secondJob = queue.GetJob();
    optional<Job> thirdJob = queue.GetJob();

    if (firstJob.has_value() &&
        secondJob.has_value() &&
        thirdJob.has_value() &&
        firstJob->GetName() == "Job A" &&
        secondJob->GetName() == "Job B" &&
        thirdJob->GetName() == "Job C")
    {
        cout << "Test 4: FIFO order - PASS\n";
    }
    else
    {
        cout << "Test 4: FIFO order - FAIL\n";
    }

    if (queue.IsEmpty())
    {
        cout << "Test 5: Queue empty after retrieving all jobs - PASS\n";
    }
    else
    {
        cout << "Test 5: Queue empty after retrieving all jobs - FAIL\n";
    }

    return 0;
}