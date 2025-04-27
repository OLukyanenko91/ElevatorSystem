#pragma once

#include "src/Service/UDPLink.hpp"


class Service;

class MAVLinkHandler
{
public:
    MAVLinkHandler(Service& commandHandler);

public:
    void StartHandling(const uint16_t localPort,
                       const uint16_t remotePort,
                       const std::string remoteHost);
    void SendHeartbeat();

private:
    void ProcessUDPData(const uint8_t* buffer,
                        const uint16_t size);

private:
    UDPLink  mUDPLink;
    Service& mCommandHandler;
};
