#pragma once

#include <memory>


class Elevator;

namespace ElevatorSM
{
    class State;

    class StateMachine
    {
    public:
        std::unique_ptr<State> mCurrentState;
    };


    class State
    {
    public:
        State(Elevator& elevator);

    public:
        virtual void Enter() = 0;
        // virtual void CallElevatorAction() = 0;
        // virtual void GoToFloorAction() = 0;
        // virtual void OpenDoorAction() = 0;
        // virtual void CloseDoorAction() = 0;

    protected:
        Elevator& mElevator;
    };

    class IdleState : public State
    {
    public:
        IdleState(Elevator& elevator);

    public:
        void Enter() override;
        // void CallElevatorAction() override;
        // void GoToFloorAction() override;
        // void OpenDoorAction() override;
        // void CloseDoorAction() override;
    };

    class CalledFromFloorState : public State
    {
    public:
        CalledFromFloorState(Elevator& elevator,
                             const uint8_t floor);

    public:
        void Enter() override;

    private:
        uint8_t mFloor;
    };

    // class MovingState : public State
    // {
    // public:
    //     MovingState(Elevator& elevator);

    // public:
    //     // void CallElevatorAction() override;
    //     // void GoToFloorAction() override;
    //     // void OpenDoorAction() override;
    //     // void CloseDoorAction() override;
    // };
}
