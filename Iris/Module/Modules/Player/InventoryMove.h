#pragma once

class InventoryMove : public Module
{
public:
    InventoryMove(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("GuiMove", "Player", "Allow you to move while in GUIs", keybind, enabled)
    {
        addEnum("Mode", "The type of method used", { "Vanilla" }, &mode);
    }

    float speed = 0.432f;
    float height = 0.42f;

    int mode = 0;

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer() || !Game::GetLocalPlayer()->getMovementProxy() || Game::Core::IsInChat())
            return;

        MinecraftUIRenderContext* context = event->Context;

        Player* player = Game::GetLocalPlayer();
        DirectPlayerMovementProxy* proxy = player->getMovementProxy();

        MovementInterpolatorComponent* movement = player->try_get<MovementInterpolatorComponent>();
        StateVectorComponent* stateVec = player->try_get<StateVectorComponent>();

        if (!movement || !stateVec)
            return;

        bool w = Game::Core::Keymap[GameInput::Forwards];
        bool a = Game::Core::Keymap[GameInput::Left];
        bool s = Game::Core::Keymap[GameInput::Backwards];
        bool d = Game::Core::Keymap[GameInput::Right];

        bool pressed = !context->ClientInstance->mcGame->canUseMoveKeys() && (w || a || s || d);
        auto calcYaw = movement->Rotations.y;

        updateYaw(w, a, s, d, calcYaw);

        auto calcYawF = calcYaw * (3.1415927f / 180);
        if (pressed)
        {
            switch (mode)
            {
            case 0:
                if (player->isOnGround() && Game::Core::Keymap[Keyboard::SPACEBAR])
                    stateVec->r_Velocity.y = height;

                stateVec->r_Velocity.x = cos(calcYawF) * (speed / 2);
                stateVec->r_Velocity.z = sin(calcYawF) * (speed / 2);
                break;
            }
        }
    }

    void updateYaw(bool w, bool a, bool s, bool d, float& calcYaw)
    {
        if (w)
        {
            if (!a && !d)
                calcYaw += 90.f;
            else if (a)
                calcYaw += 45.f;
            else if (d)
                calcYaw += 135.f;
        }
        else if (s)
        {
            if (!a && !d)
                calcYaw -= 90.f;
            else if (a)
                calcYaw -= 45.f;
            else if (d)
                calcYaw -= 135.f;
        }
        else if (!w && !s)
        {
            if (!a && d)
                calcYaw += 180.f;
        }
        if (w && s) {
            calcYaw -= 90.f;
        }
    }
};