#pragma once

class Blink : public Module // this wont be fun to keep clean
{
public:
    Blink(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Blink", "World", "Stop sending outgoing movement/input packets", keybind, enabled)
    {}

    void onEvent(PacketSendingEvent* event) override
    {
        if (event->Packet->instanceOf<MovePlayerPacket>()
            || event->Packet->instanceOf<PlayerAuthInputPacket>())
        {
            *event->cancelled = true;
        }
    }
};