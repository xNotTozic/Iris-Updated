#pragma region Includes

bool g_isRunning = true;
bool g_hasInitialized = false;
bool g_fullyUpdated = true;
bool g_debugMode = true;

// C++ Includes
#include <windows.h>
#include <sstream>
#include <chrono>
#include <map>
#include <string>
#include <iostream>
#include <psapi.h>
#include <cassert>
#include <cstdarg>
#include <sysinfoapi.h>
#include <corecrt_math.h>
#include <unordered_map>
#include <wininet.h>
#include <tchar.h>
#include <stdexcept>
#include <vector>
#include <wincrypt.h>
#include <lmcons.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.h>

// include dx12
#include <d2d1.h>
#include <d2d1_2.h>
#include <dwrite.h>
#include <d3d12.h>
#include <d3d11on12.h>
#include <dxgi1_4.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "Libs/imgui/imgui.h"
#include "Libs/imgui/imgui_impl_win32.h"
#include "Libs/imgui/imgui_impl_dx12.h"

#include "Libs/kiero/kiero.h"
#include "Libs/imgui/imgui_impl_dx11.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Iris/Util/Render/Image/stb_image.h"
#include "Libs/imgui/imgui_internal.h"

#pragma comment(lib, "wininet.lib")

#define _logf(str) std::cout << str;

//c
class Player;
class MinecraftUIRenderContext;
class CommandManager;

// MinHook & utils
#include "SDK/GameCore/Struct/TextHolder.h"
#include "Libs/minhook/minhook.h"
#include "Util/MemoryUtils.h"
#include "Libs/glm/glm/glm.hpp"
#include "Libs/glm/glm/ext/matrix_transform.hpp"

#include "SDK/GameCore/Math/UIColor.h"

#include "SDK/GameCore/BlockRegistry.h"

#include "SDK/GameInput.h"

// Include meth
#include "SDK/GameCore/Math/MCTextFormat.h"
#include "SDK/GameCore/Math/TextInput.h"
#include "SDK/GameCore/Math/Keys.h"
#include "SDK/GameCore/Math/Math.h"
#include "SDK/GameCore/Math/Vector2.h"
#include "SDK/GameCore/Math/Vector3.h"
#include "SDK/GameCore/Math/Vector4.h"
#include "SDK/GameCore/Math/AABB.h"

Vector3<float> lifeboatTpTarget = Vector3<float>(0, 0, 0);

#include "Util/Render/EasingUtil.h"
#include "Util/Time/TimeUtil.h"

// Include render stuff
#include "SDK/GameCore/Math/CaretMeasureData.h"
#include "Notification/NotificationBase.h"

// had to move this for w2s
namespace GuiInfo
{
    static float DeltaTime = 0.016f;
    static float GuiScale = 1;

    static Vector2<float> TrueScreenRes = { 0, 0 };
    static Vector2<float> ScreenRes = { 0, 0 };

    static Vector2<short> TrueMousePos = { 0, 0 };
    static Vector2<short> MousePos = { 0, 0 };
}

uint64_t lastRunId = 0;

// Include globals
#include "Libs/json.hpp"
#include "Libs/xorstr.hpp"
#include "NonHookAddresses.h"
#include "SDK/GameCore/Game/ContainerScreenController/ContainerScreenController.h"
#include "SDK/GameCore/Game/ClientInstance/GuiData.h"
#include "SDK/GameCore/Game/ClientInstance/LoopbackPacketSender.h"
#include "SDK/GameCore/Game/ClientInstance/MoveInputHandler.h"
#include "SDK/GameCore/Game/ClientInstance/ClientInstance.h"
#include "SDK/GameCore/Game/ClientInstance/Actor/Inventory/Inventory.h"
#include "SDK/GameCore/Game/MinecraftUIRenderContext/ScreenContext/Tessellator/Tessellator.h"
#include "SDK/GameCore/Game/SplashJob.h"
#include "SDK/GameCore/Game/GameMode/GameMode.h"
#include "SDK/GameCore/Struct/Texture2D.h"
#include "SDK/GameCore/Game/ClientInstance/Actor/DirectPlayerMovementProxy.h"
#include "SDK/GameCore/Game/MinecraftUIRenderContext/UIScene.h"
#include "SDK/GameCore/Globals.h"
#include "Util/Render/ColorUtil.h"


#include "SDK/GameCore/Game/ClientInstance/Actor/Inventory/Item.h"
#include "SDK/GameCore/Game/ClientInstance/Actor/Inventory/ItemStack.h"
#include "SDK/GameCore/Game/ClientInstance/Actor/Inventory/Inventory.h"
#include "SDK/GameCore/Game/ClientInstance/Actor/InventoryTransaction.h"

