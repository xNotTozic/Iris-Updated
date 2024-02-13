#pragma once

class TrueJesus : public Module
{
public:
    TrueJesus(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("TrueJesus", "Player", "Makes water blocks act like a semi-solid", keybind, enabled)
    {}

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer() || !Game::GetInstance()->getBlockSource() || !Game::GetLocalPlayer()->getMovementProxy())
            return;

        Player* player = Game::GetLocalPlayer();
        StateVectorComponent* stateVec = player->try_get<StateVectorComponent>();
        AABBShapeComponent* shape = player->try_get<AABBShapeComponent>();
        BlockSource* source = Game::GetInstance()->getBlockSource();
        DirectPlayerMovementProxy* proxy = player->getMovementProxy();

        if (!stateVec || !shape)
            return;

        Vector3<int> playerPos = player->GetBlockPosition();
        playerPos.y -= 1;

        Block* block = source->getBlock(playerPos);

        if (block->GetMaterialType() == MaterialType::Water || block->GetMaterialType() == MaterialType::Lava)
        {
            float threshold = playerPos.y - shape->r_Pos_Lower.y;

            if (stateVec->r_Velocity.y <= 0 && threshold >= -1.3f)
            {
                stateVec->r_Velocity.y = 0; // cuz meant to be a solid
                shape->r_Pos_Lower.y = playerPos.y + 1;
                shape->r_Pos_Upper = shape->r_Pos_Lower + shape->r_Hitbox;
                proxy->setOnGround(true);
            }
        }
    }
};