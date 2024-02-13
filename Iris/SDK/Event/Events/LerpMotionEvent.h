#pragma once

class LerpMotionEvent : public Event
{
public:
    LerpMotionEvent(Player* act, Vector3<float>* motion)
    {
        Motion = motion;
        Actor = act;
    }

    EventType getType() const override { return EventType::LerpMotion; }
    Vector3<float>* Motion;
    Player* Actor;
};