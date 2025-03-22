#pragma once

#include "src/Elevator/Elevator.hpp"
#include "src/Common.hpp"


class Service
{
public:
    explicit Service(Elevator& elevator,
                     FloorsMap& floors);

private:
    void Run();

private:
    Elevator&  mElevator;
    FloorsMap& mFloors;

    std::thread mProcessingThread;
};
