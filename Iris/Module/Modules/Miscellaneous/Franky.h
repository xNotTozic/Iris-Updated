#pragma once

class Franky : public Module
{
public:
    Franky(int keybind = Keyboard::NONE, bool enabled = false) :
        Module("Franky", "Misc", "It does exactly what you think it does", keybind, enabled)
    {}
};
