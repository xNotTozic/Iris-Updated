#pragma once

void* oUpdateTick;

void onUpdate(__int64* _this) {
    bool cancelled = false;

    PreUpdateTickEvent preEvent{};
    preEvent.cancelled = &cancelled;
    DispatchEvent(&preEvent);

    CallFunc<void*, __int64*>(oUpdateTick, _this);

    UpdateTickEvent event{};
    event.cancelled = &cancelled;
    DispatchEvent(&event);
}

class onUpdateHook : public FuncHook
{
public:
    static onUpdateHook& Instance() {
        static onUpdateHook instance;
        return instance;
    }

    bool Initialize() override
    {
        void* updateTick = findSig(xorstr_("48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ?"));
        // 48 8b c4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8d a8 ? ? ? ? 48 81 ec ? ? ? ? 0f 29 70 ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 85 ? ? ? ? 4c 8b f9 45 33 ed
        // 48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 
        return HookFunction(updateTick, (void*)&onUpdate, &oUpdateTick, xorstr_("Tick"));
    }
};