#pragma once

class BlockContinuePlaceEvent : public Event
{
public:
    BlockContinuePlaceEvent(Vector3<int> blockPos, int blockFace)
    {
        PlacePos = blockPos;
        BlockFace = blockFace;
    }

    EventType getType() const override { return EventType::ContinuePlaceBlock; }
    Vector3<int> PlacePos;
    int BlockFace;
};