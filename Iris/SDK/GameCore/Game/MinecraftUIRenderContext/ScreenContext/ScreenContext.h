#pragma once

#include "Tessellator/Tessellator.h"

class ScreenContext {
public:
    inline float* getColorHolder() {
        return *reinterpret_cast<float**>((uintptr_t)(this) + 0x30);
    }

    inline Tessellator* getTessellator() {
        return *reinterpret_cast<Tessellator**>((uintptr_t)(this) + 0xC0); // Updated to 1.20.51
        // The same offset in 1.20.0.1
    }
};