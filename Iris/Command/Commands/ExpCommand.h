#pragma once

class ExpCommand : public Command
{
public:
    ExpCommand() : Command("exp", "Give yourself levels using packets", { "xp" })
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        if (cmd.size() == 1)
        {
            Player* lp = Game::GetLocalPlayer();

            float amount;
            if (!Float_TryParse(amount, cmd[0]))
            {
                ChatUtil::sendMessage(combine(RED, "Has to be a number!"));
                return false;
            }

            lp->addLevels(amount);
            return true;
        }

        return false;
    }
};