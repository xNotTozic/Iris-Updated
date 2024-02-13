#pragma once

class Tpaura : public Module
{
public:
    Tpaura(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("InfiniteAura", "Combat", "Serversidedly teleport to people and attack them", keybind, enabled)
    {
        addEnum("Mode", "The Mode", { "PocketMine", "MovePlayer"}, &mode);
        addEnum("Target", "How many entities will be targeted", { "Single", "Multi"}, &targetMode);
        addSlider("Range", "How far it will search for entities", &range, 0, 200);
        addSlider("Steps", "How many steps it will take to get to an entity", &teleportIncrement, 0.1f, 20);
        addBool("Raycast", "Only attack entities you can see", &raytrace);
        addSlider("APS", "How fast you will attack", &delayMS, 0, 20);

        ingameOnly = true;
    }
    
    int mode = 0;
    int targetMode = 0;
    float range = 30;
    float delayMS = 4;
    float teleportIncrement = 4;

    bool raytrace = false;

    void onEvent(UpdateTickEvent* event) {

        Game::TargetLists::infAuraList.clear();
        Player* player = Game::GetLocalPlayer();
        if (!player) {
            return;
        }

        DirectPlayerMovementProxy* mProxy = player->getMovementProxy();
        if (!mProxy) {
            return;
        }

        GameMode* gm = player->getGameMode();
        if (!gm) {
            return;
        }

        auto callback = [this](Player* act) { findEntity(act); };
        getEntities(callback);

        if (!Game::TargetLists::infAuraList.empty()) {
            Game::Iris::ShouldBlock = true;
            if (TimeUtil::hasTimeElapsed("tpDelay", 1000 / delayMS, true)) {
                float calculatedYaw = (mProxy->getRotation().y + 90) * (PI / 180);
                float calculatedPitch = (mProxy->getRotation().x) * -(PI / 180);

                Vector3<float> moveVec;
                moveVec.x = cos(calculatedYaw) * cos(calculatedPitch) * 0.5f;
                moveVec.y = sin(calculatedPitch) * 0.5f;
                moveVec.z = sin(calculatedYaw) * cos(calculatedPitch) * 0.5f;

                Vector3<float> playerPos = player->getPosition().add(moveVec);
                Vector3<float> entityPosition;

                switch (targetMode) {
                case 0: // Single
                    entityPosition = Game::TargetLists::infAuraList[0]->getPosition();
                    PathToTeleport(playerPos, entityPosition, teleportIncrement);
                    gm->attack(Game::TargetLists::infAuraList[0]);
                    PathToTeleport(entityPosition, playerPos, teleportIncrement);
                    break;
                case 1:// Multi
                    for (int i = 0; i < Game::TargetLists::infAuraList.size(); i++) {
                        entityPosition = Game::TargetLists::infAuraList[i]->getPosition();
                        PathToTeleport(playerPos, entityPosition, teleportIncrement);
                        gm->attack(Game::TargetLists::infAuraList[i]);
                        PathToTeleport(entityPosition, playerPos, teleportIncrement);
                    }
                    break;
                }
                player->swing();
            }
        }
        else {
            Game::Iris::ShouldBlock = false;
        }
    }
    
    void onDisabled() override {
        Game::TargetLists::infAuraList.clear();
        Game::Iris::ShouldBlock = false;
    }

    struct sortEntities {
        bool operator()(Player* lhs, Player* rhs) {
            return (lhs->GetPosition().distance(Game::GetLocalPlayer()->GetPosition()) < (rhs->GetPosition().distance(Game::GetLocalPlayer()->GetPosition())));
        }
    };

    void findEntity(Player* act) {
        if (!act) return;
        if (act == Game::GetLocalPlayer()) return;
        if (act->IsBadPtr()) return;
        if (raytrace && !Game::GetLocalPlayer()->canSee(*act)) return;
        if (getModuleByName("AntiBot")->isEnabled() && act->isBot()) return;

        float distance = act->GetPosition().distance(Game::GetLocalPlayer()->GetPosition());
        if (distance <= range) {
            Game::TargetLists::infAuraList.push_back(act);
            std::sort(Game::TargetLists::infAuraList.begin(), Game::TargetLists::infAuraList.end(), sortEntities());
        }
    }

    void PathToTeleport(Vector3<float> startPos, Vector3<float> endPos, float offset) {
        Player* player = Game::GetLocalPlayer();
        DirectPlayerMovementProxy* mProxy = player->getMovementProxy();
        ClientInstance* instance = Game::GetInstance();
        LoopbackPacketSender* sender = instance->getPacketSender();

        if (!sender or !instance) {
            return;
        }

        float steps = ceil(getDistance(startPos.x, startPos.y, startPos.z, endPos.x, endPos.y, endPos.z) / offset);
        float dX = endPos.x - startPos.x;
        float dY = endPos.y - startPos.y;
        float dZ = endPos.z - startPos.z;
        for (float d = 1; d <= steps; ++d) {
            Vector3<float> origPos = Vector3<float>((startPos.x + (dX * d) / steps), (startPos.y + (dY * d) / steps), (startPos.z + (dZ * d) / steps));

            switch (mode) {
            case 0: {
                PlayerAuthInputPacket pkt;
                pkt.pos = Vector3<float>(origPos.x, origPos.y, origPos.z).add(1.f);
                pkt.yaw = mProxy->getRotation().y;
                pkt.yawUnused = mProxy->getRotation().y;
                pkt.pitch = mProxy->getRotation().x;
                pkt.posDelta = mProxy->getLocalMoveVelocity();
                sender->sendToServer(&pkt);
                break;
            }
            case 1: {
                MovePlayerPacket pkt;
                pkt.position = Vector3<float>(origPos.x, origPos.y, origPos.z).add(1.f);
                pkt.yaw = mProxy->getRotation().y;
                pkt.headYaw = mProxy->getRotation().y;
                pkt.pitch = mProxy->getRotation().x;
                sender->sendToServer(&pkt);
                break;
            }
            }
        }
    }

    float getDistance(float x1, float y1, float z1, float x2, float y2, float z2) {
        float xDiff = x1 - x2;
        float yDiff = y1 - y2;
        float zDiff = z1 - z2;
        return sqrt(xDiff * xDiff + yDiff * yDiff + zDiff * zDiff);
    }
};