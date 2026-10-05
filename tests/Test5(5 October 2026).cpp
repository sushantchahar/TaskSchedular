/*
 this test is specifically designed for work completion, failed or runtime_error. The states are assigned
 correctly based on work execution
 if work's execute() return false or any runtime error inside it results the job state to be failed
 */

#include <iostream>
#include <memory>
#include <chrono>
#include "../header/TaskSchedular.h"
#include "../header/ExecutionState.h"

using namespace std;

string StateToString(ExecutionState state)
{
    switch (state)
    {
        case Created: return "Created";
        case Pending: return "Pending";
        case Running: return "Running";
        case Completed: return "Completed";
        case Failed: return "Failed";
    }

    return "Unknown";
}

class PrimeWork : public Work
{
private:
    int _Limit;
    long long _PrimeCount = 0;

public:
    explicit PrimeWork(int limit) : _Limit(limit) {}

    bool Execute() override
    {
        // throw runtime_error("Not implemented");
        const auto start = chrono::high_resolution_clock::now();

        for (int number = 2; number <= _Limit; ++number)
        {
            bool isPrime = true;

            for (int divisor = 2; divisor * divisor <= number; ++divisor)
            {
                if (number % divisor == 0)
                {
                    isPrime = false;
                    break;
                }
            }

            if (isPrime)
                ++_PrimeCount;
        }

        const auto end = chrono::high_resolution_clock::now();

        const auto duration =
            chrono::duration_cast<chrono::milliseconds>(end - start);

        cout << "      Prime numbers found: " << _PrimeCount << '\n';
        cout << "      Execution time: " << duration.count() << " ms\n";

        return true;
    }
};

class FailedWork : public Work
{
public:
    bool Execute() override
    {
        return false;
    }
};

class ExceptionWork : public Work
{
public:
    bool Execute() override
    {
        throw runtime_error("Work execution exception");
    }
};

string GetStateName(ExecutionState state)
{
    switch (state)
    {
        case ExecutionState::Created:
            return "Created";
        case ExecutionState::Pending:
            return "Pending";
        case ExecutionState::Running:
            return "Running";
        case ExecutionState::Completed:
            return "Completed";
        case ExecutionState::Failed:
            return "Failed";
    }

    return "Unknown";
}

int main()
{
    JobRegistry jobRegistry;
    JobQueue jobQueue;

    Worker worker("Worker-1");

    Schedular schedular(
        jobQueue,
        worker,
        jobRegistry
    );

    TaskSchedular taskSchedular(
        jobQueue,
        jobRegistry,
        schedular
    );

    Job successJob(
        "Successful Job",
        "Job that completes successfully",
        Priority::Medium,
        make_unique<PrimeWork>(200000)
    );

    Job failedJob(
        "Failed Job",
        "Job that returns false",
        Priority::Medium,
        make_unique<FailedWork>()
    );

    Job exceptionJob(
        "Exception Job",
        "Job that throws an exception",
        Priority::Medium,
        make_unique<ExceptionWork>()
    );

    const int successJobId = successJob.GetId();
    const int failedJobId = failedJob.GetId();
    const int exceptionJobId = exceptionJob.GetId();

    cout << "========== INITIAL STATES ==========\n";

    cout << "Job " << successJobId << ": "
         << GetStateName(successJob.GetState()) << '\n';

    cout << "Job " << failedJobId << ": "
         << GetStateName(failedJob.GetState()) << '\n';

    cout << "Job " << exceptionJobId << ": "
         << GetStateName(exceptionJob.GetState()) << '\n';

    cout << "\n========== SUBMITTING JOBS ==========\n";

    taskSchedular.SubmitJob(move(successJob));
    taskSchedular.SubmitJob(move(failedJob));
    taskSchedular.SubmitJob(move(exceptionJob));

    cout << "All three jobs submitted.\n";

    cout << "\n========== PENDING STATES ==========\n";

    auto pendingJob1 = jobRegistry.GetJob(successJobId);
    auto pendingJob2 = jobRegistry.GetJob(failedJobId);
    auto pendingJob3 = jobRegistry.GetJob(exceptionJobId);

    cout << "Job " << successJobId << ": "
         << GetStateName(pendingJob1->get().GetState()) << '\n';

    cout << "Job " << failedJobId << ": "
         << GetStateName(pendingJob2->get().GetState()) << '\n';

    cout << "Job " << exceptionJobId << ": "
         << GetStateName(pendingJob3->get().GetState()) << '\n';

    cout << "\n========== EXECUTION ==========\n";

    taskSchedular.Execute();

    cout << "\n========== FINAL STATES ==========\n";

    auto finalJob1 = jobRegistry.GetJob(successJobId);
    auto finalJob2 = jobRegistry.GetJob(failedJobId);
    auto finalJob3 = jobRegistry.GetJob(exceptionJobId);

    cout << "Job " << successJobId << ": "
         << GetStateName(finalJob1->get().GetState()) << '\n';

    cout << "Job " << failedJobId << ": "
         << GetStateName(finalJob2->get().GetState()) << '\n';

    cout << "Job " << exceptionJobId << ": "
         << GetStateName(finalJob3->get().GetState()) << '\n';

    cout << "\n========== TEST VERIFICATION ==========\n";

    bool successTest =
        finalJob1->get().GetState() == ExecutionState::Completed;

    bool failedTest =
        finalJob2->get().GetState() == ExecutionState::Failed;

    bool exceptionTest =
        finalJob3->get().GetState() == ExecutionState::Failed;

    cout << "Successful Work: "
         << (successTest ? "PASS" : "FAIL") << '\n';

    cout << "Failed Work: "
         << (failedTest ? "PASS" : "FAIL") << '\n';

    cout << "Exception Work: "
         << (exceptionTest ? "PASS" : "FAIL") << '\n';

    cout << "\n========== TEST RESULT ==========\n";

    if (successTest && failedTest && exceptionTest)
    {
        cout << "All execution lifecycle tests passed.\n";
    }
    else
    {
        cout << "One or more execution lifecycle tests failed.\n";
    }

    return 0;
}