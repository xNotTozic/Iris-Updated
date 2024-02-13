#pragma once

class Freecam : public Module
{
public:
    Freecam(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Freecam", "Player", "Freely move around client sidedly", keybind, enabled)
    {}

    Vector3<float> savedVel, savedCoords;

    void onEnabled() override
    {
        if (!Game::GetLocalPlayer() || !Game::GetLocalPlayer()->try_get<StateVectorComponent>())
            return;

        Player* player = Game::GetLocalPlayer();
        StateVectorComponent* state = player->try_get<StateVectorComponent>();

        savedVel = state->r_Velocity;
        savedCoords = player->GetPosition();
    }

    void onDisabled() override
    {
        if (!Game::GetLocalPlayer() || !Game::GetLocalPlayer()->try_get<StateVectorComponent>())
            return;

        Player* player = Game::GetLocalPlayer();
        StateVectorComponent* state = player->try_get<StateVectorComponent>();

        player->TeleportTo(savedCoords);
        state->r_Velocity = savedVel;
    }

    void onEvent(PacketSendingEvent* event) override
    {
        if (event->Packet->instanceOf<PlayerAuthInputPacket>() ||
            event->Packet->instanceOf<MovePlayerPacket>())
        {
            *event->cancelled = true;
        }
    }
};