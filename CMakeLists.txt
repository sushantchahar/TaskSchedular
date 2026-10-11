cmake_minimum_required(VERSION 4.2)
project(TaskSchedular)

set(CMAKE_CXX_STANDARD 26)

add_executable(TaskSchedular main.cpp
        src/Job.cpp
        src/JobQueue.cpp
        src/JobRegistry.cpp
        src/Schedular.cpp
        src/TaskSchedular.cpp
        src/WorkerPool.cpp
        src/Worker.cpp
        src/Work.cpp
)

target_include_directories(TaskSchedular PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include )
