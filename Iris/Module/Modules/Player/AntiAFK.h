#pragma once

class AntiAFK : public Module
{
public:
    AntiAFK(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("AntiAFK", "Player", "Avoids getting kicked for AFK", keybind, enabled)
    {}

    void onEvent(UpdateEvent* event) override
    {
        bool w = Game::Core::Keymap[GameInput::Forwards];
        bool a = Game::Core::Keymap[GameInput::Left];
        bool s = Game::Core::Keymap[GameInput::Backwards];
        bool d = Game::Core::Keymap[GameInput::Right];

        bool isMoving = w || a || s || d;

        if (isMoving)
        {
            TimeUtil::resetTime("ANTIAFK");
            return;
        }

        if (!Game::GetLocalPlayer())
            return;

        Player* player = Game::GetLocalPlayer();

        if (!player)
            return;

        StateVectorComponent* stateVec = player->try_get<StateVectorComponent>();

        if (!stateVec)
            return;

        if (TimeUtil::hasTimeElapsed("ANTIAFK", 30000, true))
        {
            stateVec->r_Velocity = { 0, 0.4f, 0 };
        }
    }
};