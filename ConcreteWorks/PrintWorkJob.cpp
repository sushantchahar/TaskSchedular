#include "PrintWorkJob.h"
#include <iostream>

bool PrintWorkJob::Execute()
{
    std::cout << "PrintWorkJob Execute() executed" << "\n";
    return true;
}