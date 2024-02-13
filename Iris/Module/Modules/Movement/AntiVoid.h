#pragma once

class AntiVoid : public Module
{
public:
    AntiVoid(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("AntiVoid", "World", "Automatically avoids falling into the void or off cliffs", keybind, enabled)
    {
        addSlider("Distance", "Distance to fall before teleporting", &distance, 1, 6);
    }

    float distance = 3;

    void onEvent(UpdateTickEvent* event) override
    {
        if (!Game::GetLocalPlayer() || !Game::GetInstance()->getBlockSource() || !Game::GetLocalPlayer()->getMovementProxy())
            return;

        Player* player = Game::GetLocalPlayer();
        DirectPlayerMovementProxy* proxy = player->getMovementProxy();
        BlockSource* src = Game::GetInstance()->getBlockSource();

        static Vector3<float> savePos = player->GetPosition();
        Vector3<float> blockBelow = player->GetPosition();

        // Save the last onGround pos
        if (player->isOnGround() && player->GetStandingBlock()->GetMaterialType() != MaterialType::Air)
        {
            savePos = blockBelow;
        }

        bool blockBelowAir = false;
        for (int y = blockBelow.y; y >= -65; --y) 
        {
            if (src->getBlock(Vector3<int>(blockBelow.x, y, blockBelow.z))->GetMaterialType() == MaterialType::Air)
            {
                blockBelowAir = true;
            }
            else 
            {
                blockBelowAir = false;
                break;
            }
        }

        if (proxy->getFallDistance() >= distance && blockBelowAir)
        {
            player->TeleportTo(savePos);
        }
    }
};