#pragma once

class Criticals : public Module
{
public:
    float reach = 3.f;
    Criticals(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Criticals", "Combat", "Makes every hit packet a critical", keybind, enabled)
    {
        addEnum("Mode", "The type of server the criticals will target", { "Vanilla" }, &critStyle);
    }

    int critStyle = 0;

    void onEvent(PacketSendingEvent* event) override
    {
        switch (critStyle)
        {
        case 0: // vanilla criticals cant be done any other way anymore
            if (event->Packet->instanceOf<PlayerAuthInputPacket>())
            {
                PlayerAuthInputPacket* packet = reinterpret_cast<PlayerAuthInputPacket*>(event->Packet);
                packet->pos = packet->pos + Vector3<float>(0, 2, 0);
            }

            if (event->Packet->instanceOf<MovePlayerPacket>())
            {
                MovePlayerPacket* packet = reinterpret_cast<MovePlayerPacket*>(event->Packet);

                packet->position = packet->position + Vector3<float>(0, 2, 0);
                packet->onGround = false;
            }
            break;
        }
        
    }
};