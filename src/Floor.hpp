#pragma once

#include <cstdint>


class Floor
{
    friend class Service;

public:
    Floor(const uint8_t number);

private:
    uint8_t mNumber {0};
};
