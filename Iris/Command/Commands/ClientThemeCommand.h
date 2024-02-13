#pragma once

class ClientThemeCommand : public Command
{
public:

    ClientThemeCommand() : Command("theme", "Set the clients theme!", { "style" })
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        if (cmd.size() < 1)
        {
            ChatUtil::sendMessage(combine("Please specify a theme! ", GRAY, BOLD, ".theme list",RESET, GRAY," for all themes",RESET,"!"));
            return false;
        }

        if (Game::Iris::commands.find(cmd[0]) != Game::Iris::commands.end())
        {
            Game::Iris::ClientColor = Game::Iris::commands.find(cmd[0])->second;
            ChatUtil::sendMessage(combine("Set the color to ", GRAY, cmd[0], RESET, "!"));
            return true;
        }

        if (cmd[0] == "list")
        {
            ChatUtil::sendMessage("List of themes!");
            for (auto& themes : Game::Iris::commands)
            {
                std::string themeName = themes.first;
                themeName[0] = std::toupper(themeName[0]);
                ChatUtil::sendPlainMessage(combine(GRAY, themeName), true);
            }
            return true;
        }

        ChatUtil::sendMessage(combine("Please specify a theme! ", GRAY, BOLD, ".theme list", RESET, GRAY, " for all themes", RESET, "!"));
        return false;
    }
};
