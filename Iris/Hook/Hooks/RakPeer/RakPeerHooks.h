#pragma once
void* oNetSkip;

class RakPeerHooks : public FuncHook {
public:
    static __int64 RakPeer_RunUpdateCycle(__int64 _this, __int64 a1) {
        if (Game::Iris::skipTicks) {
            return 0;
        }
        return CallFunc<__int64, __int64, __int64>(oNetSkip, _this, a1);
    }

    static RakPeerHooks& Instance() {
        static RakPeerHooks instance;
        return instance;
    }

    bool Initialize() override {
        void* addr = findSig(xorstr_("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24 ? ? ? ? 0F 29 BC 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B F2 48 89 55 80 4C 8B F9 48"));
        if (!HookFunction(addr, (void*)&RakPeer_RunUpdateCycle, &oNetSkip, xorstr_("RakPeer_RunUpdateCycle"))) {
            return false;
        }

        return true;
    }
};
