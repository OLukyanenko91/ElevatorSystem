#pragma once

#include <cstdint>


class Elevator;

class Floor
{
    friend class Service;

public:
    Floor(uint8_t number,
          Elevator& elevator);

private:
    void CallButtonPushed();

private:
    uint8_t   mNumber {0};
    Elevator& mElevator;
};
