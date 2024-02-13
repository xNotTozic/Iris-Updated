#pragma once

class FakeBlock : public Module
{
public:
    FakeBlock(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Animations", "Visual", "Change how you swing", keybind, enabled)
    {
        addEnum("Animation", "Change your swing speed", { "1.7" }, &mode);
        addSlider("Swing Speed", "Change your swing speed", &Game::Core::SwingSpeed, 1, 50);
    }

    int mode = 0;

    bool flux = true;

    void onDisabled() override
    {
        Game::Core::SwingSpeed = 6;
    }

    void onEvent(ViewBobTickEvent* event) override
    {
        glm::mat4& matrix = *event->Matrix;

        if (GetAsyncKeyState(VK_RBUTTON) && Game::GetInstance()->mcGame->canUseMoveKeys() || Game::Iris::ShouldBlock) // RenderUtil::GetCTX()->ClientInstance->mcGame->CanUseKeys
        {
            nopBytes((unsigned char*)fluxSwing, 6);

            matrix = glm::translate<float>(matrix, glm::vec3(0.42222223281, 0.0, -0.16666666269302368));
            matrix = glm::translate<float>(matrix, glm::vec3(-0.1f, 0.15f, -0.2f));
            matrix = glm::translate<float>(matrix, glm::vec3(-0.24F, 0.25f, -0.20F));
            matrix = glm::rotate<float>(matrix, -1.98F, glm::vec3(0.0F, 1.0F, 0.0F));
            matrix = glm::rotate<float>(matrix, 1.30F, glm::vec3(4.0F, 0.0F, 0.0F));
            matrix = glm::rotate<float>(matrix, 60.0F, glm::vec3(0.0F, 1.0F, 0.0F));
        }
        else
        {
            patchBytes((unsigned char*)((uintptr_t)fluxSwing), (unsigned char*)"\x0F\x84\xBD\x04\x00\x00", 6);
        }
    }
};