#pragma once

class MinecraftGame
{
public:
	bool canUseMoveKeys()
	{
		static unsigned int offset = 0x108; // offset sig here
		return *reinterpret_cast<bool*>((uintptr_t)this + offset);
	}
};