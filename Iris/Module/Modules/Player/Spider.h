#pragma once

class Spider : public Module
{
public:
    Spider(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Spider", "Player", "Climb up walls just like a spider", keybind, enabled)
    {
        addSlider("Speed", "How fast you go up or down", &speed, 0.1f, 1);
    }

    float speed = 0.4f;

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer() || !Game::GetLocalPlayer()->getMovementProxy())
            return;

        Player* player = Game::GetLocalPlayer();
        DirectPlayerMovementProxy* proxy = player->getMovementProxy();

        if (proxy->getHorizontalCollision())
        {
            bool w = Game::Core::Keymap[GameInput::Forwards];
            bool a = Game::Core::Keymap[GameInput::Left];
            bool s = Game::Core::Keymap[GameInput::Backwards];
            bool d = Game::Core::Keymap[GameInput::Right];
            bool space = Game::Core::Keymap[VK_SPACE];
            bool shift = Game::Core::Keymap[VK_SHIFT];

            if (w || a || s || d || space || shift)
            {
                StateVectorComponent* state = Game::GetLocalPlayer()->try_get<StateVectorComponent>();

                if (!state)
                    return;

                state->r_Velocity.y = shift ? -speed : speed;
            }
        }
    }
};