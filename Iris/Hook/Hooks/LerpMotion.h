#pragma once

void* __o__lerpMotion;

void lerpMotionDetour(Player* _this, Vector3<float>* vel)
{
    static void* velReceive = nullptr;
    if (!velReceive) velReceive = (void*)findSig(xorstr_("C6 46 11 ? 48 8B ? ? ? 48 83 C4 ? 5E C3 CC"));

    bool cancelled = false;

    LerpMotionEvent event{ _this, vel };
    event.cancelled = &cancelled;
    if (Game::GetLocalPlayer() && _this == Game::GetLocalPlayer() && velReceive == _ReturnAddress()) {
        DispatchEvent(&event);
    }

    if (!cancelled)
    {
        CallFunc<void*, Player*, Vector3<float>*>(__o__lerpMotion, _this, vel);
    }
}

// util (not a hook)
void LerpEntity(Player* entity, Vector3<float> vel)
{
    CallFunc<void*, Player*, Vector3<float>*>(
        __o__lerpMotion,
        entity,
        &vel
    );
}

class LerpMotionHook : public FuncHook
{
public:
    bool Initialize() override
    {
        void* lerpMot = findSig(xorstr_("48 83 EC 28 4C 8B 81 ? ? ? ? 4D 85 C0 74 19 8B 02 41 89 40 18"));

        if (not HookFunction(lerpMot, (void*)&lerpMotionDetour, &__o__lerpMotion, xorstr_("LerpMotion")))
            return false;

        return true;
    }

    static LerpMotionHook& Instance()
    {
        static LerpMotionHook instance;
        return instance;
    }
};