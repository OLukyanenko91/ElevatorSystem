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

////////////// ELEVATOR SM //////////////

namespace ElevatorSM
{
    class Elevator;

    class State
    {
    public:
        State(Elevator& elevator);

    public:
        virtual void CallElevatorAction() = 0;
        virtual void GoToFloorAction() = 0;
        virtual void OpenDoorAction() = 0;
        virtual void CloseDoorAction() = 0;

    private:
        Elevator& mElevator;
    };

    class IdleState : public State
    {
        void CallElevatorAction() override;
        void GoToFloorAction() override;
        void OpenDoorAction() override;
        void CloseDoorAction() override;
    };

    class MovingState : public State
    {
        void CallElevatorAction() override;
        void GoToFloorAction() override;
        void OpenDoorAction() override;
        void CloseDoorAction() override;
    };
}

////////////// ELEVATOR //////////////

class Elevator
{
    using ActionsQueue = std::queue<ElevatorData::Action>;
    using aBool        = std::atomic<bool>;
    using cVariable    = std::condition_variable;

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
    void ProcessActions();

private:
    ActionsQueue mActionsQueue;
    std::mutex   mActionsQueueMutex;

    std::thread mProcessingThread;
    aBool       mProcessingRunning {true};
    cVariable   mProcessingCVariable;
};