#include "Util/Base64/Base64Util.h"
#include "Util/Util.h"
#include "Util/Render/RenderUtil.h"
#include "Util/Network/NetworkUtil.h"
#include "Util/Network/HWIDUtil.h"
#include "SDK/GameCore/Packet/Packet.h"
#include "SDK/GameCore/Game/ClientInstance/Actor/Actor.h"
#include "SDK/GameCore/Packet/Packets/MovePlayerPacket/MovePlayerPacket.h"
#include "SDK/GameCore/Packet/Packets/NetworkStackLatencyPacket/NetworkStackLatencyPacket.h"
#include "Util/Render/ParticleUtil.h"
#include "Util/Chat/ChatUtil.h"
#include "Util/Player/MoveUtil.h"
#include "Notification/Notification.h"

void getEntities(std::function<void(Player*)> callback) 
{
    if (Game::GetLocalPlayer() && Game::GetLocalPlayer()->GetLevel()) 
    {
        std::vector<Player*> listOut;
        std::function<bool __cdecl(Player&)> functor = [&listOut](Player& p) -> bool 
        {
            listOut.push_back(&p);
            return true;
        };

        CallVFunc<305, decltype(listOut)*>(Game::GetLocalPlayer()->GetLevel(), &listOut);  // Level::getRuntimeActorList
        CallVFunc<214, void>(Game::GetLocalPlayer()->GetLevel(), &functor); // Level::forEachPlayer

        for (auto actor : listOut)
        {
            callback(actor);
        }
    }
}
#include "Module/Module.h"

std::vector<Module*> modules = std::vector<Module*>();
std::vector<std::string> categories;

Module* getModuleByName(const std::string& name) {
    std::string nameLower(name);
    std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);

    auto it = std::find_if(modules.begin(), modules.end(), [&](Module* m) {
        std::string moduleNameLower = m->getName();
        std::transform(moduleNameLower.begin(), moduleNameLower.end(), moduleNameLower.begin(), ::tolower);
        moduleNameLower.erase(std::remove(moduleNameLower.begin(), moduleNameLower.end(), ' '), moduleNameLower.end());
        return nameLower == moduleNameLower;
        }
    );
    return it != modules.end() ? *it : nullptr;
}

void SaveConfig(std::string config);
void LoadConfig(std::string config);

#include "Command/Command.h"
#include "Command/CommandManager.h"

CommandManager commandMgr;

// hooks
#include "Hook/FuncHook.h"

// Controls Base
//#include "SDK/Window/Control.h"

// Windows
//#include "SDK/Window/Windows/DevForm.h"

// Controls
//#include "SDK/Window/Controls/TextLabel.h"

// other

#include "Module/ModuleHandler.h"

#include "SDK/MCUI/MCUI.h"

#pragma endregion

nlohmann::json GetSettings(std::vector<Setting*> _settings)
{
    nlohmann::json arr = nlohmann::json::array();

    for (const auto& obj : _settings) {
        nlohmann::json obj_json = nlohmann::json::object();

        obj_json["name"] = obj->name;
        obj_json["type"] = obj->type;

        switch (obj->type)
        {
        case SettingType::BOOL:
            if (!obj->value)
                break;

            obj_json["value"] = *reinterpret_cast<bool*>(obj->value);
            break;
        case SettingType::ENUM:
            if (!obj->getIterator())
                break;

            obj_json["value"] = *obj->getIterator();
            break;
        case SettingType::SLIDER:
            if (!obj->value)
                break;

            obj_json["value"] = *reinterpret_cast<float*>(obj->value);
            break;
        }

        arr.push_back(obj_json);
    }

    return arr;
}

void SetSettings(std::vector<Setting*> _settings, nlohmann::json settings)
{
    for (nlohmann::json::iterator it = settings.begin(); it != settings.end(); ++it)
    {
        nlohmann::json item = it.value();

        std::string itemname = item["name"].get<std::string>();

        for (Setting* setting : _settings)
        {
            if (strcmp(setting->getName().c_str(), itemname.c_str()) == 0)
            {
                //_logf(combine(item["value"], "\r\n"));
                //continue;

                switch (setting->type)
                {
                case SettingType::BOOL:
                    if (!setting->value)
                        break;

                    *reinterpret_cast<bool*>(setting->value) = item["value"].get<bool>();
                    break;
                case SettingType::SLIDER:
                    if (!setting->value)
                        break;

                    *reinterpret_cast<float*>(setting->value) = item["value"].get<float>();
                    break;
                case SettingType::ENUM:
                    if (!setting->getIterator())
                        break;

                    int value = item["value"].get<int>();

                    if (value >= 0 && value < setting->getEnumValues().size())
                        *setting->getIterator() = value;
                    break;
                }
            }
        }
    }
}

