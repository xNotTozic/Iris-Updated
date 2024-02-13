#pragma once

class Scaffold : public Module
{
public:
    float distance = 5;

    float targetY = 0.f;
    int prevSlot = -1;
    Vector2<float> angle = {};
    bool hasTowered = false;
    Vector3<float> targetBlock = {};
    int towerMode = 0;
    int selectMode = 0;

    bool yLock = false;

    Scaffold(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Scaffold", "World", "Basic version of scaffold", keybind, enabled)
    {
        ingameOnly = true;

        addEnum("Switch", "How you will switch to blocks", { "First " }, &selectMode);
        addBool("Keep Y", "Kepps your y level when placing blocks", &yLock);
        addEnum("Tower", "The tower mode", { "None", "Motion" }, &towerMode);
    }

    bool canPlace(Vector3<float> pos) {
        return Game::GetInstance()->getBlockSource()->getBlock(pos.floor().ToInt())->GetMaterialType() == MaterialType::Air;
    }

    bool isUseful(ItemStack* itemStack) {
        std::vector<std::string> uselessSubstrings = { "_coral", "_button", "chest", "boom", "vine", "pressure_plate", "fence", "_wall", "_stairs", "_table", "furnace", "trapdoor", "command_block", "torch", "carpet", "flower" };
        std::vector<std::string> uselessNames = { "cake", "ladder", "tnt", "lever", "loom", "scaffolding", "web", "sand", "gravel", "dragon_egg", "anvil", "bamboo" };

        std::string itemName = itemStack->item->name;

        for (auto substring : uselessSubstrings) {
            if (itemName.find(substring) != std::string::npos) {
                return false;
            }
        }

        for (auto name : uselessNames) {
            if (itemName == name) {
                return false;
            }
        }

        return true;
    }

    bool findBlock() {
        auto supplies = Game::GetLocalPlayer()->getSupplies();
        auto inv = supplies->inventory;
        auto prevSlot = supplies->hotbarSlot;

        for (int n = 0; n < 9; n++) {
            ItemStack* stack = inv->getItem(n);
            Item* it = stack->item;
            if (stack->item) {
                if (prevSlot != n) {
                    if (selectMode == 1) {
                        MobEquipmentPacket pkt(Game::GetLocalPlayer()->getRuntimeIDComponent()->runtimeID, n, n);
                        Game::GetInstance()->getPacketSender()->sendToServer(&pkt);
                    };
                    supplies->hotbarSlot = n;
                };
                return true;
            };
        }; 

        return false;
    }

    bool buildBlock(Vector3<float> pos, GameMode* gm) {
        static std::vector<Vector3<float>> neighbours = {
            Vector3<float>(0, -1, 0), Vector3<float>(0, 1, 0),
            Vector3<float>(0, 0, -1), Vector3<float>(0, 0, 1),
            Vector3<float>(-1, 0, 0), Vector3<float>(1, 0, 0),
        };

        for (int face = 0; face < neighbours.size(); face++) {
            Vector3<float> offset = Vector3<float>(pos.floor()).submissive(neighbours[face]);
            if (!canPlace(offset.ToFloat()) && findBlock()) {
                gm->buildBlock(offset.ToInt(), face, false);

                if (selectMode == 1) {
                    Game::GetLocalPlayer()->getSupplies()->hotbarSlot = prevSlot;

                }

                return true;
            }
        }
        return false;
    }

    bool predictBlock(Vector3<float> pos, GameMode* gm) {
        static std::vector<Vector3<float>> blocks;
        if (blocks.empty()) {
            for (int y = -distance; y <= 0; y++) {
                for (int x = -distance; x <= distance; x++) {
                    for (int z = -distance; z <= distance; z++) {
                        blocks.push_back(Vector3<float>(x, y, z));
                    }
                }
            }
            std::sort(blocks.begin(), blocks.end(), [](Vector3<float> start, Vector3<float> end) {
                return sqrtf((start.x * start.x) + (start.y * start.y) + (start.z * start.z)) < sqrtf((end.x * end.x) + (end.y * end.y) + (end.z * end.z));
                });
        }

        for (const Vector3<float>& offset : blocks) {
            Vector3<float> currentBlock = Vector3<float>(pos.floor()).add(offset);
            if (buildBlock(currentBlock, gm)) {
                return true;
            }
        }
        return false;
    }

    void onEvent(UpdateTickEvent* event) override
    {
        auto player = Game::GetLocalPlayer();
        auto gm = player->getGameMode();
        auto stateVec = player->try_get<StateVectorComponent>();

        if (!player || !gm || !stateVec) {
            return;
        }

        Vector3<float> velocity = stateVec->r_Velocity.Normalize();

        // Set our yLevel
        if (player->getMovementProxy()->isOnGround() || player->GetPosition().y < targetY + 0.5f || !MoveUtil::isMoving() && GetAsyncKeyState(VK_SPACE) || (!yLock && player->GetPosition().y > targetY))
            targetY = player->GetPosition().floor().y - 0.5f;

        // Handle tower modes
        switch (towerMode) {
        case 0:
            break;
        case 1:
            if (!MoveUtil::isMoving() && GetAsyncKeyState(VK_SPACE) && velocity.y > -0.2) {
                stateVec->r_Velocity.y = .85f;
                hasTowered = true;
            }
            else {
                if (!player->getMovementProxy()->isOnGround() && hasTowered) {
                    stateVec->r_Velocity.y = -5.f;
                    hasTowered = false;
                }
            }
            break;
        }

        targetBlock = player->GetPosition();
        targetBlock.y = targetY;

        targetBlock.x += velocity.x;
        targetBlock.z += velocity.z;

        if (canPlace(targetBlock)) {
            predictBlock(targetBlock, gm);
        }
    }

    void onEvent(PacketSendingEvent* event) override
    {
        auto packet = event->Packet;
        if (packet && packet->instanceOf<PlayerAuthInputPacket>()) {
            PlayerAuthInputPacket* pkt = (PlayerAuthInputPacket*)packet;
            if (pkt) {
                pkt->pitch = 90.f;
            }
        }
    }

    void onEnabled() override {
        Player* player = Game::GetLocalPlayer();
        if (!player) {
            return;
        }
        hasTowered = false;
        prevSlot = player->getSupplies()->hotbarSlot;
    }

    void onDisabled() override {

        auto player = Game::GetLocalPlayer();
        auto stateVec = player->try_get<StateVectorComponent>();

        if (!player || !stateVec) {
            return;
        }

        if (hasTowered) {
            stateVec->r_Velocity.y = -5.f;
        }
        player->getSupplies()->hotbarSlot = prevSlot;
    }
};