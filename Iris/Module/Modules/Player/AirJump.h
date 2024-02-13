#pragma once

class AirJump : public Module
{
public:
    AirJump(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("AirJump", "Player", "Allow you to jump infinitely", keybind, enabled)
    {}

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer() || !Game::GetLocalPlayer()->getMovementProxy())
            return;

        Player* player = Game::GetLocalPlayer();
        DirectPlayerMovementProxy* proxy = player->getMovementProxy();

        proxy->setOnGround(true);
    }
};