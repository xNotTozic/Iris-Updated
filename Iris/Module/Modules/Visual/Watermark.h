#pragma once

class Watermark : public Module
{
public:
    Watermark(int keybind = Keyboard::NONE, bool enabled = true) :
        Module("Watermark", "Visual", "Display the client watermark", keybind, enabled)
    {
        addEnum("Style", "The style of watermark", { "Wave" }, &mode); // , "Exhi"
        addBool("Version", "Show the client version below", &vers);
    }

    int mode = 0;
    bool vers = true;

    void onEvent(ImGUIRenderEvent* event)
    {
        if (getModuleByName("clickgui")->isEnabled()) return;

        pos = pos.animate(Vector2<float>(6.f, 6.f), pos, RenderUtil::getDeltaTime() * 10.f);

        switch (mode)
        {
        case 0:
            ImRenderUtil::drawGradientString(pos, &Game::Iris::ClientName, 2.5f, 1, true, 4, 1, 1, 50);
            if (vers)
                ImRenderUtil::drawGradientString(Vector2<float>(pos.x, pos.y * 7), &Game::Iris::ClientVersion, 1.2f, 1, true, 4, 1, 1, 50);
            break;
        }
    }

    void onEnabled() override
    {
        pos = Vector2<float>(-20, -20);
    }

private:
    Vector2<float> pos = Vector2<float>(-20, -20); //lmao
};