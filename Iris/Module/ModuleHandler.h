#pragma once

#pragma region Module imports

int disablerMode = 0;

#include "Modules/Visual/Animations.h"
#include "Modules/Visual/NoHurtcam.h"
#include "Modules/Visual/ItemModel.h"
#include "Modules/Visual/Outline.h"
#include "Modules/Visual/ESP.h"
#include "Modules/Visual/ArrayList.h"
#include "Modules/Visual/ClickGUI/ClickGUI.h"
#include "Modules/Visual/Hud.h"
#include "Modules/Visual/Watermark.h"
#include "Modules/Visual/Changelog.h"
#include "Modules/Visual/OreSense.h"
#include "Modules/Visual/ViewBob.h"
#include "Modules/Visual/Zoom.h"
#include "Modules/Visual/Nametags.h"
#include "Modules/Visual/WorldBorder.h"

#include "Modules/Combat/Hitbox.h"
#include "Modules/Combat/Killaura.h"
#include "Modules/Combat/Tpaura.h"
#include "Modules/Combat/Reach.h"
#include "Modules/Combat/Criticals.h"

#include "Modules/Player/AirJump.h"
#include "Modules/Player/BlockReach.h"
#include "Modules/Player/ChestStealer.h"
#include "Modules/Player/ChestDumper.h"
#include "Modules/Player/Phase.h"
#include "Modules/Player/Velocity.h"
#include "Modules/Player/AntiAFK.h"
#include "Modules/Player/TrueJesus.h"
#include "Modules/Player/InventoryMove.h"
#include "Modules/Player/Freecam.h"
#include "Modules/Player/Spider.h"
#include "Modules/Player/Glide.h"

#include "Modules/Movement/Flight.h"
#include "Modules/Movement/Speed.h"
#include "Modules/Movement/FastStop.h"
#include "Modules/Movement/AutoSprint.h"
#include "Modules/Movement/ReverseStep.h"
#include "Modules/Movement/AntiVoid.h"
#include "Modules/Movement/NoWeb.h"

#include "Modules/Miscellaneous/Franky.h"
#include "Modules/Miscellaneous/ClickTP.h"
#include "Modules/Miscellaneous/TestModule.h"
#include "Modules/Miscellaneous/CosmoCrasher.h"
#include "Modules/Miscellaneous/Disabler.h"
#include "Modules/Miscellaneous/NoFall.h"
#include "Modules/Miscellaneous/InstaBreak.h"
#include "Modules/Miscellaneous/ClientSidedUI.h"
#include "Modules/Miscellaneous/NetSkip.h"

#include "Modules/World/Nuker.h"
#include "Modules/World/Fucker.h"
#include "Modules/World/Scaffold.h"
#include "Modules/World/Timer.h"
#include "Modules/World/SoundPlayer.h"
#include "Modules/World/Blink.h"
#include "Modules/World/NoPacket.h"
#include "Modules/World/AirStuck.h"

// INVISIBLE MODULES!
#include "Modules/System/LifeboatTickAction.h"
#include "Modules/System/ClientTick.h"
#include "Modules/System/LayoutEditor.h"

#pragma endregion

void SortCategories()
{
	for (Module* mod : modules)
	{
		if (std::find(categories.begin(), categories.end(), mod->getCategory()) == categories.end())
			categories.push_back(mod->getCategory());
	}
}

