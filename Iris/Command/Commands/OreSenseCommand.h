#pragma once

std::vector<std::string> oreSenseTiles = std::vector<std::string>{
    "tile.diamond_ore",
    "tile.deepslate_diamond_ore",
    "tile.chest"
};

class OreSenseCommand : public Command
{
public:
    OreSenseCommand() : Command("oresense", "Change what OreSense highlights", { "ores", "osense", "os" })
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        if (cmd.size() == 1)
        {
            if (cmd[0] == "list")
            {
                for (std::string tile : oreSenseTiles)
                {
                    ChatUtil::sendMessage("Warning: Tile names are case sensitive!");
                    ChatUtil::sendMessage(combine("> ", tile));
                }
            }
            return true;
        }

        if (cmd.size() == 2)
        {
            if (cmd[0] == "add")
            {
                for (std::string tile : oreSenseTiles)
                {
                    if (tile == cmd[1])
                    {
                        ChatUtil::sendMessage(combine(RED, "This is already being highlighted!"));
                        return false;
                    }
                }

                oreSenseTiles.push_back(cmd[1]);
                ChatUtil::sendMessage(combine(GREEN, cmd[1], " is now being highlighted"));
            }

            if (cmd[0] == "remove")
            {
                for (std::string tile : oreSenseTiles)
                {
                    if (tile == cmd[1])
                    {
                        oreSenseTiles.erase(std::remove(oreSenseTiles.begin(), oreSenseTiles.end(), tile), oreSenseTiles.end());
                        ChatUtil::sendMessage(combine(GREEN, cmd[1], " is no longer being highlighted"));
                        return true;
                    }
                }

                ChatUtil::sendMessage(combine(RED, "This is not something thats highlighted"));
            }

            return true;
        }

        ChatUtil::sendMessage("Invalid argument format. Usage: .oresense <add,remove,list> <tilename>");

        return false;
    }
};