#pragma once

class ClientSidedUI : public Module
{
public:
    ClientSidedUI(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("InvFix", "Misc", "Makes inventory clientsided", keybind, enabled)
    {}

    void onEvent(PacketSendingEvent* event) override
    {
        if (event->Packet->instanceOf<InteractPacket>())
        {
            InteractPacket* pkt = reinterpret_cast<InteractPacket*>(event->Packet);

            if (pkt->action == Action::OPEN_INVENTORY)
            {
                *event->cancelled = true;

                Game::GetLocalPlayer()->openInventory();

                return;
            }
        }
    }
};