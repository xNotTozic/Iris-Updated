#pragma once

#include "SoundType.h"

class LevelSoundEventPacket : public Packet
{
public:
	LevelSoundEventPacket() { init(); };
	LevelSoundEventPacket(Vector3<float> position, SoundType soundType)
	{
		init();
		this->Position = position;
		this->SoundType = soundType;
		this->ExtraData = 0;
		//TextHolder str("minecraft:player");
		this->EntityType = nullptr;
		this->BabyMob = false;
		this->DisableRelativeVolume = false;

	}

	SoundType SoundType;
	Vector3<float> Position;
	__int64 ExtraData;
	TextHolder* EntityType;
	bool BabyMob;
	bool DisableRelativeVolume;

	void init()
	{
		static void* sig = nullptr;
		if (!sig) sig = findSig("48 8D 05 ? ? ? ? 48 89 45 D0 44 89 6D 00");
		this->setVTable<LevelSoundEventPacket>(reinterpret_cast<uintptr_t*>(sig));
	}
};