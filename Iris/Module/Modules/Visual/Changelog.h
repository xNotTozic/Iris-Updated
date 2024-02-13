#pragma once

class Changelog : public Module
{
public:
    
    float percentage = 0;

    Changelog(int keybind = Keyboard::NONE, bool enabled = true) :
        Module("Changelog", "Visual", "Shows changes about the client", keybind, enabled)
    {}
    ParticleEngine particleMgr;
    void onEvent(ImGUIRenderEvent* event) override
    {
        static std::string added = "[+] ";
        static std::string removed = "[-] ";
        static std::string changed = "[*] ";

        static std::string tip = "Press ESC to discard";

        static std::vector<std::string> logs = 
        {

        };

        Vector2<float> res = ImRenderUtil::getScreenSize();
        static bool hasShown = false;
        if (!hasShown)
        {
            particleMgr.addParticles(25, res.x / 2, res.y / 2, 20, 3);
            hasShown = true;
        }

        Game::GetInstance()->releaseCursor();

        static EasingUtil easing;

        static float textSize = 0.f;
        const float lineHeight = ImRenderUtil::getTextHeight(textSize);
        static float opacity = 0.f;

        float totalHeight = 0.f;
        float maxWidth = 0.f;

        percentage += RenderUtil::getDeltaTime();
        easing.percentage = percentage;
        percentage = std::clamp(percentage, 0.f, 1.f);

        textSize = Math::lerp(0, 1.2f, easing.easeOutElastic());
        opacity = Math::lerp(0, 1.f, easing.easeOutExpo());

        // Draw a background
        ImRenderUtil::fillRectangle(Vector4<float>(0, 0, res.x, res.y), UIColor(0, 0, 0), 0.6f * opacity);

        for (auto& line : logs) 
        {
            totalHeight += lineHeight;
            maxWidth = std::max(maxWidth, ImRenderUtil::getTextWidth(&line, textSize));
        }

        Vector2<float> textPos = Vector2<float>(res.x / 2.f, res.y / 2.f - totalHeight / 2.f);

        for (auto& line : logs)
        {
            Vector2<float> linePos = textPos + Vector2<float>(-maxWidth / 2.f, 0.f);
            ImRenderUtil::drawText(linePos, &line, UIColor(255,255,255), textSize, opacity, true);
            textPos.y += lineHeight;
        }

        Vector2<float> tipPos = Vector2<float>(res.x / 2 - ImRenderUtil::getTextWidth(&tip, 1.f) / 2, -15).lerp(Vector2<float>(res.x / 2 - ImRenderUtil::getTextWidth(&tip, 1.f) / 2, 5), easing.easeOutExpo());
        ImRenderUtil::drawText(tipPos, & tip, UIColor(150, 150, 150), 1.f, opacity, true);

        particleMgr.drawParticles();
        particleMgr.updateParticles(RenderUtil::getDeltaTime() * 2);
    }

    void onEnabled() override
    {
        particleMgr.addParticles(25, ImRenderUtil::getScreenSize().x / 2, ImRenderUtil::getScreenSize().y / 2, 20, 3);
        percentage = 0;
        getModuleByName("clickgui")->setEnabled(false);
    }

    void onDisabled() override
    {
        particleMgr.clearParticles();
        if (Game::Core::HudScreen)
            Game::GetInstance()->grabCursor();
    }

    void onEvent(KeyboardEvent* event) override
    {
        __int32 key = *event->Key;
        bool held = *event->Held;

        if (key == VK_ESCAPE)
            this->toggle();

        *event->cancelled = true;
    }

    void onEvent(MouseEvent* event) override
    {
        *event->cancelled = true;
    }
};