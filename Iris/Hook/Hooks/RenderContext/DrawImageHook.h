#pragma once

void DrawImageDetour(
    MinecraftUIRenderContext* _this,
    TextureData* texturePtr,
    Vector2<float>& imagePos,
    Vector2<float>& imageDimension,
    Vector2<float>& UvPos,
    Vector2<float>& UvSize
)
{
    if (strcmp(texturePtr->GetFilePath().getText(), xorstr_("textures/ui/selected_hotbar_slot")) == 0)
    {
        static float lerpedPos = imagePos.x;
        lerpedPos = Math::animate(imagePos.x, lerpedPos, RenderUtil::getDeltaTime() * Game::Core::HotbarSpeed);
        imagePos.x = lerpedPos;
    }

    if (strcmp(texturePtr->GetFilePath().getText(), xorstr_("textures/ui/title")) == 0)
    {
        static float pos = 0;
        pos = Math::lerp(-1000, 0, anim);

        if (Game::FontRepos::GetClientFont() == nullptr)
            return;

        std::string str(Game::Iris::ClientName);

        float strSize = 6;
        float width = RenderUtil::getTextWidth(&str, strSize);

        titlePos = imagePos + Vector2<float>((imageDimension.x / 2) - (width / 2), pos);
        titleSize = Vector2<float>(width, 48);

        RenderUtil::drawGradientString(titlePos, &str, strSize, anim, true, 3, 1, 1, 55);
        RenderUtil::flushString();

        return;
    }

    /* This is for when we want to make our own hotbar */

    /*const char* prefix = "textures/ui/hotbar_";
    int prefixLen = strlen(prefix);
    if (strncmp(texturePtr->GetFilePath().getText(), prefix, prefixLen) == 0)
    {
        RenderUtil::fillRectangle(Vector4<float>(imagePos.y + imageDimension.y, imagePos.x, imagePos.y, imagePos.x + imageDimension.x), UIColor(0, 0, 0), 0.5f);
        return 0;
    }*/

    CallFunc<void*, MinecraftUIRenderContext*, TextureData*, Vector2<float>&, Vector2<float>&, Vector2<float>&, Vector2<float>&>(
        __o__DrawImage,
        _this,
        texturePtr,
        imagePos,
        imageDimension,
        UvPos,
        UvSize
    );
}