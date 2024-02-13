#pragma once

#include "MovePacketMode.h"
#include "MovePacketCause.h"

class MovePlayerPacket : public Packet
{
public:
    MovePlayerPacket() {
        init();
    }

    MovePlayerPacket(Player* actor, Vector3<float> position, Vector2<float> rot, bool onGround)
    {
        init();
        this->runtimeId = lastRunId; // actor.try_get<RuntimeIDComponent>()->runtimeId
        this->position = position;
        this->pitch = rot.y;
        this->yaw = rot.x;
        this->headYaw = rot.x;
        this->mode = MovePacketMode::MOVE_PACKET_MODE_NORMAL;
        this->onGround = onGround;
        this->ridingRuntimeId = 0;
        this->teleportCause = MovePacketCause::MOVE_PACKET_CAUSE_UNKNOWN;
        this->teleportItem = 0;
        this->tick = 0;
    }

    uint64_t runtimeId;
    Vector3<float> position;
    float pitch;
    float yaw;
    float headYaw;
    MovePacketMode mode;
    bool onGround;
    uint64_t ridingRuntimeId;
    MovePacketCause teleportCause;
    __int32 teleportItem;
    __int32 tick;

    void init()
    {
        static void* sig = nullptr;
        if (!sig) sig = findSig("48 8D 05 ? ? ? ? 48 89 43 08 48 8B"); // Updated to 1.20.51
        // 48 8D 05 ? ? ? ? 48 89 43 08 48 8B 46 30 48 89 43 38 F2 0F 10 46 ? F2 0F 11 43 ? 8B 46 40 89 43 48 F2 0F 10 46 ? F2 0F 11 43 ? 8B 46 4C 
        // 48 8D 05 ? ? ? ? 48 89 42 08 48 8B 47 30 in 1.20.0.1
        this->setVTable<MovePlayerPacket>(reinterpret_cast<uintptr_t*>(sig));
    }
};