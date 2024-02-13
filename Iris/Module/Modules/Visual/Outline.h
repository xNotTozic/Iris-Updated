#pragma once

class Outline : public Module
{
public:
    float thickness = 1;
    float lerpSpeed = 8;

    Outline(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Outline", "Visual", "Draws a custom outline around blocks", keybind, enabled)
    {
        addSlider("Thickness", "The thickness of each pixel", &thickness, 1, 10);
        //addSlider("EasingSpeed", "The speed at which it animates", &lerpSpeed, 5, 50);
    }

    void onEvent(BeforeUpdateEvent* event) override
    {
        if (!Game::GetInstance()->mcGame->canUseMoveKeys())
            return;

        Player* player = Game::GetLocalPlayer();
        if (!player)
            return;

        Level* level = player->GetLevel();
        if (!level)
            return;

        Vector3<float> blockPos = level->IBlockPos.ToFloat();

        if (blockPos.x == 0 && blockPos.y == 0 && blockPos.z == 0)
            return;

        BlockSource* source = event->Context->ClientInstance->getBlockSource();

        if (!source)
            return;

        Block* block = source->getBlock(blockPos.ToInt());

        MaterialType type = block->GetMaterialType();

        UIColor clientColour = ColorUtil::getClientColor(5, 1, 1, 1);

        switch (type)
        {
        case MaterialType::Carpet:
            ThreeUtil::DrawCube(blockPos, clientColour, thickness, lerpSpeed, { 1, 0.05f, 1 });
            return;
        case MaterialType::Bed:
            ThreeUtil::DrawCube(blockPos, clientColour, thickness, lerpSpeed, { 1, 0.55f, 1 });
            return;
        case MaterialType::Cake:
            ThreeUtil::DrawCube(blockPos + Vector3<float>(0.05f, 0.f, 0.05f), clientColour, thickness, lerpSpeed, { 0.9f, 0.5f, 0.9f });
            return;
        }

        if (block->isSlab())
        {
            ThreeUtil::DrawCube(blockPos, clientColour, thickness, lerpSpeed, { 1, 0.5f, 1 });
            return;
        }

        std::string str = block->GetTileName()->getText();

        if (ends_with(str, "standing_sign"))
        {
            ThreeUtil::DrawCube(blockPos + Vector3<float>(0.25f, 0, 0.25f), clientColour, thickness, lerpSpeed, {0.5f, 1.f, 0.5f});
            return;
        }

        ThreeUtil::DrawCube(blockPos, clientColour, thickness, lerpSpeed);
    }
};
