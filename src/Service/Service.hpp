#pragma once

#include "src/Elevator/Elevator.hpp"
#include "src/Common.hpp"
#include "src/Service/MAVLinkHandler.hpp"


class Service
{
    friend MAVLinkHandler;

public:
    explicit Service(Elevator& elevator,
                     FloorsMap& floors);

private:
    void Run();

    void GoToFloorCmdReceived(const uint8_t floor);
    void CallFromFloorCmdReceived(const uint8_t floor);

private:
    Elevator&      mElevator;
    FloorsMap&     mFloors;
    MAVLinkHandler mMAVHandler;

    std::thread mProcessingThread;
};
