#pragma once

class Glide : public Module
{
public:
    Glide(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Glide", "Player", "Allow you to glide like a little birdy", keybind, enabled)
    {
        addSlider("Speed", "How fast you go up or down", &speed, -1, 1);
    }

    float speed = 0.1f;

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer() || !Game::GetLocalPlayer()->try_get<StateVectorComponent>())
            return;

        Player* player = Game::GetLocalPlayer();
        StateVectorComponent* state = player->try_get<StateVectorComponent>();

        state->r_Velocity.y = speed;
    }
};