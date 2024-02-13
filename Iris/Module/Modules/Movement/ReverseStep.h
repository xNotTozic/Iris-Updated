#pragma once

class ReverseStep : public Module
{
public:
    ReverseStep(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("ReverseStep", "Movement", "Like step but downwards", keybind, enabled)
    {
        addSlider("Speed", "The amount speed you get", &speed, 2, 50);
        ingameOnly = true; // cant use keybind unless on the toast screen
    }

    float speed = 20;

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer())
            return;

        Player* player = Game::GetLocalPlayer();

        StateVectorComponent* state = player->try_get<StateVectorComponent>();

        if (!state)
            return;

        if (player->isOnGround() && state->r_Velocity.y < 0 && !(state->r_Velocity.y < -1))
        {
            state->r_Velocity.y = -(speed / 20);
        }
    }
};