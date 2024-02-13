#pragma once

class FastStop : public Module
{
public:
    FastStop(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("FastStop", "Movement", "Quickly stops your player", keybind, enabled)
    {
        addSlider("Speed", "Speed of which to stop", &stopAmount, 2, 6);
    }

    float stopAmount = 6;

    void onEvent(KeyboardEvent* event) override
    {
        int key = *event->Key;

        Player* player = Game::GetLocalPlayer();
        ClientInstance* instance = Game::GetInstance();

        // Check if player or valid key is null
        if (!player || key != GameInput::Forwards && key != GameInput::Left && key != GameInput::Backwards && key != GameInput::Right)
            return;

        Game::Core::Keymap[key] = *event->Held; // Update key state

        bool w = Game::Core::Keymap[GameInput::Forwards];
        bool a = Game::Core::Keymap[GameInput::Left];
        bool s = Game::Core::Keymap[GameInput::Backwards];
        bool d = Game::Core::Keymap[GameInput::Right];

        bool isMoving = instance->mcGame->canUseMoveKeys() && (w || a || s || d);

        if (!isMoving)
        {
            StateVectorComponent* stateVec = player->try_get<StateVectorComponent>();

            // If state vector component is missing then no further action needed
            if (!stateVec)
                return;

            if (stopAmount != 6)
            {
                // Adjust velocity based on stop amount
                stateVec->r_Velocity.x /= stopAmount;
                stateVec->r_Velocity.z /= stopAmount;
            }
            else
            {
                // Set velocity to zero
                stateVec->r_Velocity.x = 0;
                stateVec->r_Velocity.z = 0;
            }
        }
    }
};