#pragma once

#pragma once
#include <bitset>

class Packet
{
public:
	uintptr_t** VTable;
private:
	char pad[0x24];
public:
	template<typename P>
	void setVTable(void* sig)
	{
		if (!sig)
			return;

		int offset = *(int*)((uintptr_t)sig + 3);
		this->VTable = (uintptr_t**)((uintptr_t)sig + offset + 7);
	}

	template <class T>
	bool instanceOf()
	{
		T packet;
		return (packet.VTable == this->VTable);
	}

	int getId()
	{
		return CallVFunc<1, int>(this);
	}

	std::string getName(void)
	{
		return CallVFunc<2, TextHolder*>(this)->getText();
	}

};

#include "Packets/LevelSoundEventPacket/LevelSoundEventPacket.h"
#include "Packets/PlayerAuthInputPacket/PlayerAuthInputPacket.h"
#include "Packets/InteractPacket/InteractPacket.h"
#include "Packets/CommandRequestPacket/CommandRequestPacket.h"
#include "Packets/MobEquipmentPacket/MobEquipmentPacket.h"
