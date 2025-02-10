#include <unistd.h>
#include <Logger.hpp>
#include <SettingsLoader.hpp>


int main(int argc, char *argv[])
{
    auto settings = SettingsLoader::GetSettings();
    if (settings.valid) {
        while(true) {
            lInfo() << "Test";
            sleep(1);
        }
    }

    return 0;
}
