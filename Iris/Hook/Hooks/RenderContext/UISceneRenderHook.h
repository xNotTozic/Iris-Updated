#pragma once

void UISceneRender(
    UIScene* uiscene,
    ScreenContext* screenctx
)
{
    TextHolder scrName{};
    uiscene->getScreenName(&scrName);
    static auto clickguiMod = getModuleByName(xorstr_("clickgui"));
    if (scrName.getTextLength() < 100) strcpy_s(Game::currentScreenName, scrName.getText());
    scrName.alignedTextLength = 0;
    bool isHud = false;
    if (strcmp(scrName.getText(), xorstr_("hud_screen")) == 0) Game::Core::HudScreen = true;

    if (clickguiMod->isEnabled() && strcmp(scrName.getText(), xorstr_("pause_screen")) == 0 || strcmp(scrName.getText(), xorstr_("respawn_screen")) == 0 || strcmp(scrName.getText(), xorstr_("disconnect_screen")) == 0)
    {
        clickguiMod->setEnabled(false);
        Game::GetInstance()->grabCursor();
    }

    CallFunc<void*, UIScene*, ScreenContext*>(
        __o__UISceneRender,
        uiscene,
        screenctx
    );
}