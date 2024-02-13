#pragma once

#include "G_UUID.h"
#include "CommandOrigin.h"

class CommandRequestPacket : public Packet
{
public:
    enum class Origin 
    {
        PLAYER = 0,
        COMMAND_BLOCK = 1,
        MINECART_COMMAND_BLOCK = 2,
        DEV_CONSOLE = 3,
        AUTOMATION_PLAYER = 4,
        CLIENT_AUTOMATION = 5,
        DEDICATED_SERVER = 6,
        ENTITY = 7,
        VIRTUAL = 8,
        GAME_ARGUMENT = 9,
        INTERNAL = 10
    };

    CommandRequestPacket() { init(); };
    CommandRequestPacket(std::string command, Origin origin = Origin::PLAYER, bool isExternal = 0) 
    {
        init();
        this->command = command;
        this->origin = origin;
        this->isExternal = isExternal;
    }

    TextHolder command;
	Origin origin = Origin::PLAYER;
	bool isExternal = 0;
	char pad[0x256];

    void init()
    {
        static void* sig = nullptr;
        if (!sig) sig = findSig("48 8D 05 ? ? ? ? 48 8B F9 48 89 01 8B DA 48 83 C1 68 E8 ? ? ? ? 48 8D 4F 30 E8 ? ? ? ? 48 8D 05 ? ? ? ?");
        this->setVTable<CommandRequestPacket>(reinterpret_cast<uintptr_t*>(sig));
    }
};