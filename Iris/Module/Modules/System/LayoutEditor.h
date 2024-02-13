#pragma once


class LayoutEditor : public Module
{
public:
    LayoutEditor(int keybind = Keyboard::NONE, bool enabled = false) : Module("LayoutEditor", "Interface", "Edit the clients layout", keybind, enabled)
    {
        MenuToggle(); // allow toggle on menu
        RemoveFromClickgui(); // remove from clickgui
        RemoveFromArraylist(); // hide in arraylist
        RemoveNotifications(); // disable toggle messages
    }

    void onEvent(UpdateEvent* event) override
    {
        //srxfiq can u animate this cuz ur best person

        Vector4<float> screenRect = Vector4<float>(Vector2<float>(0, 0), GuiInfo::ScreenRes);

        RenderUtil::yeemi_fillRectangle(screenRect, UIColor(0, 0, 0), 0.5);

        for (Module* mod : modules)
        {
            if (mod->isEnabled())
            {
                if (mod->getCategory() == "Interface")
                {
                    // interface

                    if (mod->size != Vector2<float>()) // has a module size so we can modify it
                    {
                        RenderUtil::yeemi_fillRectangle(Vector4<float>(mod->location, mod->size), UIColor(0, 0, 0), 0.5);
                    }
                }
            }
        }

        Game::GetInstance()->releaseCursor();
    }

    void onEvent(MouseEvent* event) override
    {
        *event->cancelled = true;
    }

    void onEvent(KeyboardEvent* event) override
    {
        __int32 key = *event->Key;

        if (key == VK_ESCAPE)
            this->toggle();

        *event->cancelled = true;
    }

    void onDisabled() override
    {
        Game::GetInstance()->grabCursor(); // bro has these flipped lmfao
    }
};