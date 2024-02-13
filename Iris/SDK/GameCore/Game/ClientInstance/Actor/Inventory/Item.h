#pragma once

class Item
{
public:
	std::string getNameId()
	{
		return *(std::string*)((uintptr_t)(this) + 0x110);
	}

	uint16_t maxStackSize;
	std::string name;
};