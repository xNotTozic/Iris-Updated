#pragma once

class ChatUtil
{
public:

	static void sendMessage(std::string message)
	{
		Game::GetLocalPlayer()->DisplayClientMessage(combine(LIGHT_PURPLE, Game::Iris::ClientName, BOLD, " » ", RESET, message).c_str());
	}

	static void sendPlainMessage(std::string message, bool displayArrow = true)
	{
		std::string arrow = displayArrow ? "» " : "";
		Game::GetLocalPlayer()->DisplayClientMessage(combine(LIGHT_PURPLE, arrow, RESET, message).c_str());
	}
};
