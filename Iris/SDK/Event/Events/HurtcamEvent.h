#pragma once

class HurtcamEvent : public Event
{
public:
    HurtcamEvent(Player* actor)
    {
        Entity = actor;
    }

    EventType getType() const override { return EventType::Hurtcam; }
    Player* Entity;
};