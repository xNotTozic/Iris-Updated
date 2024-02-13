#pragma once

void* __o__DrawSplash;

#include "../../SDK/GameCore/Struct/UIControl.h"

//SplashTextRenderer::render(SplashTextRenderer *this, MinecraftUIRenderContext *, IClientInstance *, UIControl *, int, RectangleArea *)
__int32 SplashTextRenderDetour(
    SplashJob* _this,
    __int64 ctx,
    __int64 ci,
    UIControl* control,
    __int64 a5,
    __int64 rect
)
{
    control->Position = titlePos + titleSize - Vector2<float>(titleSize.x / 16, titleSize.y / 16);
    control->Opacity = 0.5f; // halve it

    return CallFunc<float, SplashJob*, __int64, __int64, UIControl*, __int64, __int64>(
        __o__DrawSplash,
        _this,
        ctx,
        ci,
        control,
        a5,
        rect
    );
}

#include <thread>

class SplashHook : public FuncHook
{
public:
    static SplashHook& Instance()
    {
        static SplashHook instance;
        return instance;
    }

    bool Initialize() override
    {
        void* splashAddr = findSig(xorstr_("48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? ? ? 70 A8 ? ? 78 98 44 ? ? 40 88 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E1"));

        return HookFunction(
            splashAddr,
            (void*)&SplashTextRenderDetour,
            &__o__DrawSplash,
            xorstr_("CheckSplash")
        );
    }
};