#ifndef TASKSCHEDULAR_PRINT1TONNUMBERS_H
#define TASKSCHEDULAR_PRINT1TONNUMBERS_H
#include "../header/Work.h"

class Print1toNnumbers : public Work
{
public:
    bool Execute() override;
    ~Print1toNnumbers() = default;

};


#endif //TASKSCHEDULAR_PRINT1TONNUMBERS_H
