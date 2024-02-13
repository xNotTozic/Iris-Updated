#pragma once

void* __o__sendChatMessage;

void SendChatMessageDetour(
    void* a1,
    TextHolder* message
)
{
    if (message->getText()[0] == *"." or message->getText()[0] == *",")
    {
        commandMgr.sendCommand(message->getText());
        return;
    }

    CallFunc<void*, void*, TextHolder*>(
        __o__sendChatMessage,
        a1,
        message
    );
}

class SendChatMessage : public FuncHook
{
public:
    static SendChatMessage& Instance()
    {
        static SendChatMessage instance;
        return instance;
    }

    bool Initialize() override
    {
        void* sendMessageAddr = findSig(xorstr_("48 89 5C 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 48 89 54 24 ?? 48 8B D9 48 8B 49"));
        return HookFunction(sendMessageAddr, (void*)&SendChatMessageDetour, &__o__sendChatMessage, xorstr_("SendChatMessage"));
    }
};

