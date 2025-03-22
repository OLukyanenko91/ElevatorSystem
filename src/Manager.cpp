#include <unistd.h>
#include <Logger.hpp>

// Test
#include <random>

#include "Manager.hpp"
#include "version.hpp"

#define LOG_MODULE_NAME "Manager"


Manager::Manager()
{
    lmInfo() << "ElevatorSystem version: " << PROJECT_VERSION;
}

void Manager::StartSystem()
{
    lmInfo() << "Start system";

    // Test
    std::random_device rd;  // Obtain a random seed
    std::mt19937 gen(rd()); // Initialize Mersenne Twister PRNG
    std::uniform_int_distribution<int> dist(1, 5); // Define range [1, 5]

    while(true) {
        switch (dist(gen)) {
        case 1:
            mElevator.OpenDoor();
            break;
        case 2:
            mElevator.CloseDoor();
            break;
        case 3:
            mElevator.Stop();
            break;
        case 4:
            mElevator.GoToFloor(dist(gen));
            break;
        case 5:
            mElevator.CalledFromFloor(dist(gen));
            break;
        default:
            break;
        }

        sleep(1);
    }
}
