#pragma once

class Speed : public Module
{
public:
    Speed(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Speed", "Movement", "Move faster", keybind, enabled)
    {
        addEnum("Mode", "The mode of speed niga", { "Vanilla", "Friction" }, &mode);
        addSlider("Speed", "How fast you will go", &speed, 0, 2);
        addSlider("Friction", "How fast you will slowdown off ground", &friction, 0.1, 5);
        addSlider("Height", "How high you will jump", &height, 0, 0.42);
        addSlider("Timer", "Increase the game timer", &timerSpeed, 0, 60);

        ingameOnly = true; // cant use keybind unless on the toast screen
    }

    float timerSpeed = 20;

    float speed = 0.5f;
    float height = 0.42f;
    float friction = 2.50f;

    int mode = 1;

    void onEvent(PacketSendingEvent* event) override 
    {
        auto player = Game::GetLocalPlayer();
        if (!player || !event->Packet) {
            return;
        }

        if (event->Packet->instanceOf<PlayerAuthInputPacket>()) {
            PlayerAuthInputPacket* p = reinterpret_cast<PlayerAuthInputPacket*>(event->Packet);
            p->setFlag(InputFlag::StopSprinting, false);
            p->setFlag(InputFlag::StartSprinting, true);
            p->setFlag(InputFlag::SprintDown, true);
            p->setFlag(InputFlag::Sprinting, true);

            if (player->isOnGround()) {
                p->setFlag(InputFlag::StartJumping, true);
            }
            else {
                p->setFlag(InputFlag::JumpDown, true);
                p->setFlag(InputFlag::Jumping, true);
            }
        }
    }

    void onEvent(UpdateTickEvent* event) override
    {
        if (Game::Core::IsInChat())
            return;

        if (getModuleByName("flight") && getModuleByName("flight")->isEnabled()) {
            return;
        }

        auto context = Game::GetInstance();
        if (!context) {
            return;
        }

        auto player = Game::GetLocalPlayer();
        if (!player) {
            return;
        }

        player->setSprinting(true);

        Game::GetInstance()->getMinecraft()->setTimerSpeed(timerSpeed);

        auto stateVec = player->try_get<StateVectorComponent>();
        if (!stateVec)
            return;

        auto
            w = Game::Core::Keymap[GameInput::Forwards],
            a = Game::Core::Keymap[GameInput::Left],
            s = Game::Core::Keymap[GameInput::Backwards],
            d = Game::Core::Keymap[GameInput::Right];

        bool keyPressed = context->mcGame->canUseMoveKeys() && (w || a || s || d);

        auto onGround = Game::GetLocalPlayer()->getMovementProxy()->isOnGround();

        switch (mode)
        {
        case 0:
        {
            // Are we holding movement keys?
            if (keyPressed)
            {
                // Should we jump?
                if (height > 0 && onGround)
                {
                    player->jumpFromDaGround();
                    stateVec->r_Velocity.y = height;
                }
                MoveUtil::setSpeed(speed);
            }
            break;
        }
        case 1:
        {
            static float currentSpeed = speed;

            // Are we holding movement keys?
            if (keyPressed)
            {
                // Should we jump?
                if (height > 0 && onGround)
                {
                    player->jumpFromDaGround();
                    stateVec->r_Velocity.y = height;

                    // Set our speed onGround
                    currentSpeed = speed;
                }
                MoveUtil::setSpeed(currentSpeed);
            }

            // Apply air friction
            float frictionFactor = friction; // Adjust this value to control the rate of speed reduction
            currentSpeed *= (1 - frictionFactor * RenderUtil::getDeltaTime());
            break;
        }
        }
    }

    void onDisabled() override
    {
        Game::GetInstance()->getMinecraft()->setTimerSpeed(20);
    }
};