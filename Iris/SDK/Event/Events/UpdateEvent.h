#pragma once

class UpdateEvent : public Event
{
public:
    UpdateEvent(MinecraftUIRenderContext* context, ScreenView* guilayer)
    {
        Context = context;
        GuiLayer = guilayer;
    }

    EventType getType() const override { return EventType::Update; }
    MinecraftUIRenderContext* Context;
    ScreenView* GuiLayer;
};