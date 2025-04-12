#include <unistd.h>
#include <random>
#include <thread>
#include <Logger.hpp>
#include "Service.hpp"

#define LOG_MODULE_NAME "Service"


Service::Service(Elevator& elevator,
                 FloorsMap& floors)
    : mElevator(elevator)
    , mFloors(floors)
{
    mProcessingThread = std::thread(&Service::Run, this);
}

void Service::Run()
{
    lmInfo() << "Run";

    // // Test
    // std::random_device rd;  // Obtain a random seed
    // std::mt19937 gen(rd()); // Initialize Mersenne Twister PRNG
    // std::uniform_int_distribution<int> dist(1, 5); // Define range [1, 5]

    // while(true) {
    //     switch (dist(gen)) {
    //     case 1:
    //         mElevator.OpenDoor();
    //         break;
    //     case 2:
    //         mElevator.CloseDoor();
    //         break;
    //     case 3:
    //         mElevator.Stop();
    //         break;
    //     case 4:
    //         mElevator.GoToFloor(dist(gen));
    //         break;
    //     case 5:
    //         mElevator.CalledFromFloor(dist(gen));
    //         break;
    //     default:
    //         break;
    //     }

    //     sleep(1);
    // }

    // Test 2
    sleep(5);
    mElevator.CalledFromFloor(4);
    sleep(15);
    mElevator.GoToFloor(0);
}
