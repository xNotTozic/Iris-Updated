#pragma once

class FuncHook
{
public:
	virtual bool Initialize() = 0;
};

#include "../SDK/GameCore/Game/MinecraftUIRenderContext/ScreenView/ScreenView.h"

#include "SDK/Event/Events.h"

#include "Hooks/DirectX/DirectXHook.h"
#include "Hooks/RenderContext/RenderContextHook.h"
#include "Hooks/Keymap/KeymapHook.h"
#include "Hooks/SwingHook.h"
#include "Hooks/ContainerTickHook.h"
#include "Hooks/SplashHook.h"
#include "Hooks/ViewBobbingHook.h"
#include "Hooks/LerpMotion.h"
#include "Hooks/HurtcamHook.h"
#include "Hooks/SendChatMessage.h"
#include "Hooks/onUpdateHook.h"
#include "Hooks/FieldHook.h"
#include "Hooks/RakPeer/RakPeerHooks.h"
#include "Hooks/Camera/CameraHooks.h"

//#include "Hooks/GammaTick.h"
//#include "Hooks/UIControl.h"

void InitializeHooks()
{
    static FuncHook* hooks[] = {
        &onUpdateHook::Instance(),
        &SendChatMessage::Instance(),
        &KeymapHook::Instance(),
        &RenderContextHook::Instance(),
        &Dx12Hook::Instance(),
        &ActorHook::Instance(),
        //&SplashHook::Instance(),
        &ViewbobHook::Instance(),
        &LerpMotionHook::Instance(),
        &ContainerTickHook::Instance(),
        &HurtcamHook::Instance(),
        &RakPeerHooks::Instance(),
        &CameraHooks::Instance(),
    };

    for (std::size_t i = 0; i < std::size(hooks); ++i)
    {
        if (not hooks[i]->Initialize())
        {
            //error handling
        }
    }

    std::cout << "[" << Game::Iris::ClientName << " " << Game::Iris::ClientVersion << "] Initialized hooks" << std::endl;
}