#pragma once

class ViewBobTickEvent : public Event
{
public:
    ViewBobTickEvent(glm::mat4* matrix)
    {
        Matrix = matrix;
    }

    EventType getType() const override { return EventType::ViewBobTick; }
    glm::mat4* Matrix;
};