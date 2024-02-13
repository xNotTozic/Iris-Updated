#pragma once

class BeforeUpdateEvent : public Event
{
public:
    BeforeUpdateEvent(MinecraftUIRenderContext* context, ScreenView* guilayer)
    {
        Context = context;
        GuiLayer = guilayer;
    }

    EventType getType() const override { return EventType::BeforeUpdate; }
    MinecraftUIRenderContext* Context;
    ScreenView* GuiLayer;
};