#pragma once

class NoPacket : public Module // this wont be fun to keep clean
{
public:
    NoPacket(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("NoPacket", "World", "Stop sending all outgoing packets", keybind, enabled)
    {}

    void onEvent(PacketSendingEvent* event) override
    {
        *event->cancelled = true;
    }
};