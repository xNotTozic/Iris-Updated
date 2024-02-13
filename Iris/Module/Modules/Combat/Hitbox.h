#pragma once

class Hitbox : public Module
{
public:
    Hitbox(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Hitbox", "Combat", "Expand entities hitboxes", keybind, enabled)
    {
        addSlider("Width", "The width of the hitboxes", &hitboxWidth, 0.1f, 7);
        addSlider("Height", "The height of the hitboxes", &hitboxHeight, 0.1f, 7);

        ingameOnly = true;
    }

    float hitboxWidth = 0.6f;
    float hitboxHeight = 1.8f;

    void onEvent(ActorTickEvent* event) override
    {
        /*if (!event->Entity || event->Entity == Game::GetLocalPlayer())
            return;

        if (getModuleByName("AntiBot")->isEnabled())
        {
            if (event->Entity->isBot())
                return;
        }

        AABBShapeComponent* shape = event->Entity->try_get<AABBShapeComponent>();

        if (!shape)
            return;

        shape->r_Hitbox.x = hitboxWidth;
        shape->r_Hitbox.y = hitboxHeight;*/
    }
};