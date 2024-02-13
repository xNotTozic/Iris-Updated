#pragma once

class BlockPlaceEvent : public Event
{
public:
    BlockPlaceEvent(Vector3<int> blockPos, int blockFace)
    {
        PlacePos = blockPos;
        BlockFace = blockFace;
    }

    EventType getType() const override { return EventType::PlaceBlock; }
    Vector3<int> PlacePos;
    int BlockFace;
};