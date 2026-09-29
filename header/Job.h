#ifndef TASKSCHEDULAR_JOB_H
#define TASKSCHEDULAR_JOB_H
#include <string>
#include "Priority.h"
#include "ExecutionState.h"
#include "Work.h"
#include <memory>

class Job
{
// Attributes
private:
    static int UniqueId;
    int Id;
    std::string _Name;
    std::string _Description;
    Priority _Priority;
    ExecutionState _State;
    std::unique_ptr<Work> _Work;

// Operations
public:
    // Constructor
    Job(std::string name, std::string description, ExecutionState state, Priority priority, std::unique_ptr<Work> work);

    // Getters
    const std::string GetName() const;
    const std::string GetDescription() const;
    const int GetId() const;
    const Priority GetPriority() const;
    const ExecutionState GetState() const;
    Work& GetWork() const;

    // Setters
    void SetPriority(Priority priority);
};

#endif //TASKSCHEDULAR_JOB_H
