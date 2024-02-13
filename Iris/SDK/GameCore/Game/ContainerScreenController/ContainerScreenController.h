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
		static void* shiftClick = findSig("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B E1 4D 8B F0");
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