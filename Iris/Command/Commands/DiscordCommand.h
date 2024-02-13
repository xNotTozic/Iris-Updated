#pragma once

class DiscordCommand : public Command
{
public:
	DiscordCommand() : Command("discord", "Sends the iris discord invite into your chat", {})
	{}

	bool execute(std::vector<std::string> cmd) override
	{
		Util::setClipboardText("https://discord.gg/3Da9HakJam");
		ChatUtil::sendMessage("Copied invite to clipboard!");

		return true;
	}
};
