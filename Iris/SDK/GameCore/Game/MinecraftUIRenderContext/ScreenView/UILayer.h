#pragma once

namespace UILayer
{
	static std::string Ingame_CanMoveScreen("UnknownLayer");

	// ingame menus
	static std::string Ingame_ChatScreen("chat.chat_screen");
	static std::string Ingame_HudScreen("hud.hud_screen");
	static std::string Ingame_PauseScreen("pause.pause_screen");
	static std::string Ingame_InventoryScreen("crafting.inventory_screen");
	static std::string Ingame_DeathScreen("death.death_screen");
	static std::string Ingame_Progress_ModalProcessScreen("progress.modal_progress_screen");

	// ingame container menus
	static std::string Ingame_SmithingTableScreen("smithing_table.smithing_table_screen");
	static std::string Ingame_BlastFurnaceScreen("blast_furnace.blast_furnace_screen");
	static std::string Ingame_BrewingStandScreen("brewing_stand.brewing_stand_screen");
	static std::string Ingame_StoneCutterScreen("stonecutter.stonecutter_screen");
	static std::string Ingame_CartographyScreen("cartography.cartography_screen");
	static std::string Ingame_SmallChestScreen("chest.small_chest_screen");
	static std::string Ingame_LargeChestScreen("chest.large_chest_screen");
	static std::string Ingame_ShulkerBoxScreen("chest.shulker_box_screen");
	static std::string Ingame_EnderChestScreen("chest.ender_chest_screen");
	static std::string Ingame_BarrelScreen("chest.barrel_screen");
	static std::string Ingame_CraftingScreen("crafting.crafting_screen");
	static std::string Ingame_EnchantingScreen("enchanting.enchanting_screen");
	static std::string Ingame_BeaconScreen("beacon.beacon_screen");
	static std::string Ingame_FurnaceScreen("furnace.furnace_screen");
	static std::string Ingame_SmokerScreen("smoker.smoker_screen");
	static std::string Ingame_DispenserScreen("redstone.dispenser_screen");
	static std::string Ingame_DropperScreen("redstone.dropper_screen");
	static std::string Ingame_HopperScreen("redstone.hopper_screen");
	static std::string Ingame_InBedScreen("bed.in_bed_screen");
	static std::string Ingame_LoomScreen("loom.loom_screen");
	static std::string Ingame_BookScreen("book.book_screen");
	static std::string Ingame_GrindStoneScreen("grindstone.grindstone_screen");
	static std::string Ingame_AnvilScreen("anvil.anvil_screen");
	static std::string Ingame_ThirdPartyScreen("server_form.third_party_server_screen");

	static std::string Toast_ToastScreen("toast_screen.toast_screen");

	static std::string Debug_DebugScreen("debug_screen.debug_screen");

	static std::string ProfileCard_ProfileCardScreen("profile_card.profile_card_screen");

	static std::string Start_StartScreen("start.start_screen");

	static std::string Play_PlayScreen("play.play_screen");

	static std::string XBL_FriendFinderScreen("xbl_friend_finder.xbl_friend_finder");

	static std::string Events_GatheringInfoScreen("gathering_info.gathering_info_screen");

	static std::string WorldTemplates_WorldTemplateScreen("world_templates.world_templates_screen");

	static std::string Feed_FeedScreen("feed.feed_screen");
	static std::string Feed_CommentScreen("comment.comment_screen");

	static std::string Progress_LoadingScreen("progress.world_loading_progress_screen");
	static std::string Progress_SavingScreen("progress.world_saving_progress_screen");
	static std::string Progress_RealmLoadingScreen("progress.realms_loading_progress_screen");

	static std::string Settings_ScreenControls("settings.screen_controls_and_settings");
	static std::string Settings_WorldEditScreen("settings.screen_world_edit");
	static std::string Settings_HowToScreen("how_to_play.how_to_play_screen");
	static std::string Settings_SafeZoneScreen("safe_zone.safe_zone_screen");
	static std::string Settings_AddExternalServerEditScreen("add_external_server.add_external_server_screen_edit");

	static std::string Store_DataDrivenScreen("store_layout.store_data_driven_screen");
	static std::string Store_InventoryScreen("store_inventory.store_inventory_screen");

	static std::string RealmsPlus_RealmsPlusPDPScreen("realmsPlus.realms_plus_pdp_screen");
	static std::string RealmsPlus_SlotsScreen("realms_slots.realms_slots_screen");
	static std::string RealmsPlus_WorldEditScreen("settings.screen_world_slot_edit");
	static std::string RealmsPlus_LocalWorldPickerScreen("local_world_picker.local_world_picker_screen");
	static std::string RealmsPlus_RealmManageScreen("settings.screen_realm_manage");

	static std::string Persona_ProfileScreen("profile.profile_screen");
	static std::string Persona_PersonaScreen("persona.persona_screen");

	static std::vector<std::string> MainMenu_Screen = {
		Start_StartScreen,
		Play_PlayScreen,
		XBL_FriendFinderScreen,
		WorldTemplates_WorldTemplateScreen,
		Progress_LoadingScreen, // all but the realms one cuz that needs special care
		Progress_SavingScreen,
		Settings_AddExternalServerEditScreen, // all settings menu
		Settings_WorldEditScreen,
		Settings_HowToScreen,
		Settings_ScreenControls,
		Settings_SafeZoneScreen,
		Persona_PersonaScreen, // all of persona stuff
		Persona_ProfileScreen,
		Feed_CommentScreen, // realms comments stuff
		Feed_FeedScreen,
		RealmsPlus_LocalWorldPickerScreen, // all realms management stuff
		RealmsPlus_RealmManageScreen,
		RealmsPlus_RealmsPlusPDPScreen,
		RealmsPlus_SlotsScreen,
		RealmsPlus_WorldEditScreen,
		Store_DataDrivenScreen, // all of the marketplace store
		Store_InventoryScreen
	};

	bool Is(ScreenView* screen, std::string screenType)
	{
		return screen->tree->root->GetName() == screenType;
	}

	bool Is(ScreenView* screen, std::vector<std::string> screenTypes)
	{
		std::string currentScreenType = screen->tree->root->GetName();

		for (std::string type : screenTypes)
		{
			if (currentScreenType == type)
			{
				return true;
			}
		}

		return false;
	}

	bool IsNot(ScreenView* screen, std::string screenType)
	{
		return screen->tree->root->GetName() != screenType;
	}

	bool IsNot(ScreenView* screen, std::vector<std::string> screenTypes)
	{
		std::string currentScreenType = screen->tree->root->GetName();

		for (std::string type : screenTypes)
		{
			if (currentScreenType == type)
			{
				return false;
			}
		}

		return true;
	}
}