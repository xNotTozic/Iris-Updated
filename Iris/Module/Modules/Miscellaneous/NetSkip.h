#pragma once

class NetSkip : public Module
{
public:
    float delay = 500.f;
    NetSkip(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("NetSkip", "Misc", "Skip network ticks", keybind, enabled)
    {
        addSlider("Delay", "Delay to wait before resending packets", &delay, 0.f, 2000);
    }

    void onEvent(UpdateTickEvent* event) {
        static auto lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count() < delay) {
            Game::Iris::skipTicks = true;
        }
        else {
            Game::Iris::skipTicks = false;
            lastTime = std::chrono::high_resolution_clock::now();
        }
    }
    void onDisabled() override {
        Game::Iris::skipTicks = false;
    }
};
