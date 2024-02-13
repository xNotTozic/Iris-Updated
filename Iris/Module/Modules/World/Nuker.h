#pragma once

class Nuker : public Module
{
public:
    Nuker(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Nuker", "World", "Nukes blocks in a radius around you", keybind, enabled)
    {
        addSlider("Radius", "How far around you is nuked", &radius, 1, 12);
        addBool("Liquids", "Allow nuker to break liquids", &liquids);
        addBool("Ore Breaker", "Only nuke ore tiles", &orebreaker);
    }

    float radius = 3;
    bool liquids = false;
    bool orebreaker = false;

    void onEvent(UpdateEvent* event) override
    {
        Player* player = Game::GetLocalPlayer();
        GameMode* gamemode = player->getGameMode();

        if (!gamemode || !player)
            return;

        Vector3<int> playerBlockPos = player->GetBlockPosition();

        for (int x = -radius; x <= radius; ++x)
        {
            for (int y = -radius; y <= radius; ++y)
            {
                for (int z = -radius; z <= radius; ++z)
                {
                    Vector3<int> blockPos = playerBlockPos + Vector3<int>(x, y, z);

                    BlockSource* source = Game::GetInstance()->getBlockSource();

                    if (!source)
                        return;

                    Block* block = source->getBlock(blockPos);

                    if (orebreaker)
                    {
                        if (strcmp(block->GetTileName()->getText(), "tile.diamond_ore") == 0
                            || strcmp(block->GetTileName()->getText(), "tile.emerald_ore") == 0
                            || strcmp(block->GetTileName()->getText(), "tile.coal_ore") == 0
                            || strcmp(block->GetTileName()->getText(), "tile.mob_spawner") == 0)
                        {

                        }
                        else continue;
                    }

                    if (blockPos.distance(playerBlockPos) <= radius)
                    {
                        if (blockPos.y <= -64)
                        {
                            if (strcmp(block->GetTileName()->getText(), "tile.bedrock") == 0)
                            {
                                continue;
                            }
                        }

                        if (!liquids)
                        {
                            if (block->GetMaterialType() != MaterialType::Lava && block->GetMaterialType() != MaterialType::Water)
                            {
                                BreakBlock(gamemode, blockPos);
                            }
                        }
                        else
                        {
                            BreakBlock(gamemode, blockPos);
                        }
                    }
                }
            }
        }
    }

    void BreakBlock(GameMode* gamemode, Vector3<int> blockPos)
    {
        gamemode->destroyBlock(blockPos, Placement::Down, true);
    }
};