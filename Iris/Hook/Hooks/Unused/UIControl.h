#pragma once

/*

48 8B C4 48 89 58 10 48 89 68 18 48 89 70 20 57 48 81 EC ? ? ? ? ? ? 70 E8 ? ? 78 D8 44 ? ? 40 C8 44 ? ? 48 B8 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 30
__int64 debugDetour(UIControl* _this, Vector2<float>* position)
_this + 0x28 ; Hovered UIControl

*/

void* __o__uiControlAddr;

#include "../../SDK/GameCore/Struct/UIControl.h"

//__int64 __fastcall sub_14044A3C0(__int64 a1, float *a2)
bool uicontrolDetour(UIControl* _this, Vector2<float>* size) // setposition?
{
    if (_this->CmpName("play_button"))
    {/*
        _this->Position.y = (GuiInfo::ScreenRes.y / 2) + ((_this->Size.y) * 1) - 6;
        _this->GetChild(0)->Position.y = (GuiInfo::ScreenRes.y / 2) + ((_this->Size.y) * 1) - 6;*/
    }
    
    if (_this->CmpName("settings_button"))
    {/*
        _this->Position.y = (GuiInfo::ScreenRes.y / 2) + ((_this->Size.y) * 2) - 6;
        _this->GetChild(0)->Position.y = (GuiInfo::ScreenRes.y / 2) + ((_this->Size.y) * 2) - 6;*/
    }

    if (_this->CmpName("store_button"))
    {/*
        _this->Position.y = (GuiInfo::ScreenRes.y / 2) - ((_this->Size.y) * 2) - 12;
        _this->GetChild(0)->Position.y = (GuiInfo::ScreenRes.y / 2) - ((_this->Size.y) * 2) - 12;*/
    }

    return CallFunc<bool, UIControl*, Vector2<float>*>(
        __o__uiControlAddr,
        _this, size
    );
}

class UIControlHook : public FuncHook
{
public:
    bool Initialize() override
    {
        void* uiControlAddr = findSig(xorstr_("48 89 5C 24 08 57 48 83 EC 20 F6 41 75"));

        return HookFunction(uiControlAddr, (void*)&uicontrolDetour, &__o__uiControlAddr, xorstr_("UIControl"));

        return true;
    }

    static UIControlHook& Instance()
    {
        static UIControlHook instance;
        return instance;
    }
};