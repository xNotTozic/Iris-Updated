#pragma once

const char* const keyNames[] =
{
    "Unknown",
"VK_LBUTTON",
"VK_RBUTTON",
"VK_CANCEL",
"VK_MBUTTON",
"VK_XBUTTON1",
"VK_XBUTTON2",
"Unknown",
"VK_BACK",
"TAB",
"Unknown",
"Unknown",
"VK_CLEAR",
"RETURN",
"Unknown",
"Unknown",
"Shift",
"CTRL",
"VK_MENU",
"VK_PAUSE",
"VK_CAPITAL",
"VK_KANA",
"Unknown",
"VK_JUNJA",
"VK_FINAL",
"VK_KANJI",
"Unknown",
"ESCAPE",
"VK_CONVERT",
"VK_NONCONVERT",
"VK_ACCEPT",
"VK_MODECHANGE",
"SPACE",
"PRIOR",
"NEXT",
"END",
"HOME",
"LEFT",
"UP",
"RIGHT",
"DOWN",
"VK_SELECT",
"VK_PRINT",
"VK_EXECUTE",
"VK_SNAPSHOT",
"INSERT",
"DELETE",
"VK_HELP",
"0",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"A",
"B",
"C",
"D",
"E",
"F",
"G",
"H",
"I",
"J",
"K",
"L",
"M",
"N",
"O",
"P",
"Q",
"R",
"S",
"T",
"U",
"V",
"W",
"X",
"Y",
"Z",
"VK_LWIN",
"VK_RWIN",
"VK_APPS",
"Unknown",
"VK_SLEEP",
"NUMPAD0",
"NUMPAD1",
"NUMPAD2",
"NUMPAD3",
"NUMPAD4",
"NUMPAD5",
"NUMPAD6",
"NUMPAD7",
"NUMPAD8",
"NUMPAD9",
"VK_MULTIPLY",
"VK_ADD",
"VK_SEPARATOR",
"VK_SUBTRACT",
"VK_DECIMAL",
"VK_DIVIDE",
"F1",
"F2",
"F3",
"F4",
"F5",
"F6",
"F7",
"F8",
"F9",
"F10",
"F11",
"F12",
"VK_F13",
"VK_F14",
"VK_F15",
"VK_F16",
"VK_F17",
"VK_F18",
"VK_F19",
"VK_F20",
"VK_F21",
"VK_F22",
"VK_F23",
"VK_F24",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"VK_NUMLOCK",
"VK_SCROLL",
"VK_OEM_NEC_EQUAL",
"VK_OEM_FJ_MASSHOU",
"VK_OEM_FJ_TOUROKU",
"VK_OEM_FJ_LOYA",
"VK_OEM_FJ_ROYA",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"Unknown",
"LeftShift",
"RightShift",
"VK_LCONTROL",
"VK_RCONTROL",
"VK_LMENU",
"VK_RMENU",
"Browser Back",
"Browser Forward",
"Browser Refresh",
"Browser Stop",
"Browser Search",
"Browser Favourites",
"Browser Home",
"Volume Mute",
"Volume Down",
"Volume Up",
"Media_Next",
"Media_Prev",
"Media_Stop",
"Media_Pause",
"Mail",
"Media",
"App1",
"App2",
"Unknown",
"Unknown",
"OEM_1",
"PLUS",
"COMMA",
"MINUS",
"DOT",
"OEM_2",
"OEM_3"
};

class BindCommand : public Command
{
public:

    BindCommand() : Command("bind", "Bind a module to a key", {"b"})
    {}

    bool execute(std::vector<std::string> cmd) override // bro has no error handling with chat messages imagineeee
    {
        if (cmd.size() < 2) 
            return false;

        if (cmd[0] == "all" && cmd[1] == "none")
        {
            for (auto module : modules)
            {
                module->setKeybind(0);
            }
            ChatUtil::sendMessage("Successfully unbound all!");
            return true;
        }

        auto mod = getModuleByName(cmd[0]);
        if (mod == nullptr)
            return false;

        if (cmd[0] == "all" && cmd [1] == "none")
        {
            for (auto module : modules)
            {
                module->setKeybind(0);
            }
            ChatUtil::sendMessage("Successfully unbound all!");
            return true;
        }

        if (strcmp(cmd[1].c_str(), "none") == 0)
        {
            mod->setKeybind(0);
            ChatUtil::sendMessage(combine("Successfully unbound ", GRAY, mod->getName(), RESET, "!"));
            return true;
        }

        if (cmd[1].length() == 1)
        {
            if (cmd[1][0] > 96 && cmd[1][0] < 122)
                std::transform(cmd[1].begin(), cmd[1].end(), cmd[1].begin(), [](unsigned char c) { return::toupper(c); });
        }

        std::string cmdLower = cmd[1];
        std::transform(cmdLower.begin(), cmdLower.end(), cmdLower.begin(), [](unsigned char c) { return std::tolower(c); });

        for (int i = 0; i < 193; i++)
        {
            std::string keyLower = keyNames[i];
            std::transform(keyLower.begin(), keyLower.end(), keyLower.begin(), [](unsigned char c) { return std::tolower(c); });

            if (cmdLower == keyLower)
            {
                mod->setKeybind(i);
                ChatUtil::sendMessage(combine("Successfully bound ", GRAY, mod->getName(), RESET, " to ", GRAY, keyNames[i], RESET, "!"));
                return true;
            }
        }

        ChatUtil::sendMessage(combine("Key not found!"));
        return false;
    }
};
