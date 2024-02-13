#pragma once

class LayerUpdateEvent : public Event
{
public:
    LayerUpdateEvent(ScreenView* guilayer)
    {
        GuiLayer = guilayer;
    }

    EventType getType() const override { return EventType::LayerUpdate; }
    ScreenView* GuiLayer;
};