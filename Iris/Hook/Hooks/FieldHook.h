#pragma once

#include "../../SDK/GameCore/Game/ClientInstance/Actor/Actor.h"

void* __o__FieldHook;

void* FieldDetour(
    void* a1,
    void* a2,
    void* a3,
    void* a4,
    float* a5
)
{
    float* fieldMulti = reinterpret_cast<float*>((uintptr_t)a1 + 0x1350);

    if (Game::Core::ApplyField)
    {
        *fieldMulti = Game::Core::FieldMultiplier; // default is 1.1f (idky lol)
    }

    return CallFunc<void*, void*, void*, void*, void*, float*>(
        __o__FieldHook,
        a1,
        a2,
        a3,
        a4,
        a5
    );
}

class FieldHook : public FuncHook
{
public:
    static FieldHook& Instance()
    {
        static FieldHook instance;
        return instance;
    }

    bool Initialize() override
    {
        void* fieldAddr = findSig(xorstr_("48 89 5C 24 18 56 48 83 EC 60 ? ? 74"));
        return HookFunction(fieldAddr, (void*)&FieldDetour, &__o__FieldHook, xorstr_("FieldHook"));
    }
};