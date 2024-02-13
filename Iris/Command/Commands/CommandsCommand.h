#pragma once

class CommandsCommand : public Command
{
public:

    CommandsCommand() : Command("commands", "Get a list of commands", {"cmds", "help"})
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        ChatUtil::sendMessage(combine("Commands (", commandsPtr->size(), ")"));

        for (Command* cmd : *commandsPtr)
        {
            ChatUtil::sendPlainMessage(combine(GRAY, cmd->name, RESET, " - ", cmd->descr));
        }

        return false;
    }
};
