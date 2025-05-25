#include <Logger.hpp>
#include "Floor.hpp"
#include "Elevator/Elevator.hpp"

#define LOG_MODULE_NAME "Floor"


Floor::Floor(uint8_t number,
             Elevator& elevator)
    : mNumber(number)
    , mElevator(elevator)
{}

void Floor::CallButtonPushed()
{
    lmInfo() << mNumber << "Call button pushed";
    mElevator.CalledFromFloor(mNumber);
}
