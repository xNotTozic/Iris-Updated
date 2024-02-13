#pragma once

class WorldBorder : public Module
{
public:
    WorldBorder(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("WorldBorder", "Visual", "Draws a custom outline when you get near the world border", keybind, enabled)
    {
        addEnum("Mode", "World Border defined by type", { "Lifeboat" }, &mode);
    }

    int mode = 0;

    void onEvent(BeforeUpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer())
            return;

        Player* player = Game::GetLocalPlayer();
        ClientInstance* instance = Game::GetInstance();
        LevelRender* render = instance->getLevelRender();

        Vector3<float> playerPos = render->getOrigin();

        if (playerPos.empty())
            return;

        int Max  = 1100, Min  = 50,
            RMax = 1110, RMin = 40;

        int borderDistanceX = std::min(abs(playerPos.x - Min), abs(playerPos.x - Max)),
            rBorderDistanceX = std::min(abs(playerPos.x - RMin), abs(playerPos.x - RMax));

        int borderDistanceZ = std::min(abs(playerPos.z - Min), abs(playerPos.z - Max)),
            rBorderDistanceZ = std::min(abs(playerPos.z - RMin), abs(playerPos.z - RMax));

        Vector2<float> cubeWall2dDim(16, 16);
        Vector2<float> cube2dDims(1, 1);
        Vector3<float> cubePosition(playerPos);

        int minDisX = playerPos.x - Min,
            maxDisX = playerPos.x - Max,
            minDisZ = playerPos.z - Min,
            maxDisZ = playerPos.z - Max,
            rminDisX = playerPos.x - RMin,
            rmaxDisX = playerPos.x - RMax,
            rminDisZ = playerPos.z - RMin,
            rmaxDisZ = playerPos.z - RMax;

        if (rBorderDistanceX <= 16)
        {
            cubePosition.x = rminDisX <= 16 ? RMin : RMax;
            for (int z = -(cubeWall2dDim.x / 2); z < cubeWall2dDim.x / 2; ++z)
            {
                for (int y = -(cubeWall2dDim.y / 2); y < cubeWall2dDim.y / 2; ++y)
                    ThreeUtil::DrawMeshFace(cubePosition + Vector3<float>(0, y, z), UIColor(255, 0, 0, 255 / 3), 2, cube2dDims);
            }
        }

        cubePosition = playerPos;

        if (rBorderDistanceZ <= 16)
        {
            cubePosition.z = rminDisZ <= 16 ? RMin : RMax;
            for (int x = -(cubeWall2dDim.x / 2); x < cubeWall2dDim.x / 2; ++x)
            {
                for (int y = -(cubeWall2dDim.y / 2); y < cubeWall2dDim.y / 2; ++y)
                    ThreeUtil::DrawMeshFace(cubePosition + Vector3<float>(x, y, 0), UIColor(255, 0, 0, 255 / 3), 2, cube2dDims, IrisRenderFace::Right);
            }
        }

        cubePosition = playerPos;

        if (borderDistanceX <= 16)
        {
            cubePosition.x = minDisX <= 16 ? Min : Max;
            for (int z = -(cubeWall2dDim.x / 2); z < cubeWall2dDim.x / 2; ++z)
            {
                for (int y = -(cubeWall2dDim.y / 2); y < cubeWall2dDim.y / 2; ++y)
                    ThreeUtil::DrawMeshFace(cubePosition + Vector3<float>(0, y, z), UIColor(255, 165, 0, 255 / 8), 2, cube2dDims);
            }
        }

        cubePosition = playerPos;

        if (borderDistanceZ <= 16)
        {
            cubePosition.z = minDisZ <= 16 ? Min : Max;
            for (int x = -(cubeWall2dDim.x / 2); x < cubeWall2dDim.x / 2; ++x)
            {
                for (int y = -(cubeWall2dDim.y / 2); y < cubeWall2dDim.y / 2; ++y)
                    ThreeUtil::DrawMeshFace(cubePosition + Vector3<float>(x, y, 0), UIColor(255, 165, 0, 255 / 8), 2, cube2dDims, IrisRenderFace::Right);
            }
        }
    }
};
