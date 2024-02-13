#pragma once

class Disabler : public Module // this wont be fun to keep clean
{
public:
    Disabler(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Disabler", "Misc", "Basic version of an anticheat disabler", keybind, enabled)
    {
        addEnum("Mode", "The mode of which the disabler will work", { "Sentinel", "OnGround" }, &disablerMode);
    }

    void onEvent(PacketSendingEvent* event) override
    {
        Packet* pkt = event->Packet;

        switch (disablerMode)
        {
        case 0: //Cubecraft
            if (pkt->instanceOf<NetworkStackLatencyPacket>())
            {
                *event->cancelled = true;
            }
            break;
        case 1: //OnGround
            if (pkt->instanceOf<MovePlayerPacket>())
            {
                MovePlayerPacket* packet = reinterpret_cast<MovePlayerPacket*>(pkt);
                packet->onGround = true;
            }
            break;
        }
    }

    void onEvent(UpdateTickEvent* event) override
    {
        ClientInstance* instance = Game::GetInstance();
        LoopbackPacketSender* sender = instance->getPacketSender();

        if (!sender || !instance || !Game::GetLocalPlayer())
        {
            return;
        }

        switch (disablerMode)
        {
        case 0: //Cubecraft
        {
            if (TimeUtil::hasTimeElapsed("gmTick", 50, true))
            {
                MovePlayerPacket pkt(Game::GetLocalPlayer(), Game::GetLocalPlayer()->getPosition(), Game::GetLocalPlayer()->getMovementProxy()->getRotation(), Game::GetLocalPlayer()->getMovementProxy()->isOnGround());
                pkt.mode = TELEPORT;
                for (int i = 0; i < 10; i++)
                {
                    sender->sendToServer(&pkt);
                }
            }
            break;
        }
        }
    }
};