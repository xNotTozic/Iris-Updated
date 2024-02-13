#pragma once

class Timer : public Module
{
public:
    Timer(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Timer", "World", "Changes the games Internal timer", keybind, enabled)
    {
        addSlider("Speed", "The games speed", &timerSpeed, 0, 60);
    }

    float timerSpeed = 20;

    void onEvent(UpdateEvent* event) override
    {
        if (!Game::GetInstance())
            return;

        if (!Game::GetInstance()->getMinecraft())
            return;

        Game::GetInstance()->getMinecraft()->setTimerSpeed(timerSpeed);
    }

    void onDisabled() override
    {
        if (!Game::GetInstance())
            return;

        if (!Game::GetInstance()->getMinecraft())
            return;

        Game::GetInstance()->getMinecraft()->setTimerSpeed(20);
    }

    std::string getModeName() override
    {
        char str[10];
        sprintf_s(str, 10, "%.0f", timerSpeed);
        return " " + std::string(str);
    }
};