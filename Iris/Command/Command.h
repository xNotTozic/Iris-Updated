#pragma once

class Command
{
public:
	Command(std::string commandName, std::string descr, std::vector<std::string> aliases = std::vector<std::string>())
		: name(commandName), descr(descr), aliases(aliases)
	{}

	virtual bool execute(std::vector<std::string> cmd) { return false; }

	std::string name = "";
	std::string descr = "";
	std::vector<std::string> aliases;
};

std::vector<Command*>* commandsPtr = nullptr;