#pragma once

std::vector<std::string> friends = std::vector<std::string>{};

class FriendCommand : public Command
{
public:
    FriendCommand() : Command("friend", "Whitelist someone for your killaura", { "f", "friends"})
    {}

    bool execute(std::vector<std::string> cmd) override
    {
        if (cmd.size() == 2)
        {
            if (strcmp(cmd[0].c_str(), "add") == 0)
            {
                ChatUtil::sendMessage(combine(GREEN, "Added ", cmd[1], " as a friend!"));

                friends.push_back(cmd[1]);

                return true;
            }

            if (strcmp(cmd[0].c_str(), "remove") == 0)
            {
                bool foundFriend = false;

                for (std::string fried : friends)
                {
                    if (strcmp(fried.c_str(), cmd[1].c_str()) == 0)
                    {
                        foundFriend = true;
                        friends.erase(std::remove(friends.begin(), friends.end(), fried), friends.end());
                    }
                }

                if (foundFriend)
                {
                    ChatUtil::sendMessage(combine(RED, "Removed ", cmd[1], " as a friend!"));
                }
                else
                {
                    ChatUtil::sendMessage(combine(RED, "No friend found by the username ", cmd[1]));
                }
                return true;
            }

            return false;
        }

        if (cmd.size() == 1)
        {
            if (strcmp(cmd[0].c_str(), "list") == 0)
            {
                if (friends.size() > 0)
                {
                    for (std::string fried : friends)
                    {
                        ChatUtil::sendMessage(combine("> ", fried));
                    }
                }
                else
                {
                    ChatUtil::sendMessage("You dont seem to have any friends! add some by typing '.friend add friend1' in chat");
                }
                return true;
            }
        }

        ChatUtil::sendMessage("Invalid argument format. Usage: .friend <add,remove,list> <name>");

        return true;
    }
};
