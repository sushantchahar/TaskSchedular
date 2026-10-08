cmake_minimum_required(VERSION 4.2)
project(TaskSchedular)

set(CMAKE_CXX_STANDARD 26)

add_executable(TaskSchedular main.cpp
        src/Job.cpp
        header/Job.h
        header/Priority.h
        header/ExecutionState.h
        src/Work.cpp
        header/Work.h
        ConcreteWorks/PrintWorkJob.cpp
        ConcreteWorks/PrintWorkJob.h
        src/JobQueue.cpp
        header/JobQueue.h
        src/Schedular.cpp
        header/Schedular.h
        src/Worker.cpp
        header/Worker.h
        main.cpp
        ConcreteWorks/Print1toNnumbers.cpp
        ConcreteWorks/Print1toNnumbers.h
        src/JobRegistry.cpp
        header/JobRegistry.h
        src/TaskSchedular.cpp
        header/TaskSchedular.h
        src/WorkerPool.cpp
        header/WorkerPool.h
        header/WorkerState.h
)
