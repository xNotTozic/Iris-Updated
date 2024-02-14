#pragma once

#include "../../SDK/GameCore/Game/ClientInstance/Actor/Actor.h"
#include <xmmintrin.h>

void* oFluxSwing;


bool getItemUseDurationDetour(Mob* _this) {
    bool ReturnValue = Game::Core::ShouldFlux;

    Game::Core::Mob = _this;

    return Game::Core::ShouldFlux;
}

class FluxHook : public FuncHook
{
public:
    static FluxHook& Instance() {
        static FluxHook instance;
        return instance;
    }

    bool Initialize() override {
        // Player::getItemUseDuration(void)

        void* addr = findSig(xorstr_("8b 81 ? ? ? ? c3 cc cc cc cc cc cc cc cc cc 48 89 6c 24"));
        if (!HookFunction(addr, (void*)&getCurrentSwingDurationDetour, &oSwingSpeed, xorstr_("Flux"))) {
            return false;
        }
        return true;
    }
};
