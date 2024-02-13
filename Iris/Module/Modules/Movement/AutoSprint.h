#pragma once

class AutoSprint : public Module
{
public:
    AutoSprint(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("AutoSprint", "Movement", "Sprint automatically", keybind, enabled)
    {
        addBool("OmniSprint", "Automatically sprint backwards too", &omni);
    }

    bool omni = false;

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer() || !Game::GetLocalPlayer()->getMovementProxy())
            return;

        Player* player = Game::GetLocalPlayer();
        DirectPlayerMovementProxy* proxy = player->getMovementProxy();

        bool forwards = Game::Core::Keymap[GameInput::Forwards];
        bool backwards = Game::Core::Keymap[GameInput::Backwards];

        // Check for horizontal collision and sneaking status
        if (!proxy->isSneaking())
        {
            if (omni && (forwards || backwards))
            {
                proxy->setSprinting(true); // Enable sprinting if omni-directional movement and forwards/backwars input
            }
            else if (!omni && forwards)
            {
                proxy->setSprinting(true); // Enable sprinting if uni-directional movement and forwards input
            }
        }
        else
        {
            proxy->setSprinting(false); // Disable spritning if there is horzontal collision or sneaking
        }
    }
};