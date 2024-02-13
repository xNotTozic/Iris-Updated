#pragma once

class BlockReach : public Module
{
public:
    BlockReach(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("BlockReach", "Player", "Change the range you can place blocks", keybind, enabled)
    {
        addSlider("Range", "The amount of block reach you have", &reach, 7.f, 255.f);
    }

    float reach = 7;

    void onEvent(GetPickRangeEvent* event) override
    {
        *event->ReturnValue = reach;
    }
};