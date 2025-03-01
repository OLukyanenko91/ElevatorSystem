#include <Logger.hpp>
#include <SettingsLoader.hpp>
#include "src/Manager.hpp"


int main(int argc, char *argv[])
{
    auto settings = SettingsLoader::GetSettings();
    if (settings.valid) {
        Manager manager;
        manager.StartSystem();
    }

    return 0;
}
