#pragma once

class NoHurtcam : public Module
{
public:
    NoHurtcam(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("NoHurtcam", "Visual", "Remove the hurt camera effect", keybind, enabled)
    {}

    void onEvent(HurtcamEvent* event) override
    {
        if (event->Entity->isLocalPlayer())
        {
            *event->cancelled = true;
        }
    }
};