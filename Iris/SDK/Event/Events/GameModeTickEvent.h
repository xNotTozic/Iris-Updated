#pragma once

class GameModeTickEvent : public Event
{
public:
    GameModeTickEvent(GameMode* gm)
    {
        this->gameMode = gm;
    }

    EventType getType() const override { return EventType::GameModeTick; }
    GameMode* gameMode;
};