#pragma once

#include "Manager.hpp"


class Service
{
public:
    explicit Service(Manager& manager);

private:
    Manager& mManager;
};
