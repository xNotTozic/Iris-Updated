#pragma once

class AirStuck : public Module
{
public:
    AirStuck(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("AirStuck", "World", "Freeze your player in place", keybind, enabled)
    {
        addBool("TrueStuck", "Forcefully lock the position", &trueStuck);
    }

    bool trueStuck = true;

    Vector3<float> enPos;

    void onEnabled() override
    {
        if (!Game::GetLocalPlayer())
            return;

        Player* player = Game::GetLocalPlayer();

        enPos = player->GetPosition();
    }

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer())
            return;

        Player* player = Game::GetLocalPlayer();
        StateVectorComponent* stateVec = player->try_get<StateVectorComponent>();

        if (!stateVec)
            return;

        stateVec->r_Velocity = { 0, 0, 0 };

        if (trueStuck)
        {
            player->TeleportTo(enPos);
        }
    }
};