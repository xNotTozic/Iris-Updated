#pragma once

class Flight : public Module
{
public:

    int mode = 0;

    Flight(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Flight", "Movement", "Fly like a bird!", keybind, enabled)
    {
        addEnum("Mode", "The type of fly", { "Lifeboat", "Elyra", "Jetpack", "Vanilla"}, &mode);
        addSlider("Horizontal", "The speed of hortizontal movement", &speed, 0, 30);
        addSlider("Vertical", "The speed of vertical movement", &vertical, 0, 60);
        addSlider("Glide", "The speed of up and down speed", &downglide, -1, 1);
        addSlider("Radius", "Some extra offset for servers like lifeboat", &radius, 0, 1);
        addSlider("VClip", "The amount of blocks you teleport up", &teleportheight, 0, 2);
        addSlider("Timer", "Internal games timer speed", &timerSpeed, 0, 60);
        addSlider("FlightTimer", "Flights timer speed (Not game timer)", &flyUpdateSleep, 2, 60);
        addBool("InMotionTP", "Ported from fadeaway - Founder#2998", &forwardsTp);
        addBool("AlwaysVClip", "Teleport instead of using velocity for UP/DOWN", &upTp);

        ingameOnly = true; // cant use keybind unless on the toast screen
    }

    float speed = 2.8f;
    float flyUpdateSleep = 60;
    float vertical = 2.8f;
    float downglide = 0.f;
    float radius = 0.01f;
    float teleportheight = 0.f;
    float timerSpeed = 10.f;
    bool forwardsTp = false;
    bool upTp = false;

    void onEnabled() override
    {
        if (!Game::GetLocalPlayer())
            return;

        Player* player = Game::GetLocalPlayer();

        Vector3<float> playerPos = player->GetPosition();

        player->teleportTo({ playerPos.x , playerPos.y + teleportheight, playerPos.z}, true, 0, 0, true);
    }

    void onDisabled() override
    {
        if (!Game::GetInstance()->getMinecraft())
            return;

        ClientInstance* instance = Game::GetInstance();
        Minecraft* minecraft = instance->getMinecraft();

        minecraft->setTimerSpeed(20);
    }

    void onEvent(KeyboardEvent* event) override
    {
        if (mode == 1)
        {
            // elytra flight mode

            if (*event->Key == VK_SHIFT)
                *event->cancelled = true;

            if (*event->Key == VK_SPACE)
                *event->cancelled = true;
        }
    }

    void onEvent(UpdateEvent* event) override
    {
        if (TimeUtil::hasTimeElapsed("Ft", 1000 / (int)flyUpdateSleep, true))
        {
            if (!Game::GetLocalPlayer() || !Game::GetInstance()->getMinecraft() || !Game::GetInstance()->mcGame)
                return;

            Player* player = Game::GetLocalPlayer();
            ClientInstance* instance = Game::GetInstance();
            Minecraft* minecraft = Game::GetInstance()->getMinecraft();
            MinecraftGame* game = Game::GetInstance()->mcGame;

            // (Actor actor, Vector3<float> position, Vector2<float> rot, bool onGround)
            MovePlayerPacket lbPkt(player, player->GetPosition(), player->getMovementProxy()->getRotation(), false);
            instance->getPacketSender()->sendToServer(&lbPkt);

            minecraft->setTimerSpeed(timerSpeed);

            StateVectorComponent* stateVec = player->try_get<StateVectorComponent>();
            AABBShapeComponent* shape = player->try_get<AABBShapeComponent>();
            auto* movement = player->try_get<MovementInterpolatorComponent>();

            if (!stateVec || !shape or !movement)
                return;

            if (mode == 2)
            {
                Vector3<float> lookingVec = player->getLookingVector();

                stateVec->r_Velocity = Vector3<float>((speed / 20) * lookingVec.x, (speed / 20) * -lookingVec.y, (speed / 20) * lookingVec.z);

                return;
            }

            float angle = (movement->Rotations.y + 90) * 0.01745327; // () + PI / 180

            Vector3<float> newVel;

            if (Game::Core::Keymap[GameInput::Forwards] && !Game::Core::IsInChat())
            {
                newVel.x = cos(angle) * (speed / 20);
                newVel.z = sin(angle) * (speed / 20);
            }

            if (downglide != 0)
            {
                newVel.y = -(downglide / 20);
            }

            if (game->canUseMoveKeys())
            {
                if (Game::Core::Keymap[VK_SHIFT])
                {
                    newVel.y += -(vertical / 20);
                }

                if (Game::Core::Keymap[VK_SPACE])
                {
                    newVel.y += (vertical / 20);
                }
            }

            if (radius != 0)
            {
                Vector3<float> entityPos = player->GetPosition();

                float offsetX = static_cast<float>(rand() / RAND_MAX * (radius * 2) - radius); // makes sure their equally random
                offsetX *= (rand() % 2 == 0) ? 1 : -1;

                float offsetY = static_cast<float>(rand() / RAND_MAX * (radius * 2) - radius);
                offsetY *= (rand() % 2 == 0) ? 1 : -1;

                float offsetZ = static_cast<float>(rand() / RAND_MAX * (radius * 2) - radius);
                offsetZ *= (rand() % 2 == 0) ? 1 : -1;

                Vector3<float> newPos = Vector3<float>(entityPos.x + offsetX, entityPos.y + offsetY, entityPos.z + offsetZ);

                if (!Game::Core::IsInChat())
                {
                    player->TeleportTo(newPos + newVel); // directly apply the position delta
                }
            }

            if (forwardsTp == false)
            {
                stateVec->r_Velocity = newVel;

                if (Game::Core::Keymap[VK_CONTROL])
                {
                    stateVec->r_Velocity = stateVec->r_Velocity * 3;
                }
            }

            if (forwardsTp == true)
            {
                bool w = Game::Core::Keymap[GameInput::Forwards];
                bool a = Game::Core::Keymap[GameInput::Left];
                bool s = Game::Core::Keymap[GameInput::Backwards];
                bool d = Game::Core::Keymap[GameInput::Right];

                bool pressed = game->canUseMoveKeys() && (w || a || s || d);
                auto calcYaw = player->getMovementProxy()->getRotation().y;

                updateYaw(w, a, s, d, calcYaw);

                auto calcYawF = calcYaw * (3.1415927f / 180);
                if (pressed && !Game::Core::IsInChat())
                {
                    newVel.x = cos(calcYawF) * (speed / 20);
                    newVel.z = sin(calcYawF) * (speed / 20);
                }

                if (Game::Core::Keymap[VK_CONTROL])
                {
                    player->SetPos(shape->r_Pos_Lower + (newVel * 3));
                    stateVec->r_Velocity = newVel * 3;
                }
                else
                {
                    player->SetPos(shape->r_Pos_Lower + newVel);
                    stateVec->r_Velocity = newVel;
                }
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