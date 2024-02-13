#pragma once

struct CommandOrigin
{
public:
    CommandOrigin()
    {
        this->origin = 0;
        this->uuid = G_UUID();
        this->playerid = 0;
        *this->string = TextHolder("");
    }

    int origin;
    G_UUID uuid;
    TextHolder* string;
    uintptr_t playerid;
};