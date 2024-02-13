#pragma once

#include "../../../SDK/GameCore/Game/MinecraftUIRenderContext/MinecraftUIRenderContext.h"
#include "../../../SDK/GameCore/Game/MinecraftUIRenderContext/ScreenView/UILayer.h"

#include "../../../SDK/MCUI/MCUI.h"

void* __o__Render;
void* __o__DrawText;

__int64* __o__UIScene;
__int64* __o__DrawImage;
__int64* __o__DrawNineSlice;
__int64* __o__UISceneRender;
__int64* __o__SendPacket;

bool hookedTxt = false;
bool supported = false;

Vector2<float> titlePos = { 0,0 };
float anim = 0;
Vector2<float> titleSize = { 0,0 };

// gonna clean this up once I sort everything out

#include "DrawTextHook.h"
#include "DrawImageHook.h"
#include "NinesliceHook.h"
#include "UISceneRenderHook.h"
#include "SendToServerHook.h"

bool RenderingGameMenus = true;

void SetupAndRenderDetour(
    ScreenView* screenView,
    MinecraftUIRenderContext* ctx
)
{
    auto var = ctx->ScreenContext;
    RenderUtil::setCTX(ctx);

    if (UILayer::Is(screenView, UILayer::MainMenu_Screen))
    {
        anim = Math::animate(1, anim, RenderUtil::getDeltaTime() * 10);
        Vector4<float> screenRes = Vector4<float>(0, 0, GuiInfo::ScreenRes.x, GuiInfo::ScreenRes.y);

        // Dont put below 2 <3
        constexpr float finalZoom = 2;
        static float zoom = 0, opacity = 0;
        zoom = Math::lerp(20, finalZoom, anim), opacity = Math::lerp(0, 1, anim);

        Vector2<float> size = Vector2<float>(screenRes.z * zoom, screenRes.w * zoom);

        // Lerp our mouse pos for smooth effect
        static float x = GuiInfo::MousePos.x, y = GuiInfo::MousePos.y;
        x = Math::animate(GuiInfo::MousePos.x, x, RenderUtil::getDeltaTime() * 8);
        y = Math::animate(GuiInfo::MousePos.y, y, RenderUtil::getDeltaTime() * 8);
        Vector2<float> mousePos = Vector2<float>(x, y);

        // Calculate the offset from the middle of the screen ye
        Vector2<float> rectCenter = Vector2<float>(screenRes.z / 2, screenRes.w / 2);
        Vector2<float> offset = mousePos - rectCenter;
        Vector2<float> rectPosition = rectCenter - offset - Vector2<float>(size.x / 2, size.y / 2);

        // Final rect area
        Vector4<float> rect = Vector4<float>(rectPosition.x, rectPosition.y, rectPosition.x + size.x, rectPosition.y + size.y);

        RenderUtil::renderImage(Util::getClientPath() + xorstr_("Assets\\mainMenuBackground.png"), rect);
        RenderUtil::flushImage(UIColor(255, 255, 255), opacity);
    }

    LayerUpdateEvent event{ screenView };
    event.cancelled = nullptr;
    DispatchEvent(&event);

    if (UILayer::Is(screenView, UILayer::Ingame_ChatScreen))
        Game::Core::InChat = true;

    if (UILayer::Is(screenView, {
            UILayer::Ingame_InventoryScreen,
            UILayer::Ingame_CanMoveScreen
        }))
    {
        Game::Core::InChat = false;
    }

    // Pre render
    if (UILayer::IsNot(screenView, {
            UILayer::Toast_ToastScreen,
            UILayer::Debug_DebugScreen,
        }))
    {
        if (Game::FontRepos::GetClientFont())
        {
            bool cancelled = false;

            BeforeUpdateEvent event{ ctx, screenView };
            event.cancelled = &cancelled;
            DispatchEvent(&event);

            if (cancelled == true)
            {
                std::cout << xorstr_("Cant cancel render events from a module (Use RenderingGameMenus boolean)") << std::endl;
            }
        }
    }

    if (RenderingGameMenus)
    {
        CallFunc<void*, void*, MinecraftUIRenderContext*>(
            __o__Render,
            screenView,
            ctx
        );
    }

    Game::Setup(ctx->ClientInstance, screenView->deltaTime, screenView->ScreenScale);

    auto stuff = *(uintptr_t**)ctx->ClientInstance;

    auto func = stuff[25];
    auto func2 = func;

    static bool hooked = false;
    if (not hooked)
    {
        auto VTable = *(uintptr_t**)ctx;

        HookFunction(
            (void*)VTable[5], // grab the 6th index & hook it lol
            (void*)&DrawTextDetour,
            &__o__DrawText,
            "DrawString"
        );

        auto Loopback_VTable = *(uintptr_t**)ctx->ClientInstance->getPacketSender();

        HookFunction(
            (void*)Loopback_VTable[2],
            (void*)&SendToServerDetour,
            &__o__SendPacket,
            "SendToServer"
        );
        HookFunction(
            (void*)VTable[7],
            (void*)&DrawImageDetour,
            &__o__DrawImage,
            "DrawImage"
        );

        HookFunction(
            (void*)VTable[8],
            (void*)&DrawNineSliceDetour,
            &__o__DrawNineSlice,
            "DrawNineslice"
        );

        hooked = true;
    }

    if (UILayer::Is(screenView, UILayer::Toast_ToastScreen))
    {
        Game::frameCount++;

        if (Game::FontRepos::GetClientFont())
        {
            bool cancelled = false;

            RenderUtil::setCTX(ctx);

            UpdateEvent event{ ctx, screenView };
            event.cancelled = &cancelled;
            DispatchEvent(&event);

            if (cancelled == true)
            {
                std::cout << "Cant cancel render events from a module (Use RenderingGameMenus boolean)" << std::endl;
            }
        }
    }
}

class RenderContextHook : public FuncHook
{
public:
    bool Initialize() override
    {
        void* renderAddr = findSig("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B ? 48 89 54 24 ? 4C"); // Updated to 1.20.51
        // 48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 ? B8 0F 29 ? A8 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B F2 48 89 54 24 ? 4C in 1.20.0.1
        void* uisceneTickAddr = findSig("48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B FA 48 8B D9 B9 ? ? ? ?");

        if (!HookFunction(renderAddr, (void*)&SetupAndRenderDetour, &__o__Render, "RenderLayer"))
            return false;

        if (!HookFunction(uisceneTickAddr, (void*)&UISceneRender, &__o__UISceneRender, "UISceneRender"))
            return false;

        return true;
    }

    static RenderContextHook& Instance()
    {
        static RenderContextHook instance;
        return instance;
    }
};