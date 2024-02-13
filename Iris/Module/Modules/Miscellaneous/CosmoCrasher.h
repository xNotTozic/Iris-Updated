#pragma once

class CosmoCrasher : public Module
{
public:
    CosmoCrasher(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Crasher", "Misc", "Sends a large amount of block packets", keybind, enabled)
    {
        addSlider("Amount", "How far around you is included", &radius, 1, 12);
        addEnum("Type", "What kind of block packet is used", { "Place", "Break", "Interact", "Position"}, &type);

        IngameOnly();
    }

    float radius = 3;
    int type = 0;

    void onEvent(GameModeTickEvent* event) override
    {
        if (!Game::GetGameMode() || !Game::GetLocalPlayer() || !Game::GetInstance()->getBlockSource())
            return;

        BlockSource* source = Game::GetInstance()->getBlockSource();
        GameMode* gamemode = Game::GetGameMode();
        Player* player = Game::GetLocalPlayer();

        Vector3<int> playerBlockPos = player->GetBlockPosition();

        for (int x = -radius; x <= radius; ++x)
        {
            for (int y = -radius; y <= radius; ++y)
            {
                for (int z = -radius; z <= radius; ++z)
                {
                    Vector3<int> blockPos = playerBlockPos + Vector3<int>(x, y, z);

                    if (Vector3<int>(playerBlockPos.x, playerBlockPos.y - 1, playerBlockPos.z) == blockPos)
                        continue;

                    switch (type)
                    {
                    case 0:
                        gamemode->buildBlock(blockPos, Placement::Down, true);
                        break;

                    case 1:
                        gamemode->destroyBlock(blockPos, Placement::Down, true);
                        break;

                    case 2:
                        gamemode->interact(Game::GetLocalPlayer(), blockPos.ToFloat());
                        break;
                    }
                }
            }
        }
    }

    void onEvent(PacketSendingEvent* event) override
    {
        if (type == 3)
        {
            if (event->Packet->instanceOf<PlayerAuthInputPacket>())
            {
                PlayerAuthInputPacket* packet = reinterpret_cast<PlayerAuthInputPacket*>(event->Packet);

                packet->pos = Vector3<float>(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
            }

            if (event->Packet->instanceOf<MovePlayerPacket>())
            {
                MovePlayerPacket* packet = reinterpret_cast<MovePlayerPacket*>(event->Packet);

                packet->position = Vector3<float>(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
            }
        }
    }
};