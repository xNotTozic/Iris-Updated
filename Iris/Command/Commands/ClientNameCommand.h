#pragma once

class ClientNameCommand : public Command
{
public:

    ClientNameCommand() : Command("clientname", "Set the clients name!", { "cname" })
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        if (cmd.size() < 1)
        {
            ChatUtil::sendMessage("Please enter a name!");
            return false;
        }

        Game::Iris::ClientName = cmd[0];
        ChatUtil::sendMessage(combine("Set client name to ", GRAY, cmd[0], RESET, "!"));

        return false;
    }
};
