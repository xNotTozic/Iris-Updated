#pragma once

class CameraHooks : public FuncHook {
public:
    static inline void* oCameraAvoidanceSystemUtil_tick;
    static void CameraAvoidanceSystemUtil_tick(__int64 _this, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6) {

        if (!true) { // when nocamera clip module enabeld yes yes
            CallFunc<void, __int64, __int64, __int64, __int64, __int64, __int64>(oCameraAvoidanceSystemUtil_tick, _this, a2, a3, a4, a5, a6);
        }
    }

    static CameraHooks& Instance() {
        static CameraHooks instance;
        return instance;
    }

    bool Initialize() override {
        void* addr = findSig(xorstr_("40 55 53 56 57 41 56 48 8D 6C 24 ?? 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 ?? 49 83 38"));
        if (!HookFunction(addr, (void*)&CameraAvoidanceSystemUtil_tick, &oCameraAvoidanceSystemUtil_tick, xorstr_("CameraAvoidanceSystemUtil_tick"))) {
            return false;
        }

        return true;
    }
};
