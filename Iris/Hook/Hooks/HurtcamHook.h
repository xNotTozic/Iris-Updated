#pragma once

#include "../../SDK/GameCore/Game/ClientInstance/Actor/Actor.h"

void* __o__CauseHurtcam;

float CauseHurtcamDetour(
    Player* _this,
    __int64 a2
)
{
    bool cancelled = false;

    HurtcamEvent event{ _this };
    event.cancelled = &cancelled;
    DispatchEvent(&event);

    if (!cancelled)
    {
        return CallFunc<float, Player*, __int64>(
            __o__CauseHurtcam,
            _this,
            a2
        );
    }

    return 0;
}

class HurtcamHook : public FuncHook
{
public:
    static HurtcamHook& Instance()
    {
        static HurtcamHook instance;
        return instance;
    }

    bool Initialize() override
    {
        void* hurtcamAddr = findSig(xorstr_("40 53 55 57 48 83 EC 50 41"));
        return HookFunction(hurtcamAddr, (void*)&CauseHurtcamDetour, &__o__CauseHurtcam, xorstr_("CauseHurtcam"));
    }
};