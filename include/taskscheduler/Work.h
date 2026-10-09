#ifndef TASKSCHEDULAR_WORK_H
#define TASKSCHEDULAR_WORK_H

class Work
{
// Operations
public:
    virtual bool Execute() = 0;
    virtual ~Work() = default;
};


#endif //TASKSCHEDULAR_WORK_H
