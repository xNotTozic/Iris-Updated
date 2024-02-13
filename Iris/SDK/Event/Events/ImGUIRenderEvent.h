#pragma once

class ImGUIRenderEvent : public Event
{
public:
    ImGUIRenderEvent()
    {}

    EventType getType() const override { return EventType::ImGUIRender; }
};
