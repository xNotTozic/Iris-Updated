#pragma once

class MoveUtil 
{
public:

    static bool isMoving() {
        auto player = Game::GetLocalPlayer();
        if (!player)
            return false;

        StateVectorComponent* velocity = player->try_get<StateVectorComponent>();
        if (!velocity && !player->try_get<StateVectorComponent>())
            return false;

        return velocity->r_Velocity.magnitudexz() >= 0.045f;
    }

    static void setSpeed(float speed) {
        auto player = Game::GetLocalPlayer();
        if (!player)
            return;

        auto velocity = player->try_get<StateVectorComponent>();
        if (!velocity) {
            return;
        }

        float calcYaw = (player->getMovementProxy()->getRotation().y + 90) * (PI / 180);
        float c = cos(calcYaw);
        float s = sin(calcYaw);

        Vector2<float> moveVec = player->getMoveVec().normalize();
        moveVec = { moveVec.x * c - moveVec.y * s, moveVec.x * s + moveVec.y * c };

        Vector3<float> movement;
        movement.x = moveVec.x * speed;
        movement.y = velocity->r_Velocity.y;
        movement.z = moveVec.y * speed;

        player->lerpMotion(movement);
    }

};
