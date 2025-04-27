#include <unistd.h>
#include <Logger.hpp>
#include "Service.hpp"
#include "MAVLinkHandler.hpp"
#include "elevator/mavlink.h"

#define LOG_MODULE_NAME "MAVLinkHandler"


namespace
{
    const auto SYSTEM_ID    = 1;
    const auto COMPONENT_ID = 1;
}


MAVLinkHandler::MAVLinkHandler(Service& commandHandler)
    : mUDPLink()
    , mCommandHandler(commandHandler)
{}

void MAVLinkHandler::StartHandling(const uint16_t localPort,
                                   const uint16_t remotePort,
                                   const std::string remoteHost)
{
    if (mUDPLink.Connect(localPort,
                         remotePort,
                         remoteHost)) {
        mUDPLink.StartReading([this](const uint8_t* buffer,
                                     const uint16_t size) {
            this->ProcessUDPData(buffer, size);
        });
    }
}

void MAVLinkHandler::SendHeartbeat()
{
    mavlink_message_t msg;
    mavlink_heartbeat_t heartbeat;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_heartbeat_encode(SYSTEM_ID, COMPONENT_ID,
                                 &msg, &heartbeat);
    uint16_t length = mavlink_msg_to_send_buffer(buffer, &msg);
    mUDPLink.SendData(buffer, length);

    lmDebug() << "MAVLINK_MSG_ID_HEARTBEAT message sent";
}

void MAVLinkHandler::ProcessUDPData(const uint8_t* buffer,
                                    const uint16_t size)
{
    mavlink_message_t msg;
    mavlink_status_t status;

    for (ssize_t i = 0; i < size; ++i) {
        if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i],
                               &msg, &status)) {
            if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                mavlink_heartbeat_t heartbeat;
                mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                lmDebug() << "Heartbeat received";
            }
            else if (msg.msgid == MAVLINK_MSG_ID_COMMAND_LONG) {
                mavlink_command_long_t commandLong;
                mavlink_msg_command_long_decode(&msg, &commandLong);

                if (commandLong.command == MAV_CMD_ELEVATOR_GO_TO_FLOOR) {
                    lmDebug() << "Command MAV_CMD_ELEVATOR_GO_TO_FLOOR received";
                    mCommandHandler.GoToFloorCmdReceived(int(commandLong.param1));
                }
                else if (commandLong.command == MAV_CMD_ELEVATOR_CALL_FROM_FLOOR) {
                    lmDebug() << "Command MAV_CMD_ELEVATOR_CALL_FROM_FLOOR received";
                    mCommandHandler.CallFromFloorCmdReceived(int(commandLong.param1));
                }
            }
        }
    }
}
