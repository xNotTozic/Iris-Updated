#pragma once

class NoWeb : public Module
{
public:
    NoWeb(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("NoSlow", "Movement", "Disables the slowdown multiplier", keybind, enabled)
    {
    }

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer() || !Game::GetLocalPlayer()->getMovementProxy())
            return;

        Player* localPlayer = Game::GetLocalPlayer();
        DirectPlayerMovementProxy* proxy = localPlayer->getMovementProxy();

        proxy->resetBlockMovementSlowdownMultiplier();
    }
};