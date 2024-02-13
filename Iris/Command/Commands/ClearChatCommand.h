#pragma once

class ClearChatCommand : public Command
{
public:

    ClearChatCommand() : Command("clearchat", "Clear all chat messages", { "cc", "clearc" })
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        for (int i = 0; i < 0xFF; ++i)
        {
            Game::GetLocalPlayer()->DisplayClientMessage(RESET);
        }

        ChatUtil::sendMessage(combine(GREEN, "Cleared the dirty chat messages"));

        return false;
    }
};
