#pragma once

class MouseScrollEvent : public Event
{
public:
    MouseScrollEvent(bool direction)
    {
        MouseDirection = direction;
    }

    EventType getType() const override { return EventType::MouseScroll; }
    bool MouseDirection;
};