#pragma once

class DebuggerCommand : public Command
{
public:
    DebuggerCommand() : Command("debug", "Activate inbuilt & custom debug utilities", { "debugger", "dbg", "d" })
    {}

    bool execute(std::vector<std::string> cmd) override // I'll actually put effort into this after I finish oresense commands
    {
        if (cmd.size() == 1)
        {
            if (cmd[0] == "list")
            {
                ChatUtil::sendMessage("> inspectelement, showelements, imguiutils");
            }

            if (cmd[0] == "inspectelement")
            {
                bool* insptElmt = Game::GetInspecter()->GetFocusInspect();

                *insptElmt = !*insptElmt;
            }

            if (cmd[0] == "showelements")
            {
                bool* allInspt = Game::GetInspecter()->GetAllInspect();

                *allInspt = !*allInspt;
            }

            if (cmd[0] == "imguiutils")
            {
                g_debugMode = !g_debugMode;
            }
        }

        return false;
    }
};