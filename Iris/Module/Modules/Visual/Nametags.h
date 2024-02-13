#pragma once

class Nametags : public Module
{
public:
    Nametags(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Nametags", "Visual", "Draws peoples nametags above their heads", keybind, enabled)
    {}

    void findEntity(Player* entity)
    {
        if (!entity || entity->isLocalPlayer() || entity == Game::GetLocalPlayer() || !Game::GetInstance()->mcGame->canUseMoveKeys())
            return;

        Player* localPlayer = Game::GetLocalPlayer();

        if (entity->isBot() || !localPlayer)
            return;

        Vector3<float> renderPos = entity->getRenderPositionComponent()->renderPos - Vector3 <float>(0, -0.7f, 0);
        float distance = renderPos.distance(Game::GetInstance()->getLevelRender()->getOrigin());

        if (distance > 200)
            return;

        Vector2<float> output1;
        if (!Game::GetInstance()->WorldToScreen(renderPos, output1))
            return;

        if (!entity->getNameTag())
            return;

        std::string user(entity->getNameTag()->getText());
        user = Util::sanitizeName(user);

        float textWidth = ImRenderUtil::getTextWidth(&user, 1);

        ImRenderUtil::drawText(output1 - Vector2<float>(textWidth / 2, 0), &user, UIColor(255, 255, 255), 1, 1, true);
    }


    void onEvent(ImGUIRenderEvent* event) override
    {
        auto callback = [this](Player* act) { findEntity(act); };
        getEntities(callback);
    }
};