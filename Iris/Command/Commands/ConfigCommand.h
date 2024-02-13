#pragma once

class ConfigCommand : public Command
{
public:

    ConfigCommand() : Command("config", "Manage your configurations", { "c" })
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        if (cmd.size() == 0)
            return false;

        //.config save
        if (strcmp(cmd[0].c_str(), "save") == 0 || strcmp(cmd[0].c_str(), "s") == 0)
        {
            if (cmd.size() == 2)
            {
                SaveCfg(cmd[1]);
            }
            else
            {
                SaveCfg("default");
            }
        }

        //.config load
        if (strcmp(cmd[0].c_str(), "load") == 0 || strcmp(cmd[0].c_str(), "l") == 0)
        {
            if (cmd.size() == 2)
            {
                LoadConfig(cmd[1]);
                Game::Core::noti.addNotification("Client:", combine("Loaded config ", cmd[1], "!"), 2.f);
            }
            else
            {
                LoadConfig("default");
            }
        }

        return false;
    }

    void SaveCfg(std::string cfg)
    {
        SaveConfig(cfg);
        ChatUtil::sendMessage(combine("Successfully saved config ", GRAY, cfg.c_str(), RESET, "!"));
        Game::Core::noti.addNotification("Client:", combine("Saved config ", cfg.c_str(), "!"), 2.f);
    }
};
