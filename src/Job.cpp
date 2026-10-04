#include "../header/Job.h"
#include <string>
using namespace std;

int Job::UniqueId = 0;

Job::Job(std::string name, std::string description, Priority priority, unique_ptr<Work> work) :
_Name(name),
_Description(description),
_State(ExecutionState::Created),
_Priority(priority),
_Work(move(work))
{
    this->Id = UniqueId + 1;
    Job::UniqueId++;
}

const int Job::GetId() const {return Id;}
const string Job::GetName() const {return _Name;}
const string Job::GetDescription() const {return _Description;}
const ExecutionState Job::GetState() const {return _State;}
const Priority Job::GetPriority() const {return _Priority;}
Work& Job::GetWork() const {return *_Work;}

void Job::SetPriority(Priority priority) {_Priority = priority;}
void Job::SetState(ExecutionState state) {_State = state;}