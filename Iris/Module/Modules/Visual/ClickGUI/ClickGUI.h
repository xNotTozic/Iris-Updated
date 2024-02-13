#pragma once
#include "IrisGUI.h"
#include "ChronosGUI.h"
#include "ModernGUI.h"

class ClickGUI : public Module
{
public:
    float animation = 0;
    int animationMode = 0; // Ease enum
    int styleMode = 0; // Ease enum
    float animationSpeed = 10.5f; // Ease speed
    int scrollDirection = 0;
    ClickGUI(int keybind = Keyboard::INSERT, bool enabled = false) : Module("ClickGUI", "Visual", "Display all modules", keybind, enabled)
    {
        addEnum("Ease", "The way it zooms in", { "Expo", "Elastic" }, &animationMode);
        addEnum("Style", "The style of ClickGUI", { "Iris" }, &styleMode);
        addSlider("EaseSpeed", "The speed it zooms in", &animationSpeed, 5, 15);
        
        visible_ = false;
        ingameOnly = false;
        callWhenDisabled = true;
    }

    void onEvent(ImGUIRenderEvent* e) override {
        static EasingUtil inEase;
        static IrisGUI irisGUI;
        static ChronosGUI chronosGUI;
        static ModernGUI modernGUI;
        this->isEnabled() ? inEase.incrementPercentage(ImRenderUtil::getDeltaTime() * animationSpeed / 10) 
            : inEase.decrementPercentage(ImRenderUtil::getDeltaTime() * 2 * animationSpeed / 10);
        float inScale = ClickGUIManager::getEaseAnim(inEase, animationMode);
        if (inEase.isPercentageMax()) inScale = 1;
        animation = Math::lerp(0, 1, inEase.easeOutExpo());

        if (animation < 0.0001f) {
            return;
        }
        
        switch (styleMode) {
        case 0: irisGUI.render(animation, inScale, scrollDirection); break;
        case 1: chronosGUI.render(animation, inScale, scrollDirection); break;
        }
    }
    

    void onEnabled() override
    {
        for (auto key : Game::Core::Keymap)
        {
            key.second == true ? CallFunc<void*, __int32, bool>(__o__SendKeyboardKey, key.first, false) : 0;
        }
    }

    void onDisabled() override
    {
        Game::GetInstance()->grabCursor();
    }

    void onEvent(MouseEvent* event) override
    {
        if (!enabled_) return;
        *event->cancelled = true;
    }

    void onEvent(KeyboardEvent* event) override
    {
        if (!enabled_) return;
        __int32 key = *event->Key;
        bool held = *event->Held;

        if (key == VK_ESCAPE && !ClickGUIManager::isBinding && held) {
            this->setEnabled(false);
            Game::GetInstance()->grabCursor();
        }

        *event->cancelled = true;
    }

    void onEvent(MouseScrollEvent* event) override
    {
        if (!enabled_) return;
        bool direction = event->MouseDirection;

        if (!direction) scrollDirection++; else scrollDirection--;
    }

private:
    // Add any additional properties or methods specific to your module here
};