void SaveConfig(std::string config)
{
    nlohmann::json top_config;

    nlohmann::json global_config;
    global_config["theme"] = Game::Iris::ClientColor;
    global_config["name"] = Game::Iris::ClientName;
    top_config.push_back(global_config);

    for (Module* mod : modules)
    {
        nlohmann::json mod_config;
        mod_config["name"] = mod->getName();
        mod_config["keybind"] = mod->getKeybind();
        mod_config["enabled"] = mod->isEnabled();
        mod_config["exists"] = mod->exists;
        mod_config["visible"] = mod->isVisible();
        mod_config["ingameOnly"] = mod->ingameOnly;
        mod_config["requiresIngame"] = mod->requiresIngame;
        mod_config["showNotifications"] = mod->showNotifications;
        mod_config["settings"] = GetSettings(mod->getSettings());

        top_config.push_back(mod_config);
    }

    std::ofstream file(Util::getClientPath() + "Configurations\\" + config + ".json");
    if (file.is_open())
    {
        file << std::setw(4) << top_config;
        file.close();
    }
}

void LoadConfig(std::string config)
{
    std::ifstream file(Util::getClientPath() + "Configurations\\" + config + ".json");

    if (file.good()) // Check if the file exists and can be opened
    {
        nlohmann::json _config = nlohmann::json::parse(file);

        for (nlohmann::json::iterator it = _config.begin(); it != _config.end(); ++it)
        {
            nlohmann::json item = it.value();

            if (item.contains("theme"))
            {
                Game::Iris::ClientColor = item["theme"].get<int>();
                Game::Iris::ClientName = item["name"].get<std::string>();

                //_logf("Config has global config (loading...)");

                continue; // skip cuz global config (probably)
            }

            std::string itemname = item["name"].get<std::string>();

            for (Module* mod : modules)
            {
                if (strcmp(mod->getName().c_str(), itemname.c_str()) == 0)
                {
                    // correct module so lets unload the json data

                    mod->setKeybind(item["keybind"].get<int>());
                    mod->setEnabled(item["enabled"].get<bool>());
                    mod->exists = item["exists"].get<bool>();
                    mod->setVisible(item["visible"].get<bool>());
                    mod->ingameOnly = item["ingameOnly"].get<bool>();
                    mod->requiresIngame = item["requiresIngame"].get<bool>();
                    mod->showNotifications = item["showNotifications"].get<bool>();

                    SetSettings(mod->getSettings(), item["settings"]);
                }
            }
        }
        ChatUtil::sendMessage(combine("Successfully loaded config ", GRAY, config.c_str(), RESET, "!"));
    }
    else
    {
        ChatUtil::sendMessage(combine("Config not found ", GRAY, config.c_str(), RESET, "!"));
    }
}

DWORD APIENTRY ejectThread(HMODULE lpParam)
{
    while (g_isRunning)
        Sleep(0);

    std::cout << "Ejecting client..." << std::endl;

    Sleep(50);
    kiero::shutdown();
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    UninitializeMods();


#ifdef _DEBUG
    Util::closeConsole();
#endif
    FreeLibraryAndExitThread(lpParam, 1);
}

void sendReq()
{
    /*std::stringstream ss;
    ss << HWIDUitl::getUsername() << " has just injected " << Game::Iris::ClientName << " " << Game::Iris::ClientVersion;

    Game::Core::User = HWIDUitl::getUsername();

    NetworkUtil::sendDiscordRequest("/api/webhooks/1082728954013687870/q6b7S2dS8YKjDJLCQcVfpNbWbutYwkQgIbUdJmqfTwL517YLDuWKEijXq9j1peCMLbuc", "YS Clients", ss.str().c_str());
    std::cout << "Fingerprint " << HWIDUitl::generateFingerprint() << std::endl;*/
}

void InitializeClient()
{
    initChars();

    Util::initClientFiles();
#ifdef _DEBUG
    Util::createConsole();
#endif
    // Init modules
    std::cout << "[" << Game::Iris::ClientName << " " << Game::Iris::ClientVersion << "] Initializing modules" << std::endl;
    InitializeMods();

    // Init signatures

    Addresses::InitializeAddresses();

    if (!g_fullyUpdated)   
        std::cout << "[" << Game::Iris::ClientName << " " << Game::Iris::ClientVersion << "] Detected out of date signature please update" << std::endl;
    
    // Init Hooks
    std::cout << std::endl << "[" << Game::Iris::ClientName << " " << Game::Iris::ClientVersion << "] Initializing hooks" << std::endl;
    InitializeHooks();

    // Init commands
    std::cout << std::endl << "[" << Game::Iris::ClientName << " " << Game::Iris::ClientVersion << "] Initializing commands" << std::endl;
    commandMgr.InitCommands();

    Game::Core::noti.addNotification("Client:", "Injected " + Game::Iris::ClientName + "!", 5.f);

    g_hasInitialized = true;
    std::cout << "[" << Game::Iris::ClientName << " " << Game::Iris::ClientVersion << "] Finished initialization" << std::endl << std::endl;

    // Calculate the games fps
    std::thread countThread([] {
        while (g_isRunning) {
            Sleep(1000);
            Game::gameFps = Game::frameCount;
            Game::frameCount = 0;
        }
        });
    countThread.detach();
}

BOOL APIENTRY DllMain(HMODULE a1, DWORD a2, LPVOID a3)
{
    switch (a2)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(a1);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitializeClient, a1, 0, 0);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ejectThread, a1, 0, 0);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}