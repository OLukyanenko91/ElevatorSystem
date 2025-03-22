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
    lmInfo() << "Close door";
    AddAction(ElevatorData::Action {ElevatorData::ActionType::CloseDoor});
}

void Elevator::OpenDoor()
{
    lmInfo() << "Open door";
    AddAction(ElevatorData::Action {ElevatorData::ActionType::OpenDoor});
}

void Elevator::Stop()
{
    lmInfo() << "Stop";
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
    lmInfo() << "Run";

    while(mProcessingRunning) {
        std::unique_lock<std::mutex> locker(mActionsQueueMutex);
        mProcessingCVariable.wait(locker, [this] { return !mActionsQueue.empty(); });
        locker.unlock();

        while (!mActionsQueue.empty() && mProcessingRunning) {
            locker.lock();
            auto action = mActionsQueue.front();
            mActionsQueue.pop();
            locker.unlock();

            lmInfo() << "Process action: " << action.type;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}
