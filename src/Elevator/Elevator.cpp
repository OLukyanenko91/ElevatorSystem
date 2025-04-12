#include <Logger.hpp>
#include "Elevator.hpp"

#define LOG_MODULE_NAME "Elevator"


////////////// ELEVATOR DATA //////////////

std::ostream& ElevatorData::operator<<(std::ostream& cout,
                                       ActionType type)
{
    if(type == ActionType::CalledFromFloor) {
        cout << "CalledFromFloor";
    }
    else if(type == ActionType::GoToFloor) {
        cout << "GoToFloor";
    }
    else if(type == ActionType::OpenDoor) {
        cout << "OpenDoor";
    }
    else if(type == ActionType::CloseDoor) {
        cout << "CloseDoor";
    }
    else if(type == ActionType::GoHome) {
        cout << "GoHome";
    }
    else if(type == ActionType::Stop) {
        cout << "Stop";
    }
    else {
        cout << "Unknown";
    }

    return cout;
}

////////////// ELEVATOR //////////////

Elevator::Elevator()
{
    mProcessingThread = std::thread(&Elevator::Run, this);
}

Elevator::~Elevator()
{
    mProcessingRunning = false;
    if (mProcessingThread.joinable()) {
        mProcessingThread.join();
    }
}

void Elevator::CalledFromFloor(const uint8_t floor)
{
    lmInfo() << "Called from " << int(floor) << " floor";
    AddAction(ElevatorData::Action {ElevatorData::ActionType::CalledFromFloor,
                                    floor});
}

void Elevator::GoToFloor(const uint8_t floor)
{
    lmInfo() << "Go to " << int(floor) << " floor";
    AddAction(ElevatorData::Action {ElevatorData::ActionType::GoToFloor,
                                    floor});
}

void Elevator::CloseDoor()
{
    lmEnter();
    AddAction(ElevatorData::Action {ElevatorData::ActionType::CloseDoor});
}

void Elevator::OpenDoor()
{
    lmEnter();
    AddAction(ElevatorData::Action {ElevatorData::ActionType::OpenDoor});
}

void Elevator::Stop()
{
    lmEnter();
    AddAction(ElevatorData::Action {ElevatorData::ActionType::Stop});
}

void Elevator::AddAction(const ElevatorData::Action& action)
{
    lmInfo() << "Add action, type " << action.type;

    {
        const std::lock_guard<std::mutex> lock(mActionsQueueMutex);
        mActionsQueue.push(action);
    }

    mProcessingCVariable.notify_one();
}

void Elevator::Run()
{
    lmEnter();

    while(mProcessingRunning) {
        // Wait new actions
        std::unique_lock<std::mutex> locker(mActionsQueueMutex);
        mProcessingCVariable.wait(locker, [this] { return !mActionsQueue.empty(); });
        locker.unlock();

        while (!mActionsQueue.empty() && mProcessingRunning) {
            locker.lock();
            auto action = mActionsQueue.front();
            mActionsQueue.pop();
            locker.unlock();

            lmInfo() << "Process action " << action.type << ", value " << int(action.floor);
            if (action.type == ElevatorData::ActionType::CalledFromFloor) {
                ProcessCalledFromFloorAction(action.floor);
            }
            else if (action.type == ElevatorData::ActionType::GoToFloor) {
                ProcessGoToFloorAction(action.floor);
            }
        }
    }
}

void Elevator::SetCurrentFloor(const uint8_t floor)
{
    lmInfo() << "Set current floor " << int(floor);
    mCurrentFloor = floor;
    lmInfo() << "Current floor is " << int(mCurrentFloor);
}

void Elevator::ProcessCalledFromFloorAction(const uint8_t floor)
{
    lmInfo() << "Process called from floor action " << int(floor);

    while (mCurrentFloor != floor) {
        SetCurrentFloor(floor > mCurrentFloor ? mCurrentFloor + 1 : mCurrentFloor - 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    ProcessOpenDoorAction();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    ProcessCloseDoorAction();
}

void Elevator::ProcessGoToFloorAction(const uint8_t floor)
{
    lmInfo() << "Process go to floor action " << int(floor);

    while (mCurrentFloor != floor) {
        SetCurrentFloor(floor > mCurrentFloor ? mCurrentFloor + 1 : mCurrentFloor - 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    ProcessOpenDoorAction();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    ProcessCloseDoorAction();
}

void Elevator::ProcessOpenDoorAction()
{
    lmEnter();

    // open internal door
    // manager -> open external door
}

void Elevator::ProcessCloseDoorAction()
{
    lmEnter();

    // close internal door
    // manager -> close external door
}
