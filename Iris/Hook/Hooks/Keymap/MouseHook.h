#pragma once

void MouseDetour(
    void* _this,
    __int8 mouseButton,
    bool isDown,
    __int16 mouseX,
    __int16 mouseY,
    __int16 relX,
    __int16 relY,
    int a8
)
{
    bool cancelled = false;

    if (mouseButton >= 1 && mouseButton <= 4)
    {
        // mouse event
        MouseEvent event{ &mouseButton, &isDown };
        event.cancelled = &cancelled;
        DispatchEvent(&event);

        Util::onMouseClick((int)mouseButton, isDown);

        if (mouseButton == 4)
        {
            MouseScrollEvent event{ isDown < 136 };
            event.cancelled = &cancelled;
            DispatchEvent(&event);
        }
    }

    if (ImGui::GetCurrentContext() != nullptr)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(mouseX, mouseY);

        switch (mouseButton)
        {
        case 1:
            io.MouseDown[0] = isDown;
            break;
        case 2:
            io.MouseDown[1] = isDown;
            break;
        case 3:
            io.MouseDown[2] = isDown;
            break;
        case 4:
            io.MouseWheel = isDown < 0 ? -0.5f : 0.5f; //For scrolling
            break;
        }

        if (io.WantCaptureMouse)
            return;
    }

    if (!cancelled)
    {
        CallFunc<void*, void*, __int8, bool, __int16, __int16, __int16, __int16, char>(
            __o__SendMouseEvent,
            _this,
            mouseButton,
            isDown,
            mouseX,
            mouseY,
            relX,
            relY,
            a8
         );
    }
}