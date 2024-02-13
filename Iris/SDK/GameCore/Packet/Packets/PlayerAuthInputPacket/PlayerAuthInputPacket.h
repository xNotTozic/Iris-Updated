#pragma once

#include "InputFlag.h"
#include "PlayerBlockAction.h"

class PlayerAuthInputPacket : public Packet
{
public:
	PlayerAuthInputPacket() { init(); };
	PlayerAuthInputPacket(Vector3<float> pos, float pitch, float yaw, float bodyyaw)
	{
		init();
		this->pitch = pitch;
		this->yawUnused = yaw;
		this->pos = pos;
		this->yaw = bodyyaw;
		this->posDelta = { 0, 0, 0 };
		this->moveVector = { 0, 0 };
		this->lookDirectionVR = { 0, 0, 0 };
		this->flags = std::bitset<(size_t)InputFlag::Emoting>();
	}

	float pitch;
	float yaw;
	Vector3<float> pos;
	float yawUnused;
	Vector3<float> posDelta;
	Vector2<float> moveVector2;
	Vector2<float> moveVector;
	Vector3<float> lookDirectionVR;
	std::bitset<(size_t)InputFlag::Emoting> flags;

	inline bool hasFlag(InputFlag flag) const
	{
		return this->flags.test(static_cast<size_t>(flag));
	}
	inline void setFlag(InputFlag flag, bool toggle = true)
	{
		this->flags.set(static_cast<size_t>(flag), toggle);
	}

	void init()
	{
		static void* sig = nullptr;
		if (!sig) sig = findSig("48 8D 0D ? ? ? ? 0F 57 C0 0F 11 00 C7 40 ? ? ? ? ? C7 40 ? ? ? ? ? 48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 28 48 89 4A 10");
		this->setVTable<PlayerAuthInputPacket>(reinterpret_cast<uintptr_t*>(sig));
	}
};