#pragma once

class LevelCommand : public Command
{
public:
    LevelCommand() : Command("level", "Get & Set stuff about the level", { "l", "lvl"})
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        if (cmd.size() == 1)
        {
            if (cmd[0] == "list")
            {
                ChatUtil::sendMessage("> list settime gettime getseed");
            }

            if (cmd[0] == "gettime")
            {
                Player* lp = Game::GetLocalPlayer();
                Level* level = lp->GetLevel();

                ChatUtil::sendMessage(combine(level->GetTime()));
            }

            if (cmd[0] == "getseed")
            {
                Player* lp = Game::GetLocalPlayer();
                Level* level = lp->GetLevel();

                ChatUtil::sendMessage(combine(level->GetSeed()));
            }

            if (cmd[0] == "settime")
            {
                Player* lp = Game::GetLocalPlayer();

                float amount;
                if (!Float_TryParse(amount, cmd[0]))
                {
                    ChatUtil::sendMessage(combine(RED, "Has to be a number!"));
                    return false;
                }

                Level* level = lp->GetLevel();
                level->SetTime(amount);
            }
            return true;
        }

        return false;
    }
};