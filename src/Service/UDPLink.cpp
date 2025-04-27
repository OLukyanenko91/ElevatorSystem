#include <unistd.h>
#include <Logger.hpp>
#include "UDPLink.hpp"

#define LOG_MODULE_NAME "UDPLink"


namespace
{
    int8_t   FAILED_RESULT_CODE = -1;
    uint16_t BUFFER_SIZE        = 2048;
}


UDPLink::UDPLink()
{}

bool UDPLink::Connect(const uint16_t localPort,
                      const uint16_t remotePort,
                      const std::string remoteHost)
{
    // Check connection
    if (mConnected) {
        lmWarning() << "Already connected";
        return false;
    }
    else {
        mConnected = false;
    }

    // Create socket
    auto socketFD = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFD == FAILED_RESULT_CODE) {
        lmWarning() << "Failed to create socket";
    }
    else {
        mSocket = socketFD;

        // Create local address
        sockaddr_in localAddr;
        localAddr.sin_family = AF_INET;
        localAddr.sin_addr.s_addr = INADDR_ANY;
        localAddr.sin_port = htons(localPort);

        // Bind socket
        auto result = bind(socketFD,
                           (sockaddr*)&localAddr,
                           sizeof(localAddr));
        if (result == FAILED_RESULT_CODE) {
            lmWarning() << "Failed to bind socket";
        }
        else {
            // Create target address
            sockaddr_in targetAddr;
            targetAddr.sin_family = AF_INET;
            inet_pton(AF_INET,
                      remoteHost.c_str(),
                      &targetAddr.sin_addr);
            targetAddr.sin_port = htons(remotePort);

            mTargetAddress = targetAddr;
            mConnected = true;
        }
    }

    return mConnected;
}

void UDPLink::StartReading(DataHandlerCb callback)
{
    if (mReading) {
        lmWarning() << "Already reading";
    }
    else {
        mReadingThread = std::thread(&UDPLink::ReadData,
                                     this,
                                     callback);
        mReading = true;
    }
}

void UDPLink::SendData(const uint8_t* buffer,
                       const uint16_t size)
{
    if (mConnected) {
        auto sentNumber = sendto(mSocket, buffer, size, 0,
                                 (sockaddr*)&mTargetAddress, sizeof(mTargetAddress));
        if (sentNumber == FAILED_RESULT_CODE) {
            lmWarning() << "Failed to send data";
        }
        else {
            lmDebug() << "Sent " << sentNumber << " bytes";
        }
    }
}

void UDPLink::ReadData(DataHandlerCb dataHandlerCb)
{
    uint8_t buffer[BUFFER_SIZE];

    while (true) {
        sockaddr_in senderAddr;
        socklen_t addrSize = sizeof(senderAddr);
        ssize_t bytesNumber = recvfrom(mSocket, buffer, sizeof(buffer), 0,
                                       (sockaddr*)&senderAddr, &addrSize);

        if (bytesNumber > 0 && dataHandlerCb) {
            dataHandlerCb(buffer, bytesNumber);
        }
    }
}
