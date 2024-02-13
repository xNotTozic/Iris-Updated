#pragma once

class MouseEvent : public Event
{
public:
    MouseEvent(__int8* key, bool* held)
    {
        Key = key;
        Held = held;
    }

    EventType getType() const override { return EventType::Mouse; }
    __int8* Key;
    bool* Held;
};