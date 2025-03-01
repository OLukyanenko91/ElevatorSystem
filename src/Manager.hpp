#pragma once

#include <cstdint>
#include <map>
#include "Floor.hpp"
#include "Elevator.hpp"


class Manager
{
    using FloorsMap = std::map<uint8_t, Floor>;

    friend class Service;

public:
    Manager();

public:
    void StartSystem();

private:
    FloorsMap mFloors;
    Elevator  mElevator;
};
