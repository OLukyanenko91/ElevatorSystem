#include <unistd.h>
#include <thread>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <Logger.hpp>
#include "Service.hpp"
#include <SettingsLoader.hpp>

#define LOG_MODULE_NAME "Service"


Service::Service(Elevator& elevator,
                 FloorsMap& floors)
    : mElevator(elevator)
    , mFloors(floors)
    , mMAVHandler(*this)
{
    mProcessingThread = std::thread(&Service::Run, this);
}

void Service::Run()
{
    lmEnter();

    auto settings = SettingsLoader::GetSettings();
    mMAVHandler.StartHandling(settings.service.port,
                              settings.service.port,
                              settings.service.host);

    while(true) {
        mMAVHandler.SendHeartbeat();
        sleep(1);
    }
}

void Service::CallFromFloorCmdReceived(const uint8_t floor)
{
    lmInfo() << "Call from floor command received, floor " << int(floor);
    if (mFloors.find(floor) != mFloors.end()) {
        mFloors[floor]->CallButtonPushed();
    }
}

void Service::GoToFloorCmdReceived(const uint8_t floor)
{
    lmInfo() << "Go to floor command received, floor " << int(floor);
    mElevator.GoToFloor(floor);
}
