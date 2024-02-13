#pragma once

class ViewBobbing : public Module
{
public:
    ViewBobbing(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("ViewBobbing", "Visual", "Change your view bobbing (Requires ViewBobbing to be enabled.)", keybind, enabled)
    {
        addEnum("Mode", "", { "Normal", "Meme", "None" }, &mode);
        addSlider("Amount", "", &viewBobAmount, -1, 1);
    }

    float viewBobAmount = 0.3;
    int mode = 0;

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetLocalPlayer())
            return;

        switch (mode)
        {
        case 0:
            break;
        case 1:
            Game::GetLocalPlayer()->getMovementProxy()->setBob(viewBobAmount);
            break;
        case 2:
            Game::GetLocalPlayer()->getMovementProxy()->setBob(0);
            break;
        }
    }
};