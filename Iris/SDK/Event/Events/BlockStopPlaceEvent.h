#pragma once

class BlockStopPlaceEvent : public Event
{
public:
    BlockStopPlaceEvent() { }

    EventType getType() const override { return EventType::StopPlaceBlock; }
};