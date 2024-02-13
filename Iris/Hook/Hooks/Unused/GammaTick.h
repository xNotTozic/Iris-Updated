#pragma once

void* __o__GammaTick;

void* gammaTickDetour(byte* _this)
{
    void* result1 = CallFunc<void*, void*>(__o__GammaTick, _this);

    return result1; // stops here
}

class GammaTickHook : public FuncHook
{
public:
    static GammaTickHook& Instance()
    {
        static GammaTickHook instance;
        return instance;
    }

    bool Initialize() override
    {
        void* gammaTickAddr = (void*)((uintptr_t)findSig(xorstr_("8B 42 18 48 83 C4 28 C3 E8 ? ? ? ? CC CC CC CC CC 48 83 EC 28 80")) + 18);
        return HookFunction(gammaTickAddr, (void*)&gammaTickDetour, &__o__GammaTick, xorstr_("GammaTick"));
    }
};