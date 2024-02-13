#pragma once

class BlockLegacy
{
public:
	TextHolder* GetTileName()
	{
		return reinterpret_cast<TextHolder*>((uintptr_t)this + 0x8);
	}

	Material* GetMaterial()
	{
		return *reinterpret_cast<Material**>((uintptr_t)this + 0x108);
	}

	MaterialType GetMaterialType()
	{
		return GetMaterial()->type;
	}
};