#pragma once

class ActorTickEvent : public Event
{
public:
    ActorTickEvent(Mob* actor, float* returnvalue)
    {
        Entity = actor;
        ReturnValue = returnvalue;
    }

    EventType getType() const override { return EventType::ActorTick; }
    Mob* Entity;
    float* ReturnValue;
};