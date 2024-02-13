#pragma once

class ClickTP : public Module
{
public:
    ClickTP(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("ClickTP", "Misc", "Teleports to the block you right click", keybind, enabled)
    {}

    void onEvent(MouseEvent* event) override
    {
        if (!Game::GetLocalPlayer() || Game::GetLocalPlayer()->GetLevel())
            return;

        Player* player = Game::GetLocalPlayer();
        Level* level = player->GetLevel();

        if (*event->Held && *event->Key == 2)
        {
            Vector3<float> lerpPos = level->AbsoluteHitPos;

            player->teleportTo(lerpPos, true, 0, 0, true);
        }
    }
};
