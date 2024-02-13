#pragma once

namespace Addresses
{
	namespace Render
	{
		static void* uiMaterial;
		static void* tess_Vertex;
		static void* tess_Begin;
		static void* renderMesh;

		void initRenderAddr()
		{
			uiMaterial = findOffset(xorstr_("4C 8D 05 ?? ?? ?? ?? 48 8B D3 48 8B CF 48 8B 5C 24 ?? 0F 28 7C 24 ?? 44 0F 28 44 24 ?? 48"), xorstr_("UIMaterial"));
			tess_Vertex = findOffset(xorstr_("40 57 48 81 ec ? ? ? ? 0f 29 7C 24"), xorstr_("TessVertex"));
			tess_Begin = findOffset(xorstr_("48 89 5c 24 ? 55 48 83 ec ? 80 b9 ? ? ? ? ? 45 0f b6 d1"), xorstr_("TessBegin"));
			renderMesh = findOffset(xorstr_("40 55 53 56 57 41 56 48 8d ac 24 ? ? ? ? 48 81 ec ? ? ? ? 49 8b f0"), xorstr_("RenderMesh"));
		}
	}
	static void* DisplayClientMessageAddr;
	static void* TeleportToAddr;
	static void* GetMovementProxy;
	static void* getplayerAddr;
	static void* getActorAddr;
	static void* getBlocksource;
	static void* getBlock;

	static void* TryGet_RuntimeId;

	static int hurttimeComponent;
	static int actorStateComponent;

	void InitializeAddresses()
	{
		Render::initRenderAddr();

		DisplayClientMessageAddr = findOffset(xorstr_("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B FA 48 8B 89"), xorstr_("DisplayClientMessage"));
		TeleportToAddr = findOffset(xorstr_("48 89 5C 24 18 55 56 57 48 81 EC ? ? ? ? ? ? B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 41"), xorstr_("TeleportTo"));
		getplayerAddr = findOffset(xorstr_("48 81 C1 ?? ?? ?? ?? E9 ?? ?? ?? ?? CC CC CC CC 40 53 48 83 EC 20 48 8B 01"), xorstr_("GetLocalPlayer"));
		getActorAddr = findOffset(xorstr_("48 8D 05 ? ? ? ? 48 89 01 49 8B 00 48 89 41 ?"), "GetActor");
		getBlocksource = findOffset(xorstr_("48 83 EC 58 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8D 91 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 80 7C 24 ? ? 74 45"), xorstr_("GetBlockSource"));
		getBlock = findOffset(xorstr_("48 89 5C 24 10 57 48 83 EC 20 48 8B F9 48 8B DA 8B"), xorstr_("GetBlock"));
		GetMovementProxy = findOffset(xorstr_("40 53 48 83 ec ? 8b 41 ? 48 8b da 48 8b 49 ? 48 8d 54 24 ? 89 44 24 ? 48 8b 09 e8 ? ? ? ? 45 33 c9"), xorstr_("GetMovementProxy"));

		TryGet_RuntimeId =
		reinterpret_cast<void*>(
			(uintptr_t)findOffset(xorstr_("73 23 8B 04 82 49 8B 4A 48 25 ? ? ? ? 8B D0 83 E0 7F 48 6B C0 44"), xorstr_("try_get<RuntimeIDComponent>"))
			+ 0x23
		);
		// dropSlot - 85 D2 0F 88 ? ? ? ? 48 89 5C 24 ? 55 56 57 41 54 | InventoryCleaner
		// _handleAutoPlace - | ChestStealer
		
		hurttimeComponent = *reinterpret_cast<int*>((uintptr_t)findOffset(xorstr_("66 ? ? 80 ? ? ? ? ? ? C0 F3 ? ? 81"), xorstr_("try_get<HurttimeComponent>")) + 4);
		actorStateComponent = *reinterpret_cast<int*>((uintptr_t)findOffset(xorstr_("48 8B 81 ? ? ? ? 48 85 C0 74 09 48 83 C0 0C"), xorstr_("try_get<StateVectorComponent>")) + 3);
	}
}