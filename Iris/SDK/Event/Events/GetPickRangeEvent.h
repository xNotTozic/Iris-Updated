#pragma once

class GetPickRangeEvent : public Event
{
public:
    GetPickRangeEvent(GameMode* gameMode, float* returnValue)
    {
        GameMode = gameMode;
        ReturnValue = returnValue;
    }

    EventType getType() const override { return EventType::GetPickRange; }
    GameMode* GameMode;
    float* ReturnValue;
};