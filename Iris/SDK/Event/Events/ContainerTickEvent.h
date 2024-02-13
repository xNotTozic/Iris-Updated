#pragma once

class ContainerTickEvent : public Event
{
public:
    ContainerTickEvent(ContainerScreenController* controller)
    {
        Controller = controller;
    }

    EventType getType() const override { return EventType::ContainerTick; }
    ContainerScreenController* Controller;
};