#pragma once

class Reach : public Module
{
public:
    float reach = 3.f;
    Reach(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Reach", "Combat", "Gives you reach", keybind, enabled)
    {
        addSlider("Range", "The amount of reach you have", &reach, 1.f, 24.f);

        if (targetAddr == nullptr)
        {
            targetAddr = findOffset("00 00 40 40 DB", "Reach");
        }
    }

    void* targetAddr;

    void onEvent(UpdateEvent* event) override
    {
        if (!targetAddr)
            return;

        setFloat(targetAddr, reach);
    }

    void onDisabled() override
    {
        if (!targetAddr)
            return;

        setFloat(targetAddr, 3);
    }
};