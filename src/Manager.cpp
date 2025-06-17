#include <Logger.hpp>
#include <SettingsLoader.hpp>
#include "Manager.hpp"
#include "version.hpp"

#define LOG_MODULE_NAME "Manager"


Manager::Manager()
{
    lmInfo() << "ElevatorSystem version: " << PROJECT_VERSION;

    GenerateFloors();
    mService.reset(new Service(mElevator,
                               mFloors));
}

void Manager::GenerateFloors()
{
    lmInfo() << "Generate floors";

     auto settings = SettingsLoader::GetSettings();
     for (int i = 0; i < settings.floorsCount; ++i)
     {
         mFloors[i] = std::make_unique<Floor>(Floor(i, mElevator));
     }
}
