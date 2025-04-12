#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <atomic>
#include <condition_variable>


////////////// ELEVATOR DATA //////////////

namespace ElevatorData
{
    enum class ActionType
    {
        Unknown = 0,
        CalledFromFloor,
        GoToFloor,
        OpenDoor,
        CloseDoor,
        GoHome,
        Stop
    };

    struct Action
    {
        ActionType type  {ActionType::Unknown};
        uint8_t    floor {0};
    };

    std::ostream& operator<<(std::ostream& cout, ActionType type);
}

////////////// ELEVATOR //////////////

class Elevator
{
    using ActionsQueue = std::queue<ElevatorData::Action>;
    using aBool        = std::atomic<bool>;
    using cVariable    = std::condition_variable;

    friend class Service;

public:
    Elevator();
    ~Elevator();

public:
    void CalledFromFloor(const uint8_t floor);
    void GoToFloor(const uint8_t floor);
    void CloseDoor();
    void OpenDoor();
    void Stop();

private:
    void AddAction(const ElevatorData::Action& action);
    void Run();
    void SetCurrentFloor(const uint8_t floor);

    void ProcessCalledFromFloorAction(const uint8_t floor);
    void ProcessGoToFloorAction(const uint8_t floor);
    void ProcessOpenDoorAction();
    void ProcessCloseDoorAction();

private:
    ActionsQueue mActionsQueue;
    std::mutex   mActionsQueueMutex;

    std::thread mProcessingThread;
    aBool       mProcessingRunning {true};
    cVariable   mProcessingCVariable;

    uint8_t mCurrentFloor {0};
};
