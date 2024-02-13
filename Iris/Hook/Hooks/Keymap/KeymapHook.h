#pragma once

void* __o__SendKeyboardKey;
void* __o__SendMouseEvent;

void SendKeyboardKeyDetour(
    int key,
    bool held
)
{
    Game::Core::Keymap[key] = held;

    // Listen for eject keys to be held and eject the client (universal keybind)
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('L') & 0x8000) && g_hasInitialized) g_isRunning = false;

    bool cancelled = false;

    //if (ImGui::GetCurrentContext() != nullptr)
    //{
    //    ImGuiIO& io = ImGui::GetIO();
    //    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard navigation

    //    io.KeysDown[key] = held;

    //    if (io.WantCaptureKeyboard)
    //        return;
    //}

    KeyboardEvent event{ &key, &held };
    event.cancelled = &cancelled;
    DispatchEvent(&event);

    for (Module* mod : modules)
    {
        if (held == true)
        {
            if (mod->getKeybind() == key)
            {
                if (mod->ingameOnly)
                {
                    if (Game::GetInstance() != nullptr && Game::GetInstance()->mcGame->canUseMoveKeys())
                    {
                        mod->toggle();
                    }
                }
                else mod->toggle();
            }
        }
    }

    if (!cancelled)
    {
        CallFunc<void*, int, bool>(
            __o__SendKeyboardKey,
            key,
            held
        );
    }
}

void PressKey(int key)
{
    SendKeyboardKeyDetour(key, true);
    SendKeyboardKeyDetour(key, false);
}

#include "MouseHook.h"

class KeymapHook : public FuncHook
{
public:
    bool Initialize() override
    {
        void* keymapAddr = findSig(xorstr_("48 83 EC 48 ? ? C1 4C 8D"));
        void* mousemapAddr = findSig(xorstr_("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24"));

        if (not HookFunction(keymapAddr, (void*)&SendKeyboardKeyDetour, &__o__SendKeyboardKey, "Keyboard"))
            return false;

        if (not HookFunction(mousemapAddr, (void*)&MouseDetour, &__o__SendMouseEvent, "Mouse"))
            return false;

        return true;
    }

    static KeymapHook& Instance()
    {
        static KeymapHook instance;
        return instance;
    }
};