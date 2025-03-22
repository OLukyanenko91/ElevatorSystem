#pragma once

#include "Elevator/Elevator.hpp"
#include "src/Service.hpp"
#include "src/Common.hpp"


class Manager
{
public:
    Manager();

private:
    void GenerateFloors();

private:
    std::unique_ptr<Elevator> mElevator;
    std::unique_ptr<Service>  mService;

    FloorsMap mFloors;
};
