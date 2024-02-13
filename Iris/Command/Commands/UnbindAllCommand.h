#pragma once

class UnbindAllCommand : public Command
{
public:

    UnbindAllCommand() : Command("unbindall", "Unbind all module binds", { "" })
    {}

    bool execute(std::vector<std::string> cmd) override // bro has no error handling with chat messages imagineeee
    {
        for (auto mod : modules)
        {
            if (!mod) return false;
            mod->setKeybind(0);
        }

        ChatUtil::sendMessage("Unbound all modules!");

        return false;
    }
};
