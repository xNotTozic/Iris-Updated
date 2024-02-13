#pragma once

#include <unordered_set>

struct BlockDat
{
    Vector3<float> Position;
    std::string TileName;
};

class OreSense : public Module
{
public:
    OreSense(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("OreSense", "Visual", "An ESP but for ores", keybind, enabled)
    {
        addEnum("Style", "Style of esp to use", { "Solid", "3D" }, &mode);
        addSlider("Radius", "How far around you the ESP will highlight ores", &radius, 16, 80);
    }

    float radius = 32;
    int mode = 1;

    std::vector<BlockDat> boundsMap{};

    void onEvent(BeforeUpdateEvent* event) override
    {
        GameMode* gamemode = Game::GetGameMode();
        Player* player = Game::GetLocalPlayer();

        if (!gamemode || !player)
            return;

        Vector3<int> playerBlockPos = player->GetBlockPosition();

        BlockSource* source = Game::GetInstance()->getBlockSource();

        if (!source)
            return;

        if (TimeUtil::hasTimeElapsed("RadarRate", 3000, true)) // 3000ms has passed
        {
            boundsMap = {};

            std::unordered_set<std::string> oreTilesSet;
            for (const std::string& oreTile : oreSenseTiles)
            {
                oreTilesSet.insert(oreTile);
            }

            for (int x = -radius; x <= radius; ++x)
            {
                for (int y = -radius; y <= radius; ++y)
                {
                    for (int z = -radius; z <= radius; ++z)
                    {
                        Vector3<int> blockPos = playerBlockPos + Vector3<int>(x, y, z);

                        Block* block = source->getBlock(blockPos);

                        const char* tileName = block->GetTileName()->getText();

                        if (block->GetMaterialType() == MaterialType::Air ||
                            strcmp(tileName, "tile.stone") == 0 ||
                            strcmp(tileName, "tile.netherrack") == 0 ||
                            strcmp(tileName, "tile.dirt") == 0) // avoid looping over tile vector if not needed
                        {
                            continue;
                        }

                        if (oreTilesSet.count(tileName) > 0)
                        {
                            BlockDat bloc;
                            bloc.Position = blockPos.ToFloat();
                            bloc.TileName = tileName;

                            boundsMap.push_back(bloc);
                        }
                    }
                }
            }
        }

        int index = 0;
        for (auto blockpair : boundsMap)
        {
            Vector3<float> blockPosss = blockpair.Position;

            std::string blocktype = blockpair.TileName;

            switch (mode)
            {
            case 0:
            {
                Vector3<float> blockLower = blockPosss + Vector3<float>(0.4f, 0.4f, 0.4f);
                Vector3<float> blockUpper = blockPosss + Vector3<float>(0.6f, 0.6f, 0.6f);

                Vector3<float> origin = Game::GetInstance()->getLevelRender()->getOrigin();
                float dist = origin.distance(blockLower);

                Vector2<float> output1, output2;
                if (!Game::GetInstance()->WorldToScreen(blockLower, output1) || !Game::GetInstance()->WorldToScreen(blockUpper, output2)) continue;

                std::vector<Vector3<float>> aabbArr;
                for (float x : { blockLower.x, blockUpper.x })
                {
                    for (float y : { blockLower.y, blockUpper.y })
                    {
                        for (float z : { blockLower.z, blockUpper.z })
                        {
                            aabbArr.push_back({ x, y, z });
                        }
                    }
                }

                std::vector<Vector2<float>> scrPoints;
                for (int i = 0; i < aabbArr.size(); i++)
                {
                    Vector2<float> scrPoint;
                    if (Game::GetInstance()->WorldToScreen(aabbArr[i], scrPoint))
                        scrPoints.push_back(scrPoint);
                }

                if (scrPoints.empty())
                    continue;

                Vector4<float> boundingRect = { scrPoints[0].x, scrPoints[0].y, scrPoints[0].x, scrPoints[0].y };
                for (const auto& point : scrPoints)
                {
                    boundingRect.x = std::min(boundingRect.x, point.x);
                    boundingRect.y = std::min(boundingRect.y, point.y);
                    boundingRect.z = std::max(boundingRect.z, point.x);
                    boundingRect.w = std::max(boundingRect.w, point.y);
                }

                if (blockReg[blocktype] == nullptr)
                    continue;

                RenderUtil::fillRectangle(boundingRect, blockReg[blocktype], 1);
            }
            break;

            case 1:
            {
                Vector3<float> blockLower = blockPosss + Vector3<float>(0.05f, 0, 0.05f);
                Vector3<float> blockHitbox = Vector3<float>(0.9f, 0.9f, 0.9f);

                UIColor* colour = blockReg[blocktype];

                if (colour == nullptr)
                    colour = new UIColor(0, 255, 0);

                ThreeUtil::DrawCube(blockLower, *colour, 1, 1, blockHitbox, OneCall);
            }
            break;
            }

            index++;
        }
    }
};