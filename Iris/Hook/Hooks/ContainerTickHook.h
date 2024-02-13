#pragma once

void* __o__ContainerTick;

void* ContainerTickCallback(
    ContainerScreenController* _this
)
{
    bool cancelled = false;

    ContainerTickEvent event{ _this };
    event.cancelled = &cancelled;
    DispatchEvent(&event);

    if (!cancelled)
    {
        return CallFunc<void*, ContainerScreenController*>(__o__ContainerTick, _this);
    }

    return nullptr;
}

class ContainerTickHook : public FuncHook
{
public:
    static ContainerTickHook& Instance()
    {
        static ContainerTickHook instance;
        return instance;
    }

    bool Initialize() override
    {
        void* containerTickAddr = findSig(xorstr_("48 89 5c 24 ? 48 89 6c 24 ? 56 57 41 56 48 83 ec ? 0f 29 74 24 ? 48 8b f1"));
        return HookFunction(containerTickAddr, (void*)&ContainerTickCallback, &__o__ContainerTick, xorstr_("ContainerTick"));
    }
};