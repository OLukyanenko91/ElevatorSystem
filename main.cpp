#include <unistd.h>
#include <Logger.hpp>
#include <SettingsLoader.hpp>
#include "src/Manager.hpp"


int main(int argc, char *argv[])
{
    auto settings = SettingsLoader::GetSettings();
    if (settings.valid) {
        Manager manager;

        while (true) {
            sleep(1);
        }
    }

    return 0;
}
