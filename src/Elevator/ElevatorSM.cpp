#include "src/Elevator/Elevator.hpp"
#include "ElevatorSM.hpp"


ElevatorSM::State::State(Elevator& elevator)
    : mElevator(elevator)
{}

ElevatorSM::IdleState::IdleState(Elevator& elevator)
    : State(elevator)
{}

void ElevatorSM::IdleState::Enter()
{

}

// ElevatorSM::MovingState::MovingState(Elevator &elevator)
//     : State(elevator)
// {

// }

ElevatorSM::CalledFromFloorState::CalledFromFloorState(Elevator& elevator,
                                                       const uint8_t floor)
    : State(elevator)
    , mFloor(floor)
{

}

void ElevatorSM::CalledFromFloorState::Enter()
{
    // mElevator.
}

// void ElevatorSM::IdleState::CallElevatorAction()
// {

// }

// void ElevatorSM::IdleState::GoToFloorAction()
// {

// }

// void ElevatorSM::IdleState::OpenDoorAction()
// {

// }

// void ElevatorSM::IdleState::CloseDoorAction()
// {

// }

// void ElevatorSM::MovingState::CallElevatorAction()
// {

// }

// void ElevatorSM::MovingState::GoToFloorAction()
// {

// }

// void ElevatorSM::MovingState::OpenDoorAction()
// {

// }

// void ElevatorSM::MovingState::CloseDoorAction()
// {

// }
