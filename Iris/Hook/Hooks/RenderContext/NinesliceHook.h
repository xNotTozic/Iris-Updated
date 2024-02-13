#pragma once

void DrawNineSliceDetour(
    MinecraftUIRenderContext* _this,
    TextureData* texturePtr,
    void* nineSliceInfo
)
{
    /*if (strcmp(texturePtr->GetFilePath().getText(), "textures/ui/hotbar_start_cap") == 0 || (strcmp(texturePtr->GetFilePath().getText(), "textures/ui/hotbar_end_cap") == 0))
        return 0;*/

    if (strcmp(texturePtr->GetFilePath().getText(), xorstr_("textures/ui/focus_border_white")) == 0 ||
        strcmp(texturePtr->GetFilePath().getText(), xorstr_("textures/ui/slider_border")) == 0)
    {
        return;
    }

    CallFunc<void*, MinecraftUIRenderContext*, TextureData*, void*>(
        __o__DrawNineSlice,
        _this,
        texturePtr,
        nineSliceInfo
    );
}