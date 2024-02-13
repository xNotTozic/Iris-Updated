#pragma once

void* __o__ViewbobHook;
void* fluxSwing;

void BobHurtCallback(
    uint64_t _this,
    glm::mat4* matrix
)
{
    bool cancelled = false;

    ViewBobTickEvent event{ matrix };
    event.cancelled = &cancelled;
    DispatchEvent(&event);

    if (not cancelled)
    {
        return CallFunc<void, uint64_t, glm::mat4*>(
            __o__ViewbobHook,
            _this,
            matrix
        );
    }

    return;
}

class ViewbobHook : public FuncHook
{
public:
    static ViewbobHook& Instance()
    {
        static ViewbobHook instance;
        return instance;
    }

    bool Initialize() override // 0F 84 BD 04 00 00
    {
        void* viewbobAddr = findSig(xorstr_("40 53 56 48 83 EC 78 ? ? 7C"));
        fluxSwing = (void*)findOffset(xorstr_("0f 84 ? ? ? ? 48 8b 46 ? 48 85 c0 74 ? 48 8b 08 48 85 c9 74 ? 44 0f b6 69"), xorstr_("FluxSwing"));
        return HookFunction(viewbobAddr, (void*)&BobHurtCallback, &__o__ViewbobHook, xorstr_("BobHurt"));
    }
};
