#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include "Floor.hpp"


using FloorsMap = std::map<uint8_t, std::unique_ptr<Floor>>;
