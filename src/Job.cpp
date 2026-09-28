#include "../header/Job.h"
#include <string>
using namespace std;

Job::Job(int id, std::string name, std::string description, ExecutionState state, Priority priority, unique_ptr<Work> work) :
Id(id),
_Name(name),
_Description(description),
_State(state),
_Priority(priority),
_Work(move(work))
{}

const int Job::GetId() const {return Id;}
const string Job::GetName() const {return _Name;}
const string Job::GetDescription() const {return _Description;}
const ExecutionState Job::GetState() const {return _State;}
const Priority Job::GetPriority() const {return _Priority;}
const Work& Job::GetWork() const {return *_Work;}

void Job::SetPriority(Priority priority) {_Priority = priority;}