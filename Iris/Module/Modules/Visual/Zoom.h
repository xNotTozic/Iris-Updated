#pragma once

class Zoom : public Module
{
public:
    Zoom(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Zoom", "Visual", "Zoom in when you hold 'C'", keybind, enabled)
    {
        //addBool("EaseOut", "Ease back to default when disabled", &Game::Core::ApplyFieldEase);
        addSlider("Multiplier", "The amount of zoom", &zoomzoomlol, 0, 1);
    }

    float zoomzoomlol = 0.8f;
    bool ease = false;

    void onEvent(ViewBobTickEvent* event) override
    {
        if (!RenderingGameMenus)
        {
            *event->Matrix = glm::translate(*event->Matrix, { 0xff, 0xff, 0xff });
        }
    }

    void onEvent(UpdateEvent* event) override
    {
        if (Game::Core::Keymap['V'] && Game::GetInstance()->mcGame->canUseMoveKeys()) 
        {
            RenderingGameMenus = false;
            Game::Core::SetFieldMulti(1.1 - zoomzoomlol);
        }
        else
        {
            RenderingGameMenus = true;
            Game::Core::ResetFieldMulti();
        }
    }
};