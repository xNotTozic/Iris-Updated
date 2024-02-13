#pragma once

class MoveBindCommand : public Command
{
public:

    MoveBindCommand() : Command("movebind", "Rebind the movement input keys from 'WASD'", { "mb" })
    {}

    bool execute(std::vector<std::string> cmd) override // bro has no error handling with chat messages imagineeee
    {
        if (cmd.size() < 1)
            return false;

        GameInput::SetKeybinds(cmd[0].c_str());

        return false;
    }
};
