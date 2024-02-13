#pragma once

class NoFall : public Module
{
public:
    NoFall(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("NoFall", "Misc", "Use varies to nullify fall damage (Servers Only)", keybind, enabled)
    {
        addEnum("Mode", "What type of method to use", { "Vanilla" }, &switchMode);
    }

    int switchMode = 0;

    bool upDown = false;

    void onEvent(GameModeTickEvent* event)
    {
        if (!Game::GetLocalPlayer())
            return;

        Player* player = Game::GetLocalPlayer();

        if (switchMode == 1)
        {
            MovePlayerPacket lbPkt(player, player->GetPosition(), player->getMovementProxy()->getRotation(), false);
            Game::GetInstance()->getPacketSender()->sendToServer(&lbPkt);
        }
    }

    void onEvent(PacketSendingEvent* event) override
    {
        if (switchMode == 1)
        {
            if (event->Packet->instanceOf<PlayerAuthInputPacket>())
            {
                PlayerAuthInputPacket* packet = reinterpret_cast<PlayerAuthInputPacket*>(event->Packet);

                upDown = !upDown;

                if (upDown)
                {
                    packet->pos = packet->pos + Vector3<float>(0, 0.4f, 0);
                }
                else packet->pos = packet->pos + Vector3<float>(0, 0.3f, 0);
            }
        }


        if (switchMode == 0)
        {
            if (event->Packet->instanceOf<MovePlayerPacket>() || event->Packet->instanceOf<PlayerAuthInputPacket>())
            {
                if (!Game::GetLocalPlayer())
                    return;

                Player* player = Game::GetLocalPlayer();

                player->respawn();
            }
        }
    }
};