#include <unistd.h>
#include <Logger.hpp>
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

    while(true) {
        lmInfo() << "Test";
        sleep(1);
    }
}
