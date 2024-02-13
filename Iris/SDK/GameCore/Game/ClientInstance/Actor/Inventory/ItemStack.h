#pragma once

class ItemStack
{
public:
	Item* getItem()
	{
		return *(Item**)((uintptr_t)(this) + 0x8);
	}
	bool isBlockType()
	{
		return *(uintptr_t**)((uintptr_t)(this) + 0x18) != nullptr;
	}

	Item* item;
	bool isBlock;
	uint8_t count;
};