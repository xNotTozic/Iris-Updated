#pragma once

#include "MaterialType.h"
#include "Material.h"
#include "BlockLegacy.h"

class Block
{
public:
	BlockLegacy* GetBlockLegacy()
	{
		return *reinterpret_cast<BlockLegacy**>((uintptr_t)this + 0x10);
	}

	TextHolder* GetTileName()
	{
		return GetBlockLegacy()->GetTileName();
	}

	Material* GetMaterial()
	{
		return GetBlockLegacy()->GetMaterial();
	}

	MaterialType GetMaterialType()
	{
		return GetBlockLegacy()->GetMaterial()->type;
	}

	bool isSlab()
	{
		std::string str = GetTileName()->getText();

		//slab
		if (ends_with(str, "slab") || ends_with(str, "slab2"))
			return true;

		return false;
	}
};
