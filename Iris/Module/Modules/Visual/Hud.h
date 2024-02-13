#pragma once

class HudModule : public Module
{
public:

    int hotbarStyle = 0;

    HudModule(int keybind = Keyboard::NONE, bool enabled = true) :
        Module("HUD", "Visual", "Display info on the screen", keybind, enabled)
    {
    }

    void onEvent(ImGUIRenderEvent* event) override
    {
        Player* player = Game::GetLocalPlayer();

        if (!Game::GetInstance()->mcGame->canUseMoveKeys())
            return;

        if (!player)
            return;

        Vector3<int> pos = player->GetBlockPosition();

        std::ostringstream oss;
        oss.precision(2);
        oss << std::fixed << player->getHorizontalSpeed();

        drawTile(combine("FPS: ", Game::gameFps), 0);
        drawTile(combine("XYZ: ", pos.x, ", ", pos.y, ", ", pos.z), 1);
        drawTile(combine("BPS: ", player->getHorizontalSpeed() > 0 ? oss.str() : "0.0"));
    }

    void drawTile (std::string tileDescr, int index = 2)
    {
        Vector2<float> tilePos = Vector2<float>(5, (Game::Core::ClientInstance->getGuiData()->WindowResolution2.y - 25) - (index * 16.f));

        ImRenderUtil::drawText(tilePos, &tileDescr, ColorUtil::getClientColor(3, 1, 1, -index * 85), 1.2f, 1, true);

        float width = ImRenderUtil::getTextWidth(&tileDescr, 1);

        if (size.x < width)
            size.x = width;

        location = tilePos;
        size.y = (index + 1) * 10;
    }
};