void InitializeModules()
{
	//Visual;
	modules.push_back(new ArrayList(Keyboard::NONE, true));
	modules.push_back(new ItemModel(Keyboard::NONE));
	modules.push_back(new FakeBlock(Keyboard::NONE, true));
	modules.push_back(new HudModule(Keyboard::NONE));
	modules.push_back(new ClickGUI(Keyboard::INSERT));
	modules.push_back(new Watermark(Keyboard::NONE, true));
	modules.push_back(new OreSense(Keyboard::NONE));
	modules.push_back(new NoHurtcam(Keyboard::NONE));
	modules.push_back(new ESP(Keyboard::NONE));
	modules.push_back(new Outline(Keyboard::NONE));
	modules.push_back(new ViewBobbing(Keyboard::NONE));
	//modules.push_back(new Zoom(Keyboard::NONE));
	modules.push_back(new WorldBorder(Keyboard::NONE));
	modules.push_back(new Nametags(Keyboard::NONE));

	//Combat
	//modules.push_back(new Hitbox(Keyboard::NONE));
	modules.push_back(new Killaura(Keyboard::NONE));
	modules.push_back(new Tpaura(Keyboard::NONE));
	modules.push_back(new Reach(Keyboard::NONE));
	modules.push_back(new Criticals(Keyboard::NONE));

	//Movement
	modules.push_back(new Flight(Keyboard::NONE));
	modules.push_back(new NoWeb(Keyboard::NONE));
	modules.push_back(new Speed(Keyboard::NONE));
	modules.push_back(new FastStop(Keyboard::NONE));
	modules.push_back(new AutoSprint(Keyboard::NONE));
	modules.push_back(new ReverseStep(Keyboard::NONE));

	//Player
	modules.push_back(new AntiAFK(Keyboard::NONE));
	modules.push_back(new AirJump(Keyboard::NONE));
	modules.push_back(new BlockReach(Keyboard::NONE));
	modules.push_back(new ChestStealer(Keyboard::NONE));
	modules.push_back(new Velocity(Keyboard::NONE));
	modules.push_back(new Phase(Keyboard::NONE));
	modules.push_back(new TrueJesus(Keyboard::NONE));
	modules.push_back(new ChestDumper(Keyboard::NONE));
	modules.push_back(new InventoryMove(Keyboard::NONE));
	modules.push_back(new Freecam(Keyboard::NONE));
	modules.push_back(new Spider(Keyboard::NONE));
	modules.push_back(new Glide(Keyboard::NONE));

	//Misc
	modules.push_back(new Module("AntiBot", "Misc", "No more bots :)", Keyboard::NONE, true));
	//modules.push_back(new ClickTP(Keyboard::NONE));
	modules.push_back(new Franky(Keyboard::NONE));
	modules.push_back(new TestModule(Keyboard::NONE));
	modules.push_back(new CosmoCrasher(Keyboard::NONE));
	modules.push_back(new Disabler(Keyboard::NONE));
	modules.push_back(new InstaBreak(Keyboard::NONE));
	modules.push_back(new NoFall(Keyboard::NONE));
	modules.push_back(new ClientSidedUI(Keyboard::NONE));
	modules.push_back(new NetSkip(Keyboard::NONE));

	//World
	modules.push_back(new AirStuck(Keyboard::NONE));
	modules.push_back(new Nuker(Keyboard::NONE));
	modules.push_back(new Fucker(Keyboard::NONE));
	modules.push_back(new Scaffold(Keyboard::NONE));
	modules.push_back(new Timer(Keyboard::NONE));
	modules.push_back(new AntiVoid(Keyboard::NONE));
	modules.push_back(new Blink(Keyboard::NONE));
	modules.push_back(new NoPacket(Keyboard::NONE));

	//System
	//modules.push_back(new LifeboatTickAction(Keyboard::NONE));
	//modules.push_back(new ClientTick(Keyboard::NONE));
	//modules.push_back(new LayoutEditor(Keyboard::DELETE_KEY));

	std::string out;
	bool versionMismatch = false;
	if (Util::doesClientPathExist(Util::getClientPath() + "Version.iris"))
	{
		std::ifstream verFileRead;
		verFileRead.open(Util::getClientPath() + "Version.iris");
		std::getline(verFileRead, out);
		verFileRead.close();

		if (out != Game::Iris::ClientVersion)
			versionMismatch = true;
	}
	else
		versionMismatch = true;

	if (versionMismatch)
		modules.push_back(new Changelog(Keyboard::NONE));

	std::ofstream verFile;
	verFile.open(Util::getClientPath() + "Version.iris");

	if (verFile.is_open())
	{
		verFile << Game::Iris::ClientVersion;
		verFile.close();
	};
}

void InitializeMods()
{
	InitializeModules();

	SortCategories(); // create categories
}

void UninitializeMods()
{
	for (auto mod : modules)
	{
		if (mod->isEnabled())
			mod->toggle();

		delete mod;
	}
}