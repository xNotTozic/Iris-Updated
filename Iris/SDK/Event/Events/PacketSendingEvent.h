#pragma once

class PacketSendingEvent : public Event
{
public:
    PacketSendingEvent(Packet* packet)
    {
        Packet = packet;
    }

    EventType getType() const override { return EventType::PacketSending; }
    Packet* Packet;
};