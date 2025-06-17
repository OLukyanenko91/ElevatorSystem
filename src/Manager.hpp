#pragma once

#include "Elevator/Elevator.hpp"
#include "src/Service/Service.hpp"
#include "src/Common.hpp"


class Manager
{
public:
    Manager();

private:
    void GenerateFloors();

private:
    Elevator  mElevator;
    FloorsMap mFloors;

    std::unique_ptr<Service>  mService;
};
