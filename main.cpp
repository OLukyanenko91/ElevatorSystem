#include "Logger/Logger.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
    while(true) {
        lInfo() << "Test";
        sleep(1);
    }

    return 0;
}
