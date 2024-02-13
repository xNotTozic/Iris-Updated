#pragma once

#include "../../SDK/GameCore/Game/ClientInstance/Actor/Actor.h"
#include <xmmintrin.h>

void* oSwingSpeed;
void* oInterpolatedHeadYaw;
void* oInterpolatedBodyYaw;
void* oInterpolatedRotation;

float getInterpolatedHeadYaw(Player* _this, float a1) {
    if (_this == Game::GetLocalPlayer() && getModuleByName("aura")->isEnabled() && !Game::TargetLists::auraList.empty()) {
        Game::Core::easedHeadYaw = Math::wrap(Game::Core::easedHeadYaw, Game::Core::headYaw - 180.f, Game::Core::headYaw + 180.f);
        Game::Core::easedHeadYaw = Math::lerp(Game::Core::easedHeadYaw, Game::Core::headYaw, RenderUtil::getDeltaTime() * 2.07);
        return Game::Core::easedHeadYaw;
    }
    else if (Game::TargetLists::auraList.empty()) {
        Game::Core::easedHeadYaw = Game::Core::headYaw;
    }
    return CallFunc<float, Player*, float>(oInterpolatedHeadYaw, _this, a1);
}

float getInterpolatedBodyYaw(Player* _this, float a1) {
    if (_this == Game::GetLocalPlayer() && getModuleByName("aura")->isEnabled() && !Game::TargetLists::auraList.empty()) {
        Game::Core::easedBodyYaw = Math::wrap(Game::Core::easedBodyYaw, Game::Core::easedHeadYaw - 180.f, Game::Core::easedHeadYaw + 180.f);
        Game::Core::easedBodyYaw = Math::lerp(Game::Core::easedBodyYaw, Game::Core::easedHeadYaw, RenderUtil::getDeltaTime() * 1.04);
        return Game::Core::easedBodyYaw;
    }
    else if(Game::TargetLists::auraList.empty()) {
        Game::Core::easedBodyYaw = Game::Core::bodyYaw;
    }
    return CallFunc<float, Player*, float>(oInterpolatedBodyYaw, _this, a1);
}
float* yRot(Player* _this, float* a2, float a3) {
    auto oFunc = CallFunc<float*, Player*, float*, float>(oInterpolatedRotation, _this, a2, a3);
    if (_this == Game::GetLocalPlayer() && getModuleByName(xorstr_("aura"))->isEnabled() && !Game::TargetLists::auraList.empty()) {
        Game::Core::easedPitch = Math::lerp(Game::Core::easedPitch, Game::Core::pitch, RenderUtil::getDeltaTime() * 2.07);
        a2[0] = Game::Core::easedPitch;
        return oFunc;
    }
    else if (Game::TargetLists::auraList.empty()) {
        Game::Core::easedPitch = Game::Core::pitch;
    }
    return oFunc;
}

int getCurrentSwingDurationDetour(Mob* _this) {
    float ReturnValue = Game::Core::SwingSpeed;

    Game::Core::Mob = _this;

    if (Game::GetLocalPlayer()) {
        bool cancelled = false;

        ActorTickEvent event{ _this, &ReturnValue };
        event.cancelled = &cancelled;
        DispatchEvent(&event);

        if (cancelled)
        {
            std::cout << xorstr_("Cant cancel actor tick events from a module") << std::endl;
        }

        static bool hooked = false;
        auto vTable = *(uintptr_t**)_this;
        if (!hooked) {
            HookFunction((void*)vTable[31], (void*)&getInterpolatedHeadYaw, &oInterpolatedHeadYaw, "HeadYaw");
            HookFunction((void*)vTable[32], (void*)&getInterpolatedBodyYaw, &oInterpolatedBodyYaw, "BodyYaw");
            hooked = true;
        }
    }

    return ReturnValue;
}

class ActorHook : public FuncHook
{
public:
    static ActorHook& Instance() {
        static ActorHook instance;
        return instance;
    }

    bool Initialize() override {
        void* swingSpeedAddr = findSig(xorstr_("48 89 5C 24 ?? 57 48 83 EC ?? 48 8B 15 ?? ?? ?? ?? 48 8B F9"));
        void* addr = findSig(xorstr_("48 89 5c 24 ? 55 56 57 48 83 ec ? 8b 41 ? 48 8b ea 48 8b 49"));
        if (!HookFunction(swingSpeedAddr, (void*)&getCurrentSwingDurationDetour, &oSwingSpeed, xorstr_("SwingTick"))) {
            return false;
        }
        if (!HookFunction(addr, (void*)&yRot, &oInterpolatedRotation, xorstr_("Rot"))) {
            return false;
        }
        return true;
    }
};
