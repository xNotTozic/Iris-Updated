#pragma once

class LifeboatTickAction : public Module
{
public:
    LifeboatTickAction(int keybind = Keyboard::NONE, bool enabled = true) :
        Module("LifeboatTickAction", "Misc", "You shouldnt be able to see this", keybind, enabled)
    {
        visible_ = false;
        exists = false;
        showNotifications = false;
    }

    void onEvent(PacketSendingEvent* event) override
    {
        if (!Game::GetLocalPlayer())
            return;
        
        if (event->Packet->instanceOf<PlayerAuthInputPacket>())
        {
            PlayerAuthInputPacket* packet = reinterpret_cast<PlayerAuthInputPacket*>(&event->Packet);

            if (lifeboatTpTarget == Vector3<float>(0, 0, 0))
                return;

            Vector3<float> point1 = Game::GetLocalPlayer()->GetPosition();
            Vector3<float> point2 = lifeboatTpTarget;

            if (point1 == point2)
            {
                setEnabled(false);

                Game::GetInstance()->getMinecraft()->setTimerSpeed(20);
            }

            Vector3<float> nextPoint = getNextPoint(point1, point2);

            if (point1.distance(point2) <= 15)
            {
                Game::GetLocalPlayer()->TeleportTo(lifeboatTpTarget);

                lifeboatTpTarget = Vector3<float>(0, 0, 0);

                Game::GetInstance()->getMinecraft()->setTimerSpeed(20);
                
                return;
            }

            Game::GetLocalPlayer()->TeleportTo(nextPoint); // hopefuly that fixes that

            if (point1.distance(point2) >= 1000)
            {
                lifeboatTpTarget = Vector3<float>(0, 0, 0);

                Game::GetInstance()->getMinecraft()->setTimerSpeed(20);

                ChatUtil::sendMessage("You can only teleport 1000 blocks at a time!");

                return;
            }
        }
    }
};