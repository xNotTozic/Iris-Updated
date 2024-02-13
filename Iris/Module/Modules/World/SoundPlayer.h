#pragma once

class SoundPlayer : public Module
{
public:
    SoundPlayer(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("SoundPlayer", "World", "funny soundplayer lol", keybind, enabled)
    {
    }

    float radius = 3;
    int type = 0;

    void onEvent(UpdateEvent* event) override
    {
        Player* player = Game::GetLocalPlayer();

        if (!player)
            return;


    }
};