#pragma once

class TeleportCommand : public Command
{
public:
    TeleportCommand() : Command("teleport", "Teleport to something without OP", { "tp" })
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        if (cmd.size() != 4)
        {
            if (cmd.size() == 1 && strcmp(cmd[0].c_str(), "list") == 0)
            {
                ChatUtil::sendMessage(combine("vanilla, list, lifeboat"));
            }

            ChatUtil::sendMessage("Invalid argument format. Usage: .teleport <type> <X> <Y> <Z> - .teleport list");
            return false;
        }

        if (!Game::GetLocalPlayer())
            return false;

        Player* player = Game::GetLocalPlayer();

        Vector3<float> pos;

        if (!Float_TryParse(pos.x, cmd[1]) || !Float_TryParse(pos.y, cmd[2]) || !Float_TryParse(pos.z, cmd[3]))
        {
            ChatUtil::sendMessage("Invalid argument format. Usage: .teleport <type> <X> <Y> <Z>");
            return false;
        }

        if (strcmp(cmd[0].c_str(), "vanilla") == 0)
        {
            player->TeleportTo(pos);
            ChatUtil::sendMessage(combine("Teleported to ", GRAY, pos.x, ", ", pos.y, ", ", pos.z, RESET, "!"));
        }

        if (strcmp(cmd[0].c_str(), "lifeboat") == 0)
        {
            if (lifeboatTpTarget == Vector3<float>(0, 0, 0))
            {
                lifeboatTpTarget = pos; // handled by LifeboatActionTick.h in misc modules
                Game::GetInstance()->getMinecraft()->setTimerSpeed(30);
                getModuleByName("LifeboatTickAction")->setEnabled(true);

                ChatUtil::sendMessage(combine("Teleported to ", GRAY, pos.x, ", ", pos.y, ", ", pos.z, RESET, "!"));
            }
            else
            {
                ChatUtil::sendMessage(combine(RED, "Teleport already in progress!"));
            }
        }

        return true;
    }
};
