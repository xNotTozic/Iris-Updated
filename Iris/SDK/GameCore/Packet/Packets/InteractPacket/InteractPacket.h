#pragma once

#include "Action.h"

class InteractPacket : public Packet
{
public:
	InteractPacket() { init(); };

	Action action;
	uint64_t actorRuntimeId;
	Vector3<float> pos;

    void init()
    {
        static void* sig = nullptr;
        if (!sig) sig = findSig("48 8D 05 ? ? ? ? 48 89 45 D7 C6 45 07 06 48 89 4D 0F F2 0F 10 05 ? ? ? ? F2 0F 11 45 ? 8B 05 ? ? ? ? 89 45 1F F3 0F 10 35 ? ? ? ? 0F 2F 35 ? ? ? ? 0F 82 ? ? ? ? 0F 2F 35 ? ? ? ? 0F 87 ? ? ? ? F3 0F 10 05 ? ? ? ? E8 ? ? ? ? 84 C0 74 21 F3 0F 10 05 ? ? ? ? E8 ? ? ? ? 84 C0 74 10 0F 28 C6 E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? 48 8D 55 8F ");
        this->setVTable<InteractPacket>(reinterpret_cast<uintptr_t*>(sig));
    }
};