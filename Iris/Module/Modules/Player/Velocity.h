#pragma once

class Velocity : public Module
{
public:
    Velocity(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Velocity", "Player", "Change your knockback", keybind, enabled)
    {
        addSlider("Vertical", "Modify your Vertical KB", &y, 0, 1);
        addSlider("Horizontal", "Modify your Horizontal KB", &x, 0, 1);
    }

    float x = 0;
    float y = 0;

    void onEvent(LerpMotionEvent* event) override
    {
        Vector3<float>* motion = event->Motion;
        StateVectorComponent* stateVector = event->Actor->try_get<StateVectorComponent>();

        if (!stateVector) {
            return;
        }

        motion->x *= x;
        motion->y *= y;
        motion->z *= x;

        *motion = stateVector->r_Velocity.lerp(*motion, x, y, x);
    }


    std::string getModeName() override
    {
        std::ostringstream oss;
        oss.precision(2);
        oss << " H: " << std::fixed << x << " V: " << std::fixed << y;
        return oss.str();
    }
};