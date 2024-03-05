#pragma once

#include "Containers.h"

class ContainerScreenController { // indexes cuz im gonna make them methods that aren't virtual
public:
	void canExit()
	{
		return CallVFunc<9, void>(this);
	}

	void tryExit()
	{
		return CallVFunc<10, void>(this);
	}

	void leaveScreen()
	{
		return CallVFunc<17, void>(this);
	}

	void shiftClickItems(std::string containerName, int slots)
	{
		static void* shiftClick = findSig("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B E1 49 8B F0 44 8B FA 89 54 24 40 48 8B F9 48 8B 01 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 84 C0 0F 84 ? ? ? ? 48 8B 8F ? ? ? ? 48 85 C9 74 6B E8 ? ? ? ? 84 C0 74 62 48 8D 8F ? ? ? ? 8B 91 ? ? ? ? 39 91 ? ? ? ? 74 13 44 89 64 24 ? 4C 8B CE");
		CallFunc<void, ContainerScreenController*, uintptr_t, TextHolder, int>(
			shiftClick,
			this,
			0x7FFFFFFF,
			containerName,
			slots
		);
	}

	void closeContainer()
	{ // bruh u need all 3 (idky)
		this->leaveScreen();
		this->canExit();
		this->tryExit();
	}
};