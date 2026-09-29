#ifndef TASKSCHEDULAR_PRINTWORKJOB_H
#define TASKSCHEDULAR_PRINTWORKJOB_H
#include "../header/Work.h"


class PrintWorkJob : public Work
{
public:
    void Execute() override;
    // ~PrintWorkJob() override;
};


#endif //TASKSCHEDULAR_PRINTWORKJOB_H
