#include <iostream>
#include <memory>
#include <chrono>
#include "../header/TaskSchedular.h"

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

void PrintJobState(Job& job, const string& message)
{
    cout << "  " << message
         << " | Job ID: " << job.GetId()
         << " | Name: " << job.GetName()
         << " | State: " << StateToString(job.GetState())
         << '\n';
}

int main()
{
    JobRegistry registry;
    JobQueue queue;
    Worker worker("Worker-1");

    Schedular schedular(queue, worker, registry);
    TaskSchedular taskSchedular(queue, registry, schedular);

    auto work1 = make_unique<PrimeWork>(200000);
    auto work2 = make_unique<PrimeWork>(250000);
    auto work3 = make_unique<PrimeWork>(300000);

    Job job1(
        "Prime Analysis 1",
        "Calculate prime numbers up to 200000",
        Priority::High,
        move(work1)
    );

    Job job2(
        "Prime Analysis 2",
        "Calculate prime numbers up to 250000",
        Priority::Medium,
        move(work2)
    );

    Job job3(
        "Prime Analysis 3",
        "Calculate prime numbers up to 300000",
        Priority::Low,
        move(work3)
    );

    const int job1Id = job1.GetId();
    const int job2Id = job2.GetId();
    const int job3Id = job3.GetId();

    cout << "========== JOB CREATION ==========\n";

    cout << "Created Jobs:\n";
    cout << "  " << job1Id << " - " << job1.GetName() << '\n';
    cout << "  " << job2Id << " - " << job2.GetName() << '\n';
    cout << "  " << job3Id << " - " << job3.GetName() << '\n';

    cout << "\nInitial States:\n";

    cout << "  Job " << job1Id << ": "
         << StateToString(job1.GetState()) << '\n';

    cout << "  Job " << job2Id << ": "
         << StateToString(job2.GetState()) << '\n';

    cout << "  Job " << job3Id << ": "
         << StateToString(job3.GetState()) << '\n';

    cout << "\n========== SUBMITTING JOBS ==========\n";

    taskSchedular.SubmitJob(job1);
    taskSchedular.SubmitJob(job2);
    taskSchedular.SubmitJob(job3);

    cout << "All three jobs submitted.\n";

    cout << "\n========== REGISTRY VERIFICATION ==========\n";

    auto registeredJob1 = registry.GetJob(job1Id);
    auto registeredJob2 = registry.GetJob(job2Id);
    auto registeredJob3 = registry.GetJob(job3Id);

    if (registeredJob1 && registeredJob2 && registeredJob3)
        cout << "All three jobs exist in Registry.\n";
    else
        cout << "Registry verification FAILED.\n";

    if (registeredJob1)
        PrintJobState(registeredJob1->get(), "Registry");

    if (registeredJob2)
        PrintJobState(registeredJob2->get(), "Registry");

    if (registeredJob3)
        PrintJobState(registeredJob3->get(), "Registry");

    cout << "\n========== QUEUE VERIFICATION ==========\n";

    if (!queue.IsEmpty())
        cout << "Queue contains pending jobs.\n";
    else
        cout << "Queue verification FAILED.\n";

    cout << "\n========== EXECUTION ==========\n";

    cout << "Worker: " << worker.GetName() << '\n';
    cout << "Executing all queued jobs...\n\n";

    taskSchedular.Execute();

    cout << "\n========== EXECUTION COMPLETE ==========\n";

    cout << "\nQueue Status:\n";

    if (queue.IsEmpty())
        cout << "  Queue is empty. All jobs were processed.\n";
    else
        cout << "  Queue is NOT empty.\n";

    cout << "\nWorker Status:\n";

    if (!worker.HasJob())
        cout << "  " << worker.GetName() << " has no current Job.\n";
    else
        cout << "  " << worker.GetName() << " still has a Job.\n";

    cout << "\nFinal Registry Verification:\n";

    auto finalJob1 = registry.GetJob(job1Id);
    auto finalJob2 = registry.GetJob(job2Id);
    auto finalJob3 = registry.GetJob(job3Id);

    if (finalJob1 && finalJob2 && finalJob3)
        cout << "  All three Jobs still exist in Registry.\n";
    else
        cout << "  Registry persistence FAILED.\n";

    cout << "\nFinal Execution States:\n";

    if (finalJob1)
        PrintJobState(finalJob1->get(), "Final");

    if (finalJob2)
        PrintJobState(finalJob2->get(), "Final");

    if (finalJob3)
        PrintJobState(finalJob3->get(), "Final");

    cout << "\n========== MISSING JOB TEST ==========\n";

    if (!registry.GetJob(999999))
        cout << "Non-existing Job correctly not found.\n";
    else
        cout << "Missing Job test FAILED.\n";

    cout << "\n========== TEST COMPLETE ==========\n";

    return 0;
}