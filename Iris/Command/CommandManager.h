#pragma once

#include "Commands/BindCommand.h"
#include "Commands/TeleportCommand.h"
#include "Commands/TopCommand.h"
#include "Commands/CommandsCommand.h"
#include "Commands/ClearChatCommand.h"
#include "Commands/ClientNameCommand.h"
#include "Commands/UnbindAllCommand.h"
#include "Commands/ClientThemeCommand.h"
#include "Commands/MoveBindCommand.h"
#include "Commands/ConfigCommand.h"
#include "Commands/FriendCommand.h"
#include "Commands/PlayerTeleportCommand.h"
#include "Commands/ToCommand.h"
#include "Commands/OreSenseCommand.h"
#include "Commands/DiscordCommand.h"
#include "Commands/DebuggerCommand.h"
#include "Commands/ExpCommand.h"
#include "Commands/LevelCommand.h"

// debug stuff
#include "Commands/TestCommand.h"

// lol

class CommandManager
{
public:
	void InitCommands()
	{
		commandsPtr = &commands; // fuck u srxfiq

		/*
		
		.compass (no cuz gui)
		.nick (streamner mode yk?)
		.home (set/delete/goto/list) (home)
		.discord
		.spawn (teleport to world spawn)
		
		*/

		commands.push_back(new CommandsCommand());
		commands.push_back(new BindCommand());
		commands.push_back(new TeleportCommand());
		commands.push_back(new TopCommand());
		commands.push_back(new ClearChatCommand());
		commands.push_back(new ClientNameCommand());
		commands.push_back(new UnbindAllCommand());
		commands.push_back(new ClientThemeCommand());
		commands.push_back(new MoveBindCommand());
		commands.push_back(new ConfigCommand());
		commands.push_back(new FriendCommand());
		commands.push_back(new PlayerTeleportCommand());
        commands.push_back(new ToCommand());
        commands.push_back(new OreSenseCommand());
        commands.push_back(new DiscordCommand());
        commands.push_back(new DebuggerCommand());
        commands.push_back(new ExpCommand());
        commands.push_back(new LevelCommand());

#if _DEBUG
        commands.push_back(new TestCommand());
#endif // _DEBUG


		std::cout << "[" << Game::Iris::ClientName << " " << Game::Iris::ClientVersion << "] Initialized commands" << std::endl << std::endl;
	}

	~CommandManager()
	{
		for (auto cmd : commands)
			delete cmd;
	}

    bool sendCommand(const std::string& command)
    {
        Command* cur = nullptr;

        if (command.length() < 2)
            return true;

        std::string argString = command.substr(1);
        std::string commandName = "";
        std::vector<std::string> arguments = turnToVec(argString, commandName);

        for (auto cmd : commands)
        {
            if (cmd->name == commandName)
            {
                cur = cmd;
                break;
            }

            for (const auto& alias : cmd->aliases)
            {
                if (alias == commandName)
                {
                    cur = cmd;
                    break;
                }
            }
        }

        if (!cur)
        {
            ChatUtil::sendMessage(xorstr_("Invalid Command!"));
            return true;
        }

        cur->execute(arguments);

        return true;
    }

    std::vector<Command*> commands;

private:
    std::vector<std::string> turnToVec(std::string str, std::string& commandName)
    {
        std::vector<std::string> ret;
        size_t pos = 0;
        bool inQuotes = false;

        while (pos < str.length())
        {
            if (str[pos] == '"')
            {
                inQuotes = !inQuotes;
                pos++;
                continue;
            }

            if (!inQuotes && str[pos] == ' ')
            {
                pos++;
                continue;
            }

            size_t start = pos;
            if (inQuotes)
            {
                pos = str.find('"', pos);
                if (pos == std::string::npos)
                    break;
            }
            else
            {
                pos = str.find(' ', pos);
                if (pos == std::string::npos)
                    pos = str.length();
            }

            std::string arg = str.substr(start, pos - start);
            ret.push_back(arg);
            pos++;
        }

        if (ret.size())
        {
            commandName = ret[0];
            std::transform(commandName.begin(), commandName.end(), commandName.begin(), tolower);
            ret.erase(ret.begin());
        }

        return ret;
    }
};