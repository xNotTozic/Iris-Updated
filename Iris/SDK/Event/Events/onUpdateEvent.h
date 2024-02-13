#pragma once

class UpdateTickEvent : public Event
{
public:
    UpdateTickEvent() {}

    EventType getType() const override { return EventType::UpdateTick; }
};

class PreUpdateTickEvent : public Event
{
public:
    PreUpdateTickEvent() {}

    EventType getType() const override { return EventType::PreUpdateTick; }
};