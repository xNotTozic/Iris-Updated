#pragma once

class Phase : public Module
{
public:
    Phase(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Phase", "Player", "Allow phasing through blocks", keybind, enabled)
    {
        addBool("Noclip", "Go through all blocks UP & DOWN", &noclip);
    }

    bool noclip = false;

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer())
            return;

        Player* player = Game::GetLocalPlayer();
        AABBShapeComponent* aabb = player->try_get<AABBShapeComponent>();

        if (noclip)
        {
            aabb->r_Pos_Upper.y = aabb->r_Pos_Lower.y - 3;
        }
        else
        {
            aabb->r_Pos_Upper.y = aabb->r_Pos_Lower.y;
        }
    }

    void onDisabled() override
    {
        if (!Game::GetLocalPlayer())
            return;

        Player* player = Game::GetLocalPlayer();
        AABBShapeComponent* aabb = player->try_get<AABBShapeComponent>();

        player->SetPos(aabb->r_Pos_Lower);
    }
};