#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <atomic>
#include "Floor.hpp"


using FloorsMap = std::map<uint8_t, std::unique_ptr<Floor>>;
using aBool     = std::atomic<bool>;
