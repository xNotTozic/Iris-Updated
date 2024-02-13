#pragma once

class G_UUID
{
public:
    G_UUID()
    {
        this->lower = 0;
        this->upper = 0;
    }

    uintptr_t lower;
    uintptr_t upper;
};