#pragma once

class InstaBreak : public Module
{
public:
    InstaBreak(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("InstaBreak", "Misc", "Instantly breaks the block you right click (for now)", keybind, enabled)
    {}

    void onEvent(MouseEvent* event) override
    {
        if (!Game::GetLocalPlayer() || !Game::GetLocalPlayer()->GetLevel())
            return;

        Player* player = Game::GetLocalPlayer();
        Level* level = player->GetLevel();
        GameMode* gamemode = player->getGameMode();

        if ((__int8)*event->Key == 1 && event->Held)
        {
            Vector3<int> target = level->IBlockPos;
            int targetFace = level->BlockFace;

            gamemode->destroyBlock(target, targetFace, true);
        }
    }
};