#pragma once

std::map<std::string, UIColor*> blockReg = // dont want single colour for single categoiry cuz thats gay so we write our own
{
	// Liquids
	{ "tile.lava", new UIColor(0xCF, 0x10, 0x20) },
	{ "tile.water", new UIColor(0xD4, 0xF1, 0xF9) },

	// Containers
	{ "tile.chest", new UIColor(0x56, 0x43, 0x35) },
	{ "tile.barrel", new UIColor(0x56, 0x43, 0x35) },
	{ "tile.trapped_chest", new UIColor(0x56, 0x43, 0x35) },
	{ "tile.ender_chest", new UIColor(0x56, 0x43, 0x35) },
	{ "tile.shulker_box", new UIColor(0x85, 0xA, 0x7B) },
	{ "tile.undyed_shulker_box", new UIColor(0x85, 0xA, 0x7B) },

	// Iron Blocks
	{ "tile.iron_ore", new UIColor(0x84, 0x7D, 0x73) },
	{ "tile.raw_iron_block", new UIColor(0x84, 0x7D, 0x73) },
	{ "tile.deepslate_iron_ore", new UIColor(0x84, 0x7D, 0x73) },
	{ "tile.iron_block", new UIColor(0xA1, 0x9D, 0x94) },
	
	// Diamond Blocks
	{ "tile.deepslate_diamond_ore", new UIColor(0x70, 0xD1, 0xF4) },
	{ "tile.diamond_ore", new UIColor(0x70, 0xD1, 0xF4) },
	{ "tile.diamond_block", new UIColor(0x70, 0xD1, 0xF4) },

	// Portals
	{ "tile.portal", new UIColor(0x41, 0x11, 0x86) },
	{ "tile.end_portal", new UIColor(0x00, 0x00, 0x00) },

	// Sculk
	{ "tile.sculk_vein", new UIColor(0x00, 0x38, 0x4F) },
	{ "tile.sculk_sensor", new UIColor(0x00, 0x38, 0x4F) },
	{ "tile.sculk_shrieker", new UIColor(0x00, 0x38, 0x4F) },

	// Monster eggs
	{ "tile.monster_egg", new UIColor(0x88, 0x8C, 0x8D) },
	{ "tile.infested_deepslate", new UIColor(0x39, 0x39, 0x2D) },
	
	// Misc
	{ "tile.reinforced_deepslate", new UIColor(0x39, 0x39, 0x2D) },
	{ "tile.obsidian", new UIColor(0x10, 0x10, 0x10) },
	{ "tile.crying_obsidian", new UIColor(0x10, 0x10, 0x10) },
	{ "tile.sponge", new UIColor(0x83, 0x83, 0x00) },
};