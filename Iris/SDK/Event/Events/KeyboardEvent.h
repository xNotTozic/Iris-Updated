#pragma once

class KeyboardEvent : public Event
{
public:
    KeyboardEvent(__int32* key, bool* held)
    {
        Key = key;
        Held = held;
    }

    EventType getType() const override { return EventType::_Keyboard; }
    __int32* Key;
    bool* Held;
};