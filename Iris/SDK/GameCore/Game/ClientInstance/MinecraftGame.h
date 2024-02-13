#pragma once

class MinecraftGame
{
public:
	bool canUseMoveKeys()
	{
		static unsigned int offset = 0x190; // offset sig here // Updated to 1.20.51
		//static unsigned int offset = 0x108; // 1.20.0.1
		return *reinterpret_cast<bool*>((uintptr_t)this + offset);
	}